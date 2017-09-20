//
//  main.cpp
//  Paper Plane
//
//  Créé le 16/12/2013.
//  Fonction main et cœur du programme
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "ResourcePath.hpp"
#include "Tileset.h"
#include "Tile.h"
#include "Tilemap.h"
#include "Entity.h"
#include "BackgroundGenerator.h"
#include "PhysicGenerator.h"
#include "ParticleSystem.h"

//Index des tiles
#define BRICK_I 1
#define LAYOUT_I 4
#define TLW_I 5
#define TCW_I 6
#define TRW_I 7
#define MLW_I 8
#define MRW_I 10
#define BLW_I 11
#define BCW_I 12
#define BRW_I 13

#define LWA_I 2
#define RWA_I 3
#define LTG_I 20
#define CTG_I 21 //CTG ! Ce sont ses initiales, Caroline Tirly-Granger ! Et c'est son numéro personnel en plus ! :'D (référence !)
#define RTG_I 22
#define TLHG_I 30
#define TCHG_I 31
#define TRHG_I 32
#define MLHG_I 33
#define MRHG_I 35
#define BLHG_I 36
#define BCHG_I 37
#define BRHG_I 38
#define LMG_I 40
#define CMG_I 41
#define RMG_I 42
#define WIDTH_TILE 70
#define HEIGHT_TILE 70

using namespace std;

/*
 * Retourne le checksum d'un int
 * Fonctionne plus ou moins sur la base d'un checksum 8bit de type "LRC" (http://en.wikipedia.org/wiki/Longitudinal_redundancy_check)
 */
char checkChecksum(int *value)
{
    char checksum(0); // Le retour de la fonction
    int valueSize(sizeof(*value)); // La taille de la variable d'entrée
    char *temp((char*)value); // On crée un pointeur sur value, sous forme d'un tableau de x cases, avec x=sizeof(value)
    
    for(int i = 0 ; i < valueSize ; i++) // Pour chaque octet...
    {
        checksum+=temp[i]; // On ajoute au checksum la valeur de l'octet i
        // Exemple : un int fait 4 octets, avec en valeurs respectives 0x01 0x2F 0xAD 0x1C
        // Le checksum vaudra 0x01 + 0x2F + 0xAD + 0x1C = 0xF9
    }
    
    return checksum;
}

/*
 * Fonction technique pour initialiser le jeu
 */
void setupGame(unsigned int &t, bool &ip, bool &pp, bool &h, bool &isp, bool &spe, bool &spg, Entity &p, unsigned int &SF, BackgroundGenerator &gen, PhysicGenerator &gen2, sf::View &gv, sf::View &sv, int &as, Tile &b, const unsigned int ovv, unsigned int &RSF, const unsigned int ovr, bool &nkp, bool &lkp, int &sc, sf::Text &hct, bool &ia, bool &wk)
{
    t = 0; // Tick pour ralentir la vitesse de déplacement de frame du joueur
    ip = false; // Indique si le jeu est mis en pause
    pp = false; // Indique si la touche escape est actuellement pressée
    h = false; // Indique si le joueur a la main. Concrètement en début de partie l'utilisateur est bloqué le temps de faire l'animation de début
    isp = true; // Indique si le jeu est lancé
    spe = false; // Indique si le son de mouvement du joueur doit être joué
    spg = false; // Indique si le son de mouvement du joueur est en lecture
    
    gen.setup(); // Mise en place du générateur de l'arrière plan
    gen2.setup(); // Mise en place du générateur d'obstacles
    
    gv.reset(sf::FloatRect(0, 0, WIDTH_TILE*16, HEIGHT_TILE*12));
    sv.reset(sf::FloatRect(0, 0, WIDTH_TILE*16, HEIGHT_TILE*12));
    
    // On réinitialise les facteurs vitesse
    SF = ovv;
    RSF = ovr;
    
    // Position et vitesse initiales du joueur
    p.setPos(WIDTH_TILE*1.5, HEIGHT_TILE*2);
    p.setSpeed(-1+SF, SF-2);
    p.setFrame(9);
    as = 0;
    
    // Couleur initiale des briques
    b.setColor(0xD7, 0x9C, 0x8E);
    
    // On réinitialise noKeyPressed, leftKeyPressed et rightKeyPressed
    nkp = true;
    lkp = false;
    
    // On remet le score à 0
    sc = 0;
    
    // Le joueur ressucite \o/
    ia = true;
    wk = false;
    
    // On prépare l'affichage du highscore
    ifstream highscoreF(resourcePath() + "score.dat", ios::in | ios::binary);
    if(highscoreF.is_open())
    {
        int hc(0);
        highscoreF.read((char *)&hc, sizeof(int));
        char checksum(checkChecksum(&hc));
        
        char fileChecksum(0);
        highscoreF.read((char *)&fileChecksum, sizeof(char));
        
        highscoreF.close();
        
        if(checksum == fileChecksum)
        {
            hct.setString("Highscore: " + to_string(hc));
        }
        else
        {
            cerr << "SCORE.DAT MODIFIED, YOU CHEATER" << endl;
            ofstream scoreFile(resourcePath() + "score.dat", ios::out | ios::binary);
            if(scoreFile.is_open())
            {
                char defChecksum(checkChecksum(&sc));
                scoreFile.write((char *)&sc, sizeof(int));
                scoreFile.write((char *)&defChecksum, sizeof(char));
                scoreFile.close();
            }
            hct.setString("Highscore: 0");
        }
    }
    else
    {
        cerr << "SCORE.DAT NOT FOUND" << endl;
        hct.setString("Highscore: 0");
    }
}

