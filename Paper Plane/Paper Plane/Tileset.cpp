//
//  Tileset.cpp
//  Paper Plane
//
//  Créé le 16/12/2013.
//  Stocke les données relatives à une texture de type Tileset (texture découpée en Tiles)
//

#include "Tileset.h"

using namespace std;

/*
 * Constructeur de classe
 * tileset : la texture du tileset
 * numRow : le nombre de lignes du tileset
 * numCol : le nombre de colonnes du tileset
 * widthTile : la largeur d'un tile
 * heightTile : la hauteur d'un tile
 */
Tileset::Tileset(sf::Texture &tileset, int numRow, int numCol, int widthTile, int heightTile, int displayWidth, int displayHeight): m_tileset(tileset), m_numRow(numRow), m_numCol(numCol), m_widthTile(widthTile), m_heightTile(heightTile), m_displayWidth(displayWidth), m_displayHeight(displayHeight)
{
    
}

Tileset::Tileset(sf::Texture &tileset, int numRow, int numCol, int widthTile, int heightTile): m_tileset(tileset), m_numRow(numRow), m_numCol(numCol), m_widthTile(widthTile), m_heightTile(heightTile), m_displayWidth(32), m_displayHeight(32)
{
    
}

/*
 * Retourne le nombre de lignes du tileset
 */
int Tileset::getRow()
{
    return m_numRow;
}

/*
 * Retourne le nombre de colonnes du tileset
 */
int Tileset::getCol()
{
    return m_numCol;
}

/*
 * Retourne la largeur d'un tile
 */
int Tileset::getWidth()
{
    return m_widthTile;
}

/*
 * Retourne la hauteur d'un tile
 */
int Tileset::getHeight()
{
    return m_heightTile;
}

/*
 * Retourne la largeur à l'écran d'un tile
 */
int Tileset::getDisplayWidth()
{
    return m_displayWidth;
}

/*
 * Retourne la hauteur à l'écran d'un tile
 */
int Tileset::getDisplayHeight()
{
    return m_displayHeight;
}

/*
 * Retourne la texture du tileset
 */
sf::Texture* Tileset::getTexture()
{
    return &m_tileset;
}