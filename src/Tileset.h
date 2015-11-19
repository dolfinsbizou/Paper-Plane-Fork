//
//  Tileset.h
//  Paper Plane
//
//  Créé le 16/12/2013.
//  Header de Tileset.cpp
//

#ifndef __Paper_Plane__Tileset__
#define __Paper_Plane__Tileset__

#include <iostream>
#include <SFML/Graphics.hpp>

class Tileset
{
public:
    
    Tileset(sf::Texture &tileset, int numRow, int numCol, int widthTile, int heightTile, int displayWidth, int displayHeight);
    Tileset(sf::Texture &tileset, int numRow, int numCol, int widthTile, int heightTile);
    int getRow();
    int getCol();
    int getWidth();
    int getHeight();
    int getDisplayWidth();
    int getDisplayHeight();
    sf::Texture* getTexture();
    
private:
    
    sf::Texture m_tileset; //La texture du tileset
    int m_numRow, m_numCol; //Le nombre de lignes et de colonnes du tileset
    int m_widthTile, m_heightTile; //La largeur et la hauteur en pixels d'un tile
    int m_displayWidth, m_displayHeight; //La largeur et la hauteur en pixels à l'écran d'un tile
};

#endif /* defined(__Paper_Plane__Tileset__) */