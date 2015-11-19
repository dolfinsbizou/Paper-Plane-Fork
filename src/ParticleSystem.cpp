//
//  ParticleSystem.cpp
//  Paper Plane
//
//  Créé le 19/01/2014.
//  Système de particules
//

#include "ParticleSystem.h"

using namespace std;
using namespace pSystem;

/*
 * Constructeur de classe
 * qty: quantité de particules
 * loc: position de l'emitter
 * ts: le tileset
 * tsLineDesc: description ligne à ligne du tileset
 * lifespan: durée de vie d'une particule
 * frameLife: durée d'une frame
 */
ParticleSystem::ParticleSystem(unsigned int qty, sf::Vector2f loc, Tileset &ts, std::vector<int> const&tsLineDesc, sf::Time lifespan, sf::Time frameLife, pSystem::ParticleType pType): m_particles(qty), m_pType(pType), m_pos(loc), m_ts(&ts), m_lifespan(lifespan), m_frameLife(frameLife)
{
    //On vide le vector de tiles s'il ne l'est pas déjà
    while(m_frames.size() > 0)
    {
        m_frames.pop_back();
    }
    
    //Maintenant pour chaque case du vector (<=> pour chaque ligne du tileset)
    for(int i = 0 ; i < tsLineDesc.size() ; i++)
    {
        //Pour chaque case de la ligne i du tileset
        for(int j = 0 ; j < tsLineDesc[i] ; j++)
        {
            Tile temp(*m_ts, -1, i+1, j+1);//petit tile temporaire...
            m_frames.push_back(temp);//que l'on copie dans une nouvelle case de m_frames
        }
    }
    
    init();
}

/*
 * Initialise les particules
 */
void ParticleSystem::init()
{
    for(int i = 0; i < m_particles.size() ; i++)
    {
        m_particles[i].p_lifespan = sf::Time::Zero;
        if(m_pType == UNDEAD || m_pType == LIMITED)
        {
            setParticle(i);
        }
    }
}

/*
 * Redéfinit la position de l'emitter en (x;y)
 */
void ParticleSystem::setLocation(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
}

/*
 * Déplace l'emitter selon un vecteur (w;h)
 */
void ParticleSystem::move(int w, int h)
{
    m_pos.x += w;
    m_pos.y += h;
}

/*
 * Réinitialise la particule d'index i
 */
void ParticleSystem::setParticle(int i)
{
    m_particles[i].p_pos = m_pos;
    m_particles[i].p_speed = sf::Vector2f((rand() % 250) - 125, (rand() % 160) - 60);
    m_particles[i].p_acceleration = sf::Vector2f(0, 80);
    m_particles[i].p_frameLife = m_frameLife;
    m_particles[i].p_lifespan = m_lifespan + sf::seconds(((rand() % ((int)(m_lifespan.asSeconds())/2)) - m_lifespan.asSeconds()/4));
    m_particles[i].p_frameIndex = 1+ (rand() % 8);
}

void ParticleSystem::display(sf::RenderWindow &w)
{
    for(int i = 0; i < m_particles.size() ; i++)
    {
        if((m_pType == MORTAL) || (m_pType == LIMITED && m_particles[i].p_lifespan > sf::Time::Zero) || (m_pType == UNDEAD))
        {
            if(m_particles[i].p_lifespan <= m_lifespan)
            {
                w.draw(*m_frames[m_particles[i].p_frameIndex - 1].draw(m_particles[i].p_pos.x, m_particles[i].p_pos.y));
            }
        }
    }
}

/*
 * Met à jour le système de particule selon le temps écoulé timeElapsed
 */
void ParticleSystem::update(sf::Time timeElapsed)
{
    unsigned int numFrames = m_frames.size();
    
    for (int i = 0 ; i < m_particles.size() ; i++)
    {
        Particle *p = &m_particles[i]; //On récupère l'adresse de la particule n°i
        
        p->p_lifespan -= timeElapsed;
        p->p_frameLife -= timeElapsed;
        
        if((p->p_lifespan <= sf::Time::Zero) && (m_pType == MORTAL))
        {
            setParticle(i);
        }
        
        if(p->p_lifespan <= m_lifespan)
        {
            //On actualise la position de la particule
            p->p_speed.x += p->p_acceleration.x  * timeElapsed.asSeconds();
            p->p_speed.y += p->p_acceleration.y  * timeElapsed.asSeconds();
            p->p_pos.x += p->p_speed.x * timeElapsed.asSeconds();
            p->p_pos.y += p->p_speed.y * timeElapsed.asSeconds();
        }
        
        //On actualise sa frame si besoin
        if(p->p_frameLife <= sf::Time::Zero)
        {
            p->p_frameLife = m_frameLife;
            if(p->p_frameIndex >= numFrames)
            {
                p->p_frameIndex = 1;
            }
            else
            {
                p->p_frameIndex++;
            }
        }
    }
}