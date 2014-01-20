//
//  Tile.cpp
//  Paper Plane
//
//  Créé le 16/12/2013.
//  Stocke un Tile d'après un Tileset
//

#include "Tile.h"

using namespace std;

/*
 * Constructeur de classe
 * tileset : le tileset
 * index : l'index du tile (pour le tile mapping)
 * row : position sur la ligne du tile
 * col : position sur la colonne du tile
 */
Tile::Tile(Tileset &tileset, int index, int col, int row): m_index(index), m_tileset(&tileset)
{
    m_tile.setTexture(*m_tileset->getTexture());
    m_tile.setTextureRect(sf::IntRect((row-1)*m_tileset->getWidth(), (col-1)*m_tileset->getHeight(), m_tileset->getWidth(), m_tileset->getHeight()));
    m_tile.setScale((float)m_tileset->getDisplayWidth()/(float)m_tileset->getWidth(), (float)m_tileset->getDisplayHeight()/(float)m_tileset->getHeight());
}

/*
 * Retourne le sprite du tile
 */
sf::Sprite Tile::getTile()
{
    return m_tile;
}

/*
 * Retourne l'index du tile
 */
int Tile::getIndex()
{
    return m_index;
}

/*
 * Assigne une couleur rgb(a) au tile
 */
void Tile::setColor(int r, int g, int b, int a)
{
    m_tile.setColor(sf::Color(r, g, b, a));
}

/*
 * Assigne une couleur sf::Color au tile
 */
void Tile::setColor(sf::Color color)
{
    m_tile.setColor(color);
}

/*
 * Retourne l'adresse du tile à la position (x,y)
 */
sf::Sprite *Tile::draw(int x, int y)
{
    m_tile.setPosition(sf::Vector2f(x, y));
    
    return &m_tile;
}