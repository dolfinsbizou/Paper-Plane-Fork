//
//  BackgroundGenerator.cpp
//  Paper Plane
//
//  Créé le 18/12/2013.
//  Générateur de l'arrière plan de jeu
//

#include "BackgroundGenerator.h"

using namespace std;

BackgroundGenerator::BackgroundGenerator(Tilemap tm): m_tm(tm), m_currLine(tm.getHeight()), m_isWindowBeingCreated(true), m_windowLine(1), m_windowPos(10), m_lineSinceLastWindow(0)
{
    
}

void BackgroundGenerator::createLine()
{
    vector<int> line;
    line.push_back(4);
    line.push_back(4);
    int currCase(0);
    bool prepareNextWindow(false);
    
    for(int i = 0 ; i < 12 ; i++)
    {
        if(m_isWindowBeingCreated) //Si on est sur une ligne comportant de la fenêtre
        {
            switch(m_windowLine) //On teste sur quelle ligne de la fenêtre on est
            {
                case 1: //Si on est sur la première ligne
                    //on teste i+3 (c'est à dire si le numéro absolu de la colonne en cours de calcul)
                    if(i+3 == m_windowPos) //Si on est sur le coin supérieur gauche
                    {
                        currCase = 5;
                    }
                    else if(i+3 == m_windowPos+1 || i+3 == m_windowPos+2) //Si on est sur le milieu haut
                    {
                        currCase = 6;
                    }
                    else if(i+3 == m_windowPos+3) //Si on est sur le coin supérieur droit
                    {
                        currCase = 7;
                    }
                    else //Si on est sur aucun des trois
                    {
                            currCase = 1;
                    }
                    break;
                case 2: //Si on est sur une ligne du milieu
                    //on teste i+3 (c'est à dire si le numéro absolu de la colonne en cours de calcul)
                    if(i+3 == m_windowPos) //Si on est sur le milieu gauche
                    {
                        currCase = 8;
                    }
                    else if(i+3 == m_windowPos+1 || i+3 == m_windowPos+2) //Si on est sur le milieu milieu (...)
                    {
                        currCase = 0;
                    }
                    else if(i+3 == m_windowPos+3) //Si on est sur le milieu droit
                    {
                        currCase = 10;
                    }
                    else //Si on est sur aucun des trois
                    {
                        currCase = 1;
                    }
                    break;
                case 3:
                    //on teste i+3 (c'est à dire si le numéro absolu de la colonne en cours de calcul)
                    if(i+3 == m_windowPos) //Si on est sur le coin inférieur gauche
                    {
                        currCase = 11;
                    }
                    else if(i+3 == m_windowPos+1 || i+3 == m_windowPos+2) //Si on est sur le milieu bas
                    {
                        currCase = 12;
                    }
                    else if(i+3 == m_windowPos+3) //Si on est sur le coin inférieur droit
                    {
                        currCase = 13;
                    }
                    else //Si on est sur aucun des trois
                    {
                        currCase = 1;
                    }
                    break;
                default: // Il y a erreur, normalement ça ne devrait pas être possible d'avoir une valeur autre que 1, 2, 3 ou 4
                    currCase = 1; //On gère l'erreur comme on peut, et on reset m_windowLine
                    m_windowLine = 1;
                    m_isWindowBeingCreated = false;
                    prepareNextWindow = true;
                    break;
            }
        }
        else //Sinon on est sur une ligne ne comportant pas de fenêtre
        {
            prepareNextWindow = true;
            currCase = 1;
        }
        line.push_back(currCase);
    }
    
    if(prepareNextWindow)// Si on est sur une ligne sans fenêtre
    {
        int chance(0);
        if(m_lineSinceLastWindow >= 8) //Si la dernière fenêtre est éloignée de 8 lignes ou plus, on prépare une nouvelle fenêtre
        {
            m_isWindowBeingCreated = true;
        }
        else if(m_lineSinceLastWindow >= 5) //Sinon si elle est éloigné de 5 ou plus, il n'y a qu'une chance sur 6
        {
            chance = rand() % 7;
            if (chance == 0)
            {
                m_isWindowBeingCreated = true;
            }
        }
        else if(m_lineSinceLastWindow >= 3) //Sinon si elle est éloigné de 3 ou plus, il y a une chance sur deux de préparer une nouvelle fenêtre 
        {
            chance = rand() % 2;
            if (chance == 0)
            {
                m_isWindowBeingCreated = true;
            }
        }// Et pas de sinon, pour éviter que les fenêtres ne se génèrent trop proches l'une de l'autre
        
        m_lineSinceLastWindow++; //On incrémente le nombre de lignes depuis la dernière fenêtre
        
        currCase = 1;
        
        if(m_isWindowBeingCreated) //Si à la fin de ce if, m_isWindowBeingCreated vaut true, ça veut dire que le prochain appel de createLine() sera pour générer une nouvelle fenêtre
        {
            m_windowPos = (rand() % 5 ) + 5; // Calcul au hasard de la position de la fenêtre entre la 5e colonne et la 9e colonne
        }
    }
    else //Sinon s'il y a une fenêtre sur la ligne
    {
        if (m_windowLine >= 3) //Si c'est la dernière ligne de la fenêtre
        {
            m_isWindowBeingCreated = false;
            m_lineSinceLastWindow = 0;
            m_windowLine = 1;
        }
        else if (m_windowLine > 1) //Sinon si on est sur la ligne du milieu
        {
            int chance = rand() % 30;
            if(chance != 0) //laisse une chance sur 30 d'avoir une ligne supplémentaire sur la fenêtre (ça fait de plus hautes fenêtres, oui)
            {
                m_windowLine++;
            }
        }
        else // Sinon on est sur la première ligne
        {
            m_windowLine++;
        }
    }
    
    // OUF ! o/ On peut enfin créer les deux dernières colonnes de notre ligne, et l'injecter dans la tilemap !
    
    line.push_back(4);
    line.push_back(4);
    
    m_currLine++;
    m_tm.addLine(line);
}

/*
 * Recrée le background generator avec des paramètres prédéfinis
 */
void BackgroundGenerator::setup()
{
    reset();
    
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 5, 6, 6, 7, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 8, 0, 0, 10, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 8, 0, 0, 10, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 11, 12, 12, 13, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_tm.addLine({4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4});
    m_currLine = 12;
}

/*
 * Recrée un background generator vide
 */
void BackgroundGenerator::reset()
{
    m_tm.clean();
    m_currLine = 0;
    m_isWindowBeingCreated = true;
    m_windowLine = 1;
    m_windowPos = 10;
    m_lineSinceLastWindow = 0;
}

/*
 * Retourne la ligne actuelle
 */
std::vector<int> BackgroundGenerator::getCurrLine()
{
    vector<int> currLine;
    if (m_currLine > 0)
    {
        for (unsigned int i = 0 ; i < m_tm.getWidth() ; i++)
        {
            currLine.push_back(m_tm.readPos(i, m_currLine - 1));
        }
        return currLine;
    }
    else
    {
        return {-1};
    }
}

/*
 * Retourne le nombre de lignes actuel
 */
int BackgroundGenerator::getPos()
{
    return m_currLine;
}

/*
 * Retourne toute la tilemap
 */
Tilemap BackgroundGenerator::getTilemap()
{
    return m_tm;
}
