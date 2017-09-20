//
//  Tilemap.h
//  Paper Plane
//
//  Créé le 16/12/2013.
//  Header de Tilemap.cpp
//

#ifndef __Paper_Plane__Tilemap__
#define __Paper_Plane__Tilemap__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Tilemap
{
public:
    
    Tilemap(std::vector<std::vector<int>> &map);
    Tilemap();
    bool addLine(std::vector<int> const&line);
    void debugDisplayTilemap();
    unsigned int getWidth();
    unsigned int getHeight();
    int readPos(int i, int j);
    void clean();
    
private:
    
    std::vector<std::vector<int>> m_map; // Tableau d'index de tile
    unsigned int m_width, m_height; // Largeur et hauteur actuelle
};

#endif /* defined(__Paper_Plane__Tilemap__) */
