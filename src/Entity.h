//
//  Entity.h
//  Paper Plane
//
//  Créé le 17/12/2013.
//  Header de Entity.cpp
//

#ifndef __Paper_Plane__Entity__
#define __Paper_Plane__Entity__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tileset.h"
#include "Tile.h"

class Entity
{
public:
    
    Entity(Tileset &ts, std::vector<int> const&tsLineDesc, int index, std::vector<sf::Vector2i> const&collisionPoints);
    sf::Vector2i getPos();
    sf::Vector2i getSpeed();
    void setPos(int x, int y);
    void setSpeed(int i, int j);
    void move();
    void setFrame(int i);
    Tile *getFrame();
    int getFrameId();
    int getIndex();
    sf::Sprite *draw();
    sf::Vector2i getCollisionPoint();
    
private:
    
    void setupFrames(std::vector<int> const&desc);
    sf::Vector2i m_v; // Le vecteur vitesse de l'entité
    std::vector<sf::Vector2i> m_collisionPoint; // Les coordonnées de collision stockées dans un Vector2i de chaque frame
    int m_x, m_y; // Positions en (x, y) de l'entité
    Tileset *m_ts; // Tileset de l'entité
    int m_index; // L'index de l'entité
    std::vector<Tile> m_frames; // vector stockant les frames d'animation de l'entité
    int m_currFrame; //frame actuelle (défaut 1)
};


//               __
//              /  \
//             /  0 \___
//             |    ,---'      duck designed by Louis Beltrame
//             /   /
// _\_________/   /
//   \    ___    /
//    \_________/
//         ||
//         \<




#endif /* defined(__Paper_Plane__Entity__) */