//
//  Tile.h
//  Paper Plane
//
//  Créé le 16/12/2013.
//  Header de Tile.h
//

#ifndef __Paper_Plane__Tile__
#define __Paper_Plane__Tile__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tileset.h"

class Tile
{
public:
    Tile(Tileset &tileset, int index, int col, int row);
    sf::Sprite getTile();
    int getIndex();
    void setColor(int r, int g, int b, int a=255);
    void setColor(sf::Color color);
    sf::Sprite *draw(int x, int y);
    
private:
    
    int m_index; // L'index du Tile
    Tileset *m_tileset; // Le tileset utilisé
    sf::Sprite m_tile; // Le sprite du Tile
};

#endif /* defined(__Paper_Plane__Tile__) */
