//
//  Entity.cpp
//  Paper Plane
//
//  Créé le 17/12/2013.
//  Stocke les données relatives à un joueur
//

#include "Entity.h"

using namespace std;

/*
 * Constructeur de classe
 * ts : le tileset
 * tsLineDesc : un vector stockant la description de chaque ligne du tileset (chaque case du vector donne le nombre de frames de la ligne)
 * index : l'index de l'entité
 */
Entity::Entity(Tileset &ts, std::vector<int> const&tsLineDesc, int index, vector<sf::Vector2i> const&collisionPoints): m_index(index), m_v(0, 0), m_x(0), m_y(0), m_ts(&ts), m_currFrame(1), m_collisionPoint(collisionPoints)
{
    setupFrames(tsLineDesc);
}

/*
 * Retourne un vecteur de la position
 */
sf::Vector2i Entity::getPos()
{
    return sf::Vector2i(m_x, m_y);
}

/*
 * Retourne un vecteur de la vitesse
 */
sf::Vector2i Entity::getSpeed()
{
    return sf::Vector2i(m_v.x, m_v.y);
}

/*
 * Redéfinit la position de l'entité
 */
void Entity::setPos(int x, int y)
{
    m_x = x;
    m_y = y;
}

/*
 * Redéfinit la vitesse de l'entité
 */
void Entity::setSpeed(int i, int j)
{
    m_v.x = i;
    m_v.y = j;
}

/*
 * Bouge l'entité en utilisant comme facteur son vecteur de mouvement
 */
void Entity::move()
{
    m_x+=m_v.x;
    m_y+=m_v.y;
}

/*
 * Définit la frame actuelle comme étant la frame d'id i
 */
void Entity::setFrame(unsigned int i)
{
    if(i > 0 && i < (m_frames.size() + 1))
    {
        m_currFrame = i;
    }
}

/*
 * Retourne la frame actuelle
 */
Tile *Entity::getFrame()
{
    return &m_frames[m_currFrame-1];
}

/*
 * Retourne l'id de frame actuelle
 */
int Entity::getFrameId()
{
    return m_currFrame;
}

/*
 * Retourne l'index du tile
 */
int Entity::getIndex()
{
    return m_index;
}

/*
 * Retourne l'adresse de la frame actuelle
 */
sf::Sprite *Entity::draw()
{
    return m_frames[m_currFrame-1].draw(m_x, m_y);
}

/*
 * Retourne le pixel collidable frame actuelle
 */
sf::Vector2i Entity::getCollisionPoint()
{
    return m_collisionPoint[m_currFrame-1];
}

/*
 * Fonction technique appelée impérativement par le constructeur, (re)découpe le tileset en tiles
 * desc : la description de chaque ligne du tileset
 */
void Entity::setupFrames(std::vector<int> const&desc)
{
    //On vide le vector de tiles s'il ne l'est pas déjà
    while(m_frames.size() > 0)
    {
        m_frames.pop_back();
    }
    
    //Maintenant pour chaque case du vector (<=> pour chaque ligne du tileset)
    for(unsigned int i = 0 ; i < desc.size() ; i++)
    {
        //Pour chaque case de la ligne i du tileset
        for(int j = 0 ; j < desc[i] ; j++)
        {
            Tile temp(*m_ts, -1, i+1, j+1);//petit tile temporaire...
            m_frames.push_back(temp);//que l'on copie dans une nouvelle case de m_frames
        }
    }
}
