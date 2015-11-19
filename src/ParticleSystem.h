//
//  ParticleSystem.h
//  Paper Plane
//
//  Créé le 19/01/2014.
//  Header de ParticleSystem.cpp
//

#ifndef __Paper_Plane__ParticleSystem__
#define __Paper_Plane__ParticleSystem__

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Tileset.h"

namespace pSystem
{
    typedef enum
    {
        MORTAL,
        LIMITED,
        UNDEAD
    }ParticleType; // Si la molécule est mortelle, alors elle a une durée de vie et, une fois morte, est réemise.
    // Si la molécule est limité, alors elle a une durée de vie mais, une fois morte, n'est pas réemise
    // Si la molécule est immortelle, alors elle ne meurt pas et n'est pas réémise
}

class ParticleSystem
{
public:
    
    ParticleSystem(unsigned int qty, sf::Vector2f loc, Tileset &ts, std::vector<int> const&tsLineDesc, sf::Time lifespan, sf::Time frameLife, pSystem::ParticleType pType = pSystem::ParticleType::MORTAL);
    void setLocation(int x, int y);
    void move(int w, int h);
    void update(sf::Time timeElapsed);
    void setParticle(int i);
    void display(sf::RenderWindow &w);
    void init();
    
private:
    
    struct Particle
    {
        sf::Vector2f p_pos; // Position
        sf::Vector2f p_speed; // Vecteur v
        sf::Vector2f p_acceleration; // Vecteur accélération
        sf::Time p_lifespan; // vie de la particule
        sf::Time p_frameLife; // vie de la frame actuelle
        int p_frameIndex; // Index de la frame de la particule
    };
    std::vector<Particle> m_particles; // Le tableau stockant les informations des particules
    sf::Time m_lifespan; // La durée de vie d'une particule
    sf::Time m_frameLife; // La durée de chaque frame
    Tileset *m_ts; // L'adresse du tileset du système
    std::vector<Tile> m_frames; // Le tableau de frames
    sf::Vector2f m_pos; //Position de l'emitter
    pSystem::ParticleType m_pType; //Indique si une particule est undead, c'est à dire si elle ne meurt jamais -> dans ce cas là,
    
};

#endif /* defined(__Paper_Plane__ParticleSystem__) */