int main(int, char const**)
{
    // Avant toute chose on initialise le système de génération de pseudo-aléatoires
    srand(time(0));
    
    /*
     * Variables techniques
     */
    
    sf::Clock watcher; // La montre pour le système de particules
    const unsigned int ORIG_R_SPEED_FACTOR = 3; // Valeur de départ R_SPEED_FACTOR
    unsigned int R_SPEED_FACTOR = ORIG_R_SPEED_FACTOR; // Facteur de vitesse de roation du joueur : plus ce facteur est grand, plus la vitesse de rotation du joueur est faible
    const unsigned int ORIG_SPEED_FACTOR = 5; // Valeur de départ de SPEED_FACTOR
    unsigned int SPEED_FACTOR = ORIG_SPEED_FACTOR; // Facteur de vitesse du joueur : plus ce facteur est grand, plus la vitesse du joueur est élevée
    const unsigned int SKY_FACTOR = 2; // Différence entre la vitesse de chute et la vitesse de l'arrière plan (le ciel) /!\ Il ne doit pas être trop grand, sinon le ciel peut, selon la position du joueur, s'arrêter, voire carrément disparaître !
    const unsigned int NB_BUTTON = 2; // Le nombre de choix dans le menu pause
    const unsigned int NB_MENU = 2; // Le nombre de choix dans le menu principal
    float windowRatio = ((float)WIDTH_TILE*16.0f)/((float)HEIGHT_TILE*12.0f); // Ratio de la fenêtre
    Tile *toDraw(0); // Pointeur vers le tile actuel à dessiner (utilisé dans la game loop)
    bool menuPlaying = true; // Indique si le motif de début de la musique de menu se joue
    //Les variables qui suivent sont initialisées dans le setupGame(...)
    unsigned int tick = 0; // Tick pour ralentir la vitesse de déplacement de frame du joueur
    bool isPaused = false; // Indique si le jeu est mis en pause
    bool pausePressed = false; // Indique si la touche escape est actuellement pressée
    bool handled = false; // Indique si le joueur a la main. Concrètement en début de partie l'utilisateur est bloqué le temps de faire l'animation de début
    bool isPlaying = false; // Indique si le jeu est lancé
    bool soundPlayed = false; // Indique si le son de mouvement du joueur doit être joué
    bool soundPlaying = false; // Indique si le son de mouvement du joueur est en lecture
    int actualStep = false; // L'étape en cours
    bool noKeyPressed(true), leftKeyPressed(false); // Indique si la dernière touche pressée était gauche, et si on vient d'en presser aucune
    int lastFrame(0); // La valeur de la frame d'animation à la frame de jeu précédente (gné xD )
    bool increaseScore(false); // Indique si on peut incrémenter le score
    int playerPos(0); // Position du joueur
    int lastPlayerPos(0); // Position du joueur à la frame précédente
    int score(0); // Le score
    bool isAlive(true); // Indique si le joueur vit :(
    bool wasKilled(false); // Indique si le joueur vient de mourir :((
    
    /*
     * Ressources de base
     */
    
    // Fenêtre de jeu
    sf::RenderWindow window(sf::VideoMode(WIDTH_TILE*16, HEIGHT_TILE*12), "Paper Plane");
    window.setVerticalSyncEnabled(true); //On active la synchro verticale
    
    // Vues (les différentes couches de rendu)
    sf::View gameView(sf::FloatRect(0, 0, WIDTH_TILE*16, HEIGHT_TILE*12));
    sf::View skyView(sf::FloatRect(0, 0, WIDTH_TILE*16, HEIGHT_TILE*12));
    
    // Musiques
    sf::Music themeSong;
    if(!themeSong.openFromFile(resourcePath() + "audio/main_theme.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Music menuSong;
    if(!menuSong.openFromFile(resourcePath() + "audio/menu_song.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Music menuLoop;
    if(!menuLoop.openFromFile(resourcePath() + "audio/menu_song2.ogg"))
    {
        return EXIT_FAILURE;
    }
        
    // Sons
    sf::SoundBuffer planeSoundBuffer;
    if(!planeSoundBuffer.loadFromFile(resourcePath() + "audio/plane_sound.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sound planeSound;
    planeSound.setBuffer(planeSoundBuffer);
    
    sf::SoundBuffer pauseSoundBuffer;
    if(!pauseSoundBuffer.loadFromFile(resourcePath() + "audio/pause.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sound pauseSound;
    pauseSound.setBuffer(pauseSoundBuffer);
    
    sf::SoundBuffer playSoundBuffer;
    if(!playSoundBuffer.loadFromFile(resourcePath() + "audio/play.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sound playSound;
    playSound.setBuffer(playSoundBuffer);
    
    playSound.setVolume(800);
    pauseSound.setVolume(800);
    
    sf::SoundBuffer deadSoundBuffer;
    if(!deadSoundBuffer.loadFromFile(resourcePath() + "audio/dead_sound.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sound deadSound;
    deadSound.setBuffer(deadSoundBuffer);
    
    sf::SoundBuffer menuSoundBuffer;
    if(!menuSoundBuffer.loadFromFile(resourcePath() + "audio/menu_sound.ogg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sound menuSound;
    menuSound.setBuffer(menuSoundBuffer);
    
    // Chargement de l'icone de l'App
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "image/icon.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Fontes et textes
    sf::Font fipps;
    if(!fipps.loadFromFile(resourcePath() + "font/fipps.ttf"))
    {
        return EXIT_FAILURE;
    }
    string quitButton("Quit");
    string playButton("Resume");
    string startButton("Play");
    string version("BETA - Gently coded by Dolfinsbizou");
    sf::Text textPauseQuitButton, textPausePlayButton, textStartButton, textExitButton;
    textPausePlayButton.setFont(fipps);
    textPauseQuitButton.setFont(fipps);
    textStartButton.setFont(fipps);
    textExitButton.setFont(fipps);
    textPausePlayButton.setString(playButton);
    textPauseQuitButton.setString(quitButton);
    textStartButton.setString(startButton);
    textExitButton.setString(quitButton);
    textPausePlayButton.setPosition(WIDTH_TILE*4, HEIGHT_TILE*5.5);
    textPauseQuitButton.setPosition(WIDTH_TILE*10, HEIGHT_TILE*5.5);
    textStartButton.setPosition(WIDTH_TILE*6, HEIGHT_TILE*8.5);
    textExitButton.setPosition(WIDTH_TILE*6, HEIGHT_TILE*10);
    textPausePlayButton.setCharacterSize(((WIDTH_TILE+HEIGHT_TILE)/2)*0.5);
    textPauseQuitButton.setCharacterSize(((WIDTH_TILE+HEIGHT_TILE)/2)*0.5);
    textStartButton.setCharacterSize(((WIDTH_TILE+HEIGHT_TILE)/2)*0.5);
    textExitButton.setCharacterSize(((WIDTH_TILE+HEIGHT_TILE)/2)*0.5);
    sf::Text textScore;
    textScore.setFont(fipps);
    textScore.setPosition(WIDTH_TILE*0.5, HEIGHT_TILE*0.5);
    textScore.setCharacterSize(45);
    sf::Text textHighscore;
    textHighscore.setFont(fipps);
    textHighscore.setPosition(WIDTH_TILE*0.2, HEIGHT_TILE*0.2);
    textHighscore.setCharacterSize(18);
    sf::Text textVersion;
    textVersion.setFont(fipps);
    textVersion.setPosition(WIDTH_TILE*0.2, HEIGHT_TILE*0.2);
    textVersion.setCharacterSize(14);
    textVersion.setColor(sf::Color(0, 0, 0));
    textVersion.setString("BETA - Gently coded by Dolfinsbizou");
    
    int activeButton = 0;
    int menuButton = 0;
    
    
    /*
     * Textures et sprites de base
     */
    
    // Menu
    sf::Texture t_menu;
    if(!t_menu.loadFromFile(resourcePath() + "image/menu.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite menu;
    menu.setTexture(t_menu);
    menu.setScale(((float)(WIDTH_TILE*16))/t_menu.getSize().x,((float)(HEIGHT_TILE*12))/t_menu.getSize().y);
    
    // Texture du ciel
    sf::Texture t_sky;
    if (!t_sky.loadFromFile(resourcePath() + "image/sky_16.png"))
    {
        return EXIT_FAILURE;
    }
    
    // Texture et sprite d'arrière plan de pause
    sf::Texture t_pause;
    if (!t_pause.loadFromFile(resourcePath() + "image/pause_shade.png"))
    {
        return EXIT_FAILURE;
    }
    t_pause.setRepeated(true);
    sf::Sprite pauseBg;
    pauseBg.setTexture(t_pause);
    pauseBg.setTextureRect(sf::IntRect(0, 0, WIDTH_TILE*16, HEIGHT_TILE*12));
    
    // Sprites de ciel
    sf::Sprite sky1, sky2;
    sky1.setTexture(t_sky);
    sky2.setTexture(t_sky);
    sky1.setScale(((float)(WIDTH_TILE*16))/t_sky.getSize().x,((float)(HEIGHT_TILE*12))/t_sky.getSize().y);
    sky2.setScale(((float)(WIDTH_TILE*16))/t_sky.getSize().x,((float)(HEIGHT_TILE*12))/t_sky.getSize().y);
    sky2.setPosition(0, HEIGHT_TILE*12);
    
    /*
     * Chargement des tilesets
     */
    
    // Textures de tilesets
    sf::Texture t_tileset;
    if(!t_tileset.loadFromFile(resourcePath() + "image/terrain_16.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Texture t_plane;
    if(!t_plane.loadFromFile(resourcePath() + "image/plane_16.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Texture t_particle;
    if(!t_particle.loadFromFile(resourcePath() + "image/particles.png"))
    {
        return EXIT_FAILURE;
    }
    
    // Les tilesets, dans l'ordre : blocs, avion, particules
    Tileset tileset(t_tileset, 5, 10, 16, 16, WIDTH_TILE, HEIGHT_TILE); // Décor
    Tileset tsPlane(t_plane, 8, 5, 25, 24, WIDTH_TILE*1.55, HEIGHT_TILE*1.55); // Avion
    int particleSize(3);
    Tileset tsParticle(t_particle, 10, 1, particleSize, particleSize, WIDTH_TILE*0.15, HEIGHT_TILE*0.15); // Particules
    
    /*
     * Système de particule
     */
    
    ParticleSystem deadParticles(50, sf::Vector2f(0, 0), tsParticle, {10}, sf::seconds(2), sf::seconds(0.1f), pSystem::ParticleType::UNDEAD);
    
    /*
     * Initialisation du joueur
     */
    
    Entity player(tsPlane, // Tileset
                  {8, 1}, // Nombre de frames par ligne du tileset
                  1, // Index de l'entité
                  { // Coordonnées de collision de chaque frame
                      sf::Vector2i(0,14),   // Frame 1
                      sf::Vector2i(1,17),   // Frame 2
                      sf::Vector2i(3,17),   // Frame 3
                      sf::Vector2i(5,19),   // Frame 4
                      sf::Vector2i(12,19),  // Frame 5
                      sf::Vector2i(19,19),  // Frame 6
                      sf::Vector2i(21,17),  // Frame 7
                      sf::Vector2i(23,17),  // Frame 8
                      sf::Vector2i(24,14)   // Frame 9
                  });
    
    /* 
     * Création des tiles
     */
    
    // Tiles de décor
    Tile brick(tileset, BRICK_I, 1, 1);
    Tile layout(tileset, LAYOUT_I, 1, 3);
    Tile topLeftWindow(tileset, TLW_I, 2, 1);
    Tile topCenterWindow(tileset, TCW_I, 2, 2);
    Tile topRightWindow(tileset, TRW_I, 2, 3);
    Tile midLeftWindow(tileset, MLW_I, 3, 1);
    Tile midRightWindow(tileset, MRW_I, 3, 3);
    Tile botLeftWindow(tileset, BLW_I, 4, 1);
    Tile botCenterWindows(tileset, BCW_I, 4, 2);
    Tile botRightWindow(tileset, BRW_I, 4, 3);
    
    // Tiles physiques
    Tile leftWall(tileset, LWA_I, 1, 2);
    Tile rightWall(tileset, RWA_I, 1, 4);
    Tile leftTinyGround(tileset, LTG_I, 5, 1);
    Tile centerTinyGround(tileset, CTG_I, 5, 2);
    Tile rightTinyGround(tileset, RTG_I, 5, 3);
    Tile topLeftHugeGround(tileset, TLHG_I, 6, 1);
    Tile topCenterHugeGround(tileset, TCHG_I, 6, 2);
    Tile topRightHugeGround(tileset, TRHG_I, 6, 3);
    Tile midLeftHugeGround(tileset, MLHG_I, 7, 1);
    Tile midRightHugeGround(tileset, MRHG_I, 7, 3);
    Tile botLeftHugeGround(tileset, BLHG_I, 8, 1);
    Tile botCenterHugeGround(tileset, BCHG_I, 8, 2);
    Tile botRightHugeGround(tileset, BRHG_I, 8, 3);
    Tile LeftMedGround(tileset, LMG_I, 9, 1);
    Tile CenterMedGround(tileset, CMG_I, 9, 2);
    Tile RightMedGround(tileset, RMG_I, 9, 3);
    
    /* 
     * Générateurs de tilemap
     */
    
    BackgroundGenerator backgroundGenerator(*new Tilemap());
    PhysicGenerator physicGenerator(*new Tilemap());
    
    // Derniers préparatifs
    themeSong.setLoop(true);
    menuLoop.setLoop(true);
    menuSong.play();
    
    /* 
     * La "game loop", c'est à dire la boucle qui englobe l'éxécution de la fenêtre
     */
    
    while (window.isOpen())
    {
        /*
         * Test des events
         */
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(isPlaying) //évents de jeu
            {
                switch (event.type)
                {
                    case sf::Event::Closed: // Demande de fermeture de la fenêtre
                        window.close();
                        break;
                    case sf::Event::LostFocus: // Focus perdu
                        if(isAlive)
                        {
                            isPaused = true;
                            themeSong.pause();
                        }
                        break;
                    case sf::Event::KeyPressed: // Touche pressée
                        switch(event.key.code)
                        {
                        case sf::Keyboard::Escape: // Echap
                            if(isAlive)
                            {
                                if(!pausePressed)
                                {
                                    pausePressed = true;
                                    if(isPaused)
                                    {
                                        isPaused = false;
                                        themeSong.play();
                                        playSound.play();
                                    }
                                    else
                                    {
                                        isPaused = true;
                                        themeSong.pause();
                                        pauseSound.play();
                                    }
                                }
                            }
                            else
                            {
                                themeSong.stop();
                                menuSound.play();
                                menuSong.play();
                                menuPlaying = true;
                                isPlaying = false;
                            }
                            break;
                        case sf::Keyboard::Left: // Flèche gauche
                            if(isPaused)
                            {
                                if(activeButton <= 0)
                                {
                                    activeButton = NB_BUTTON-1;
                                }
                                else
                                {
                                    activeButton--;
                                }
                            }
                            break;
                        case sf::Keyboard::Right: // Flèche droite
                            if(isPaused)
                            {
                                if(activeButton >= (int)NB_BUTTON-1)
                                {
                                    activeButton = 0;
                                }
                                else
                                {
                                    activeButton++;
                                }
                            }
                            break;
                        case sf::Keyboard::Return: // Entrée
                            if(isPaused)
                            {
                                switch(activeButton)
                                {
                                    case 0:
                                        playSound.play();
                                        isPaused = false;
                                        themeSong.play();
                                        break;
                                    case 1:
                                        themeSong.stop();
                                        menuSound.play();
                                        menuSong.play();
                                        menuPlaying = true;
                                        isPlaying = false;
                                        break;
                                }
                            }
                            break;
                        default:
                            
                            break;
                    }
                        break;
                    case sf::Event::KeyReleased: // Touche relachée
                        switch(event.key.code)
                    {
                        case sf::Keyboard::Escape: // Echap
                            pausePressed = false;
                            break;
                        default:
                            
                            break;
                    }
                        break;
                    default:
                        
                        break;
                }
            }
            else // events du menu
            {
                switch (event.type)
                {
                    case sf::Event::Closed: // Demande de fermeture de la fenêtre
                        window.close();
                        break;
                    case sf::Event::KeyPressed: // Touche préssée
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Up: // Flèche haut
                                if(menuButton <= 0)
                                {
                                    menuButton = NB_MENU-1;
                                }
                                else
                                {
                                    menuButton--;
                                }
                                break;
                            case sf::Keyboard::Down: // Flèche bas
                                if(menuButton >= (int)NB_MENU-1)
                                {
                                    menuButton = 0;
                                }
                                else
                                {
                                    menuButton++;
                                }

                                break;
                            case sf::Keyboard::Return: // Entrée
                                switch(menuButton)
                                {
                                    case 0:
                                        setupGame(tick, isPaused, pausePressed, handled, isPlaying, soundPlayed, soundPlaying, player, SPEED_FACTOR, backgroundGenerator, physicGenerator, gameView, skyView, actualStep, brick, ORIG_SPEED_FACTOR, R_SPEED_FACTOR, ORIG_R_SPEED_FACTOR, noKeyPressed, leftKeyPressed, score, textHighscore, isAlive, wasKilled); //Initialisatio du jeu
                                        menuSong.stop();
                                        menuLoop.stop();
                                        activeButton = 0;
                                        themeSong.play();
                                        break;
                                    case 1:
                                        window.close();
                                        break;
                                }

                                break;
                            default:
                                
                                break;
                        }
                        break;
                    default:
                        
                        break;
                }
            }
        }

        if(isPlaying) // Fonctionnement de la phase de jeu
        {
            Tilemap cp = backgroundGenerator.getTilemap(); // ESSENTIEL ! Sinon à chaque tour du double for (plus bas) il va réaccéder à backgroundGenerator.getTilemap(), ce qui ralentit ENORMEMENT le programme (j'ai testé)
            Tilemap cp2 = physicGenerator.getTilemap(); // idem
            int renderUp = (int)((player.getPos().y-(2*HEIGHT_TILE))/HEIGHT_TILE); // De même, cette petite variable évite de devoir recalculer player.getPos().y-(2*HEIGHT_TILE))/HEIGHT_TILE à chaque tour de for
            
            /* Boucle d'éxecution de jeu, se fait seulement si le jeu n'est pas en pause */
            if(!isPaused)
            {
                if(handled) //Si le joueur a la main
                {
                    if(isAlive) // Si le joueur est en vie
                    {
                        // Rotation du joueur si une touche est pressée
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        {
                            
                            if(tick%R_SPEED_FACTOR == 0)
                            {
                                player.setFrame(player.getFrameId() - 1);
                                leftKeyPressed = true;
                                noKeyPressed = false;
                            }
                            tick++;
                        }
                        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        {
                            if(tick%R_SPEED_FACTOR == 0)
                            {
                                player.setFrame(player.getFrameId() + 1);
                                leftKeyPressed = false;
                                noKeyPressed = false;
                            }
                            tick++;
                        }
                        else
                        {
                            tick = 0;
                            noKeyPressed = true;
                        }
                        
                        // On prépare à jouer le son seulement si c'est nécessaire
                        if((player.getFrameId() > 2 && player.getFrameId() < 8) && tick != 0)
                        {
                            soundPlayed = true;
                        }
                        
                        // Si on avait pressé aucune touche, alors on se met sur une frame fixe, si on est sur une frame technique
                        // Les frames techniques sont des frames sur lequel l'avion ne peut s'arrêter : elles servent seulement à la fluidité du mouvement
                        if(noKeyPressed)
                        {
                            if(leftKeyPressed)
                            {
                                switch(lastFrame)
                                {
                                    case 2:
                                        player.setFrame(1);
                                        break;
                                    case 4:
                                        player.setFrame(3);
                                        break;
                                    case 6:
                                        player.setFrame(5);
                                        break;
                                    case 8:
                                        player.setFrame(7);
                                        break;
                                }
                            }
                            else
                            {
                                switch(lastFrame)
                                {
                                    case 2:
                                        player.setFrame(3);
                                        break;
                                    case 4:
                                        player.setFrame(5);
                                        break;
                                    case 6:
                                        player.setFrame(7);
                                        break;
                                    case 8:
                                        player.setFrame(9);
                                        break;
                                }
                            }
                        }
                        
                        // Augmentation progressive de la difficulté
                        if((player.getPos().y/HEIGHT_TILE) % 333 == 0 && SPEED_FACTOR < ORIG_SPEED_FACTOR+3)
                        {
                            SPEED_FACTOR++;
                        }
                        
                        // Préparation du nouveau vecteur vitesse du joueur
                        lastFrame = player.getFrameId();
                        switch(lastFrame)
                        {
                            case 1:
                            case 2:
                                if(player.getPos().x > WIDTH_TILE*2 || (player.getPos().x >= WIDTH_TILE*12.45)) // À chaque fois, ce if/else suplémentaire permet d'éviter au joueur de sortir des limites de la map
                                {
                                    player.setSpeed(1-SPEED_FACTOR, SPEED_FACTOR-2);
                                }
                                else
                                {
                                    player.setSpeed(0, SPEED_FACTOR-2);
                                }
                                break;
                            case 3:
                            case 4:
                                if(player.getPos().x > WIDTH_TILE*2 || (player.getPos().x >= WIDTH_TILE*12.45))
                                {
                                    player.setSpeed(-SPEED_FACTOR, SPEED_FACTOR-1);
                                }
                                else
                                {
                                    player.setSpeed(0, SPEED_FACTOR);
                                }
                                break;
                            case 5:
                                player.setSpeed(0, 1+SPEED_FACTOR);
                                break;
                            case 6:
                            case 7:
                                if(player.getPos().x < WIDTH_TILE*12.45 || player.getPos().x <= WIDTH_TILE*2)
                                {
                                    player.setSpeed(SPEED_FACTOR, SPEED_FACTOR);
                                }
                                else
                                {
                                    player.setSpeed(0, SPEED_FACTOR-1);
                                }
                                break;
                            case 8:
                            case 9:
                                if(player.getPos().x < WIDTH_TILE*12.45 || player.getPos().x <= WIDTH_TILE*2)
                                {
                                    player.setSpeed(-1+SPEED_FACTOR, SPEED_FACTOR-2);
                                }
                                else
                                {
                                    player.setSpeed(0, SPEED_FACTOR-2);
                                }
                                break;
                        }
                    }
                } //                                                                             ∆
                else // Sinon il n'a pas la main, on vérifie s'il est prêt à l'avoir (:'D)  >-)-)-)-)-)°> <- Et ceci est un poisson
                { //                                                                               '
                    if(player.getPos().x >= WIDTH_TILE*8)
                    {
                        handled = true;
                    }
                }
                
                //Préparation de l'incrémentation du score
                if(increaseScore)
                {
                    increaseScore = false;
                }
                
                playerPos = player.getPos().y/HEIGHT_TILE;
                if(playerPos != lastPlayerPos)
                {
                    vector<int> obstL = physicGenerator.getObstacleVector(); // Récupère chaque ligne contenant un obstacle
                    for(unsigned int i = 0 ; i < obstL.size() ; i++)
                    {
                        if(playerPos == obstL[i]) // Si on arrive à un obstacle
                        {
                            increaseScore = true; // on va pouvoir incrémenter le score
                            i = obstL.size(); // et on fait en sorte de quitter le for (tfw tu relis ton code 3 ans après et que tu découvres que tu savais pas faire un break)
                        }
                    }
                }
                
                if(increaseScore && isAlive) // Si le score peut-être augmenté et que le joueur est vivant
                {
                    score++;
                }
                
                // Couleur des briques (rouge, vert, jaune, ou violet)
                if(actualStep != player.getPos().y/HEIGHT_TILE)
                {
                    actualStep = player.getPos().y/HEIGHT_TILE;
                    switch(actualStep)
                    {
                        case 152:
                            brick.setColor(0xFF, 0x70, 0x70);
                            break;
                        case 295:
                            brick.setColor(0x70, 0xFF, 0x70);
                            break;
                        case 440:
                            brick.setColor(0xFF, 0xFF, 0x70);
                            break;
                        case 586:
                            brick.setColor(0x99, 0x30, 0xBB);
                            break;
                    }
                }
               
                /*
                 * Position absolue du point de collision du joueur
                 */
                double pPosX(floor(((double)player.getPos().x + (double)(player.getCollisionPoint().x*((WIDTH_TILE*1.55)/25)))));
                double pPosY(floor(((double)player.getPos().y + (double)(player.getCollisionPoint().y*((HEIGHT_TILE*1.55)/24)))));
                
                if(isAlive) // Si le joueur est vivant
                {
                    // La gameview bouge
                    gameView.move(0, player.getSpeed().y);
                    // ...Et le joueur aussi
                    player.move();
                
                    // Déplacement du ciel
                    if(skyView.getCenter().y > HEIGHT_TILE*18)//Si on arrive au bout de la vue
                    {
                        int fac = skyView.getCenter().y + player.getSpeed().y - SKY_FACTOR - HEIGHT_TILE*18; // rectification vu que dans 99% des cas le centre de la vue n'arrive pas tout pile au bon endroit. Sans cette vérification, le mouvement est saccadé lors du reset de la vue
                        skyView.setCenter(WIDTH_TILE*8, (HEIGHT_TILE*6) + fac); //Reset de la vue
                    }
                    else // Sinon
                    {
                        skyView.move(0, player.getSpeed().y - SKY_FACTOR); //On la déplace
                    }
                    
                    // Génération de nouvelles lignes dans les generator
                    if(backgroundGenerator.getPos() - (int)((player.getPos().y+(15*HEIGHT_TILE))/HEIGHT_TILE) <= 10)
                    {
                        backgroundGenerator.createLine();
                    }
                    if(physicGenerator.getPos() - (int)((player.getPos().y+(15*HEIGHT_TILE))/HEIGHT_TILE) <= 14)
                    {
                        physicGenerator.addObstacle();
                    }
                }
            
                // Vérification des collisions
                switch(cp2.readPos((int)(pPosX/WIDTH_TILE), (int)(pPosY/HEIGHT_TILE))) // On récupère la valeur du block sur lequel se situe le point de collision
                {
                    case 0:
                    case LWA_I:
                    case RWA_I:
                        
                        break;
                    case LTG_I:
                    case CTG_I:
                    case RTG_I:
                    {
                        int tempOffset = floor((16*(pPosY - floor(pPosY/HEIGHT_TILE)*HEIGHT_TILE))/50);
                        if(tempOffset > 2 && tempOffset < 14) // On affine la collision, car ces obstacles sont visuellement plus petits que les autres
                        {
                            if(isAlive)
                            {
                                wasKilled = true;
                            }
                            isAlive = false;
                        }
                        break;
                    }
                    default:
                        if(isAlive)
                        {
                            wasKilled = true;
                        }
                        isAlive = false;
                        break;
                }

                if(wasKilled && !isAlive) // Si il vient juste de mourir
                {
                    ifstream scoreCheck(resourcePath() + "score.dat", ios::in | ios::binary); // On vérifie le highscore
                    if(scoreCheck.is_open())
                    {
                        int highscore(0);
                        scoreCheck.read((char *)&highscore, sizeof(int));
                        scoreCheck.close();
                        if(score > highscore) // Si le score de la partie dépasse le highscore
                        {
                            ofstream scoreFile(resourcePath() + "score.dat", ios::out | ios::binary);
                            if(scoreFile.is_open())
                            {
                                char defChecksum(checkChecksum(&score));
                                scoreFile.write((char *)&score, sizeof(int)); // ...On sauvegarde le nouveau highscore et le nouveau checksum
                                scoreFile.write((char *)&defChecksum, sizeof(char));
                                scoreFile.close();
                            }
                            else
                            {
                                cerr << "UNABLE TO SAVE SCORE: UNABLE TO OPEN SCORE.DAT" << endl;
                            }
                        }
                    }
                    else // Si il n'y a pas de fichier de score
                    {
                        cerr << "SCORE.DAT NOT FOUND" << endl;
                        ofstream scoreFile(resourcePath() + "score.dat", ios::out | ios::binary);
                        if(scoreFile.is_open())
                        {
                            char defChecksum(checkChecksum(&score));
                            scoreFile.write((char *)&score, sizeof(int)); // ...On le crée et on sauvegarde le score/checksum
                            scoreFile.write((char *)&defChecksum, sizeof(char));
                            scoreFile.close();
                        }
                        else
                        {
                            cerr << "UNABLE TO SAVE SCORE: UNABLE TO OPEN SCORE.DAT" << endl;
                        }
                    }
                    deadSound.play();
                    watcher.restart();
                    deadParticles.setLocation(pPosX, pPosY); // Et on lance le système de particules
                    deadParticles.init();
                    wasKilled = false;
                }
            }
            // Effacement de l'écran
            window.clear();
            
            window.setView(skyView);
            
            // Affichage du ciel dans la skyview
            window.draw(sky1);
            window.draw(sky2);
            
            // Le reste du rendu s'effectue dans la vue de jeu
            window.setView(gameView);
            
            // Rendu du joueur quand il n'a pas la main, c'est à dire derrière la map, pour donner l'illusion qu'il sort de la fenêtre !
            if(!handled)
            {
                window.draw(*player.draw());
            }
            
            /* Rendu des tilemaps */
            
            // Background
            for (int i = 0 ; i < 15 ; i++)
            {
                for (int j = 0 ; j < 16 ; j++)
                {
                    switch (cp.readPos(j, i+renderUp))
                    {
                        case BRICK_I:
                            toDraw = &brick;
                            break;
                        case LAYOUT_I:
                            toDraw = &layout;
                            break;
                        case TLW_I:
                            toDraw = &topLeftWindow;
                            break;
                        case TCW_I:
                            toDraw = &topCenterWindow;
                            break;
                        case TRW_I:
                            toDraw = &topRightWindow;
                            break;
                        case MLW_I:
                            toDraw = &midLeftWindow;
                            break;
                        case MRW_I:
                            toDraw = &midRightWindow;
                            break;
                        case BLW_I:
                            toDraw = &botLeftWindow;
                            break;
                        case BCW_I:
                            toDraw = &botCenterWindows;
                            break;
                        case BRW_I:
                            toDraw = &botRightWindow;
                            break;
                        default:
                            toDraw = 0;
                            break;
                    }
                    if(toDraw != 0) // Si on est sur une case non vide, alors on dessine le sprite
                    {
                        window.draw(*toDraw->draw(j*(tileset.getDisplayWidth()), (i+renderUp)*(tileset.getDisplayHeight())));
                    }
                }
            }
            
            // physicTM
            
            for (int i = 0 ; i < 15 ; i++)
            {
                for (int j = 0 ; j < 16 ; j++)
                {
                    switch (cp2.readPos(j, i+renderUp))
                    {
                        case LWA_I:
                            toDraw = &leftWall;
                            break;
                        case RWA_I:
                            toDraw = &rightWall;
                            break;
                        case LTG_I:
                            toDraw = &leftTinyGround;
                            break;
                        case CTG_I:
                            toDraw = &centerTinyGround;
                            break;
                        case RTG_I:
                            toDraw = &rightTinyGround;
                            break;
                        case TLHG_I:
                            toDraw = &topLeftHugeGround;
                            break;
                        case TCHG_I:
                            toDraw = &topCenterHugeGround;
                            break;
                        case TRHG_I:
                            toDraw = &topRightHugeGround;
                            break;
                        case MLHG_I:
                            toDraw = &midLeftHugeGround;
                            break;
                        case MRHG_I:
                            toDraw = &midRightHugeGround;
                            break;
                        case BLHG_I:
                            toDraw = &botLeftHugeGround;
                            break;
                        case BCHG_I:
                            toDraw = &botCenterHugeGround;
                            break;
                        case BRHG_I:
                            toDraw = &botRightHugeGround;
                            break;
                        case LMG_I:
                            toDraw = &LeftMedGround;
                            break;
                        case CMG_I:
                            toDraw = &CenterMedGround;
                            break;
                        case RMG_I:
                            toDraw = &RightMedGround;
                            break;
                        default:
                            toDraw = 0;
                            break;
                    }
                    if(toDraw != 0) // Si on est sur une case non vide, alors on dessine le sprite
                    {
                        window.draw(*toDraw->draw(j*(tileset.getDisplayWidth()), (i+renderUp)*(tileset.getDisplayHeight())));
                    }
                }
            }
            
            toDraw = 0; // On reset le pointeur
            
            lastPlayerPos = playerPos; // La position actuelle du joueur est stockée dans lastPlayerPos pour le tour de gameloop suivant
            
            // Rendu du joueur s'il a la main ou si il est sorti de la fenêtre de départ
            if((handled || player.getPos().x >= WIDTH_TILE*5) && isAlive)
            {
                window.draw(*player.draw());
            }
            
            if(!isAlive) // Si il est mort, alors on actualise le système de particules et on l'affiche
            {
                sf::Time elapsed = watcher.restart();
                deadParticles.update(elapsed);
                deadParticles.display(window);
            }
            
            // On joue le son de mouvement si nécessaire
            if(soundPlayed && !soundPlaying)
            {
                soundPlaying = true;
                planeSound.play();
            }
            else if(planeSound.getStatus() == sf::SoundSource::Stopped)
            {
                soundPlayed = false;
                soundPlaying = false;
            }
            
            
            // Vérifie le ratio de la fenêtre
            sf::Vector2u wSize = window.getSize();
            if(((float)(wSize.x))/((float)(wSize.y)) != windowRatio) //Si le ratio a changé alors on le corrige
            {
                window.setSize(sf::Vector2u(wSize.x, (int)((float)(wSize.x)/windowRatio)));
            }
            
            window.setView(window.getDefaultView());
            textScore.setString(to_string(score));
            sf::FloatRect textBoundingBox = textScore.getGlobalBounds();
            textScore.setPosition(WIDTH_TILE*8 - (textBoundingBox.width/2), HEIGHT_TILE*0.5);
            window.draw(textScore);
            window.draw(textHighscore);
            
            // Si le jeu est en pause, alors on affiche le menu pause
            if(isPaused)
            {
                window.draw(pauseBg);
                switch(activeButton)
                {
                    case 0:
                        textPausePlayButton.setStyle(sf::Text::Underlined);
                        textPauseQuitButton.setStyle(0);
                        break;
                    case 1:
                        textPausePlayButton.setStyle(0);
                        textPauseQuitButton.setStyle(sf::Text::Underlined);
                        break;
                }
                window.draw(textPausePlayButton);
                window.draw(textPauseQuitButton);
            }
            
            // Raffraichit l'affichage
            window.display();
            
        }
        else // Si on est pas en jeu, alors on est dans le menu
        {
            if(menuSong.getStatus() == sf::SoundSource::Stopped && menuPlaying) // Si le son d'intro est fini de jouer, alors on lance la boucle sonore ultra-chiante qui te rentre dans la tête
            {
                menuPlaying = false;
                menuLoop.play();
            }
            
            window.clear();
            
            window.setView(window.getDefaultView());
            
            window.draw(menu);
            
            switch(menuButton)
            {
                case 0:
                    textStartButton.setStyle(sf::Text::Underlined);
                    textExitButton.setStyle(0);
                    break;
                case 1:
                    textStartButton.setStyle(0);
                    textExitButton.setStyle(sf::Text::Underlined);
                    break;
            }
            window.draw(textStartButton);
            window.draw(textExitButton);
            window.draw(textVersion);
            
            // Vérifie le ratio de la fenêtre
            sf::Vector2u wSize = window.getSize();
            if(((float)(wSize.x))/((float)(wSize.y)) != windowRatio) //Si le ratio a changé alors on le corrige
            {
                window.setSize(sf::Vector2u(wSize.x, (int)((float)(wSize.x)/windowRatio)));
            }
                        
            // Raffraichit l'affichage
            window.display();
        }
    }

    return EXIT_SUCCESS;
}
