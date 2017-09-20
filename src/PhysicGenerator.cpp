//
//  PhysicGenerator.cpp
//  Paper Plane
//
//  Créé le 21/12/2013.
//  Génération des obstacles physiques
//

#include "PhysicGenerator.h"

using namespace std;

/*
 * Constructeur de classe
 * tm : tilemap de départ du générateur
 */
PhysicGenerator::PhysicGenerator(Tilemap tm): m_tm(tm), m_currLine(tm.getHeight()), m_numSteps(0), m_currObstaclesStep(0), m_lastObstacleAtLeft(false), m_lastObstacleSize(0)
{
    
}

/*
 * Ajoute l'obstacle et les 5 lignes qui vont avec
 */
void PhysicGenerator::addObstacle()
{
    int obstacleSize = 0;
    int doubleObstacle = 0;
    vector<int> line, line2;
    
    line.push_back(0);
    line.push_back(2);
    
    if(m_currObstaclesStep >= 18)
    {
        m_obstacleLines.push_back(m_currLine-1);
        m_tm.addLine({0, 2, 31, 31, 31, 32, 0, 0, 0, 0, 30, 31, 31, 31, 3, 0});
        m_tm.addLine({0, 2, 0, 0, 0, 35, 0, 0, 0, 0, 33, 0, 0, 0, 3, 0});
        m_tm.addLine({0, 2, 0, 0, 0, 35, 0, 0, 0, 0, 33, 0, 0, 0, 3, 0});
        m_tm.addLine({0, 2, 0, 0, 0, 35, 0, 0, 0, 0, 33, 0, 0, 0, 3, 0});
        m_tm.addLine({0, 2, 37, 37, 37, 38, 0, 0, 0, 0, 36, 37, 37, 37, 3, 0});
        
        m_currLine+=5;
    }
    else
    {
        m_obstacleLines.push_back(m_currLine-1);
        obstacleSize = (rand() % 2) + m_lastObstacleSize; // Taille de l'obstacle actuel = taille du dernier obstacle, auquel on rajoute au hasard jusqu'à +2
        doubleObstacle = rand() % 15; //1/15 chances d'avoir un double obstacle
        switch(m_numSteps)
        {
            case 1: // 12 + 2 au début (le début généré comporte déjà un obstacle, on ajoute ensuite les deux lignes générées avant l'obstacle suivant) + 17 obstacles * 5 (4 entre chaque obstacle + 1 pour l'obstacle) + 3 (le 19e obstacle + les deux lignes avant l'inter étape) + 5*10 pour l'inter étape = 152 lignes
                
                if(doubleObstacle < 12)
                {
                    if(m_lastObstacleAtLeft)
                    {
                        for (int i = 0 ; i < (12 - obstacleSize) ; i++)
                        {
                            line.push_back(0);
                        }
                        
                        line.push_back(20);
                        
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(21);
                        }
                        m_lastObstacleAtLeft = false;
                    }
                    else
                    {
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(21);
                        }
                        
                        line.push_back(22);
                        
                        for (int i = 0 ; i < (12 - obstacleSize) ; i++)
                        {
                            line.push_back(0);
                        }
                        
                        m_lastObstacleAtLeft = true;
                    }
                }
                else
                {
                    if(m_lastObstacleAtLeft)
                    {
                        for (int i = 0 ; i < (9 - obstacleSize) ; i++)
                        {
                            line.push_back(21);
                        }
                        
                        line.push_back(22);
                        line.push_back(0);
                        line.push_back(0);
                        line.push_back(20);
                        
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(21);
                        }
                        m_lastObstacleAtLeft = false;
                    }
                    else
                    {
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(21);
                        }
                        
                        line.push_back(22);
                        line.push_back(0);
                        line.push_back(0);
                        line.push_back(20);
                        
                        for (int i = 0 ; i < (9 - obstacleSize) ; i++)
                        {
                            line.push_back(21);
                        }
                        
                        m_lastObstacleAtLeft = true;
                    }
                }
                
                line.push_back(3);
                line.push_back(0);
                
                m_tm.addLine(line);
                m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
                m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
                break;
            case 2: // 2 libres au début + 18 obstacles * 5 + 3 (le 19e obstacle + les deux lignes avant l'inter étape) + 5*10 pour l'inter étape = 145 lignes
            case 3:
                if(doubleObstacle < 12)
                {
                    if(m_lastObstacleAtLeft)
                    {
                        for (int i = 0 ; i < (12 - obstacleSize) ; i++)
                        {
                            line.push_back(0);
                        }
                        
                        line.push_back(40);
                        
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(41);
                        }
                        m_lastObstacleAtLeft = false;
                    }
                    else
                    {
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(41);
                        }
                        
                        line.push_back(42);
                        
                        for (int i = 0 ; i < (12 - obstacleSize) ; i++)
                        {
                            line.push_back(0);
                        }
                        
                        m_lastObstacleAtLeft = true;
                    }
                }
                else
                {
                    if(m_lastObstacleAtLeft)
                    {
                        for (int i = 0 ; i < (9 - obstacleSize) ; i++)
                        {
                            line.push_back(41);
                        }
                        
                        line.push_back(42);
                        line.push_back(0);
                        line.push_back(0);
                        line.push_back(40);
                        
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(41);
                        }
                        m_lastObstacleAtLeft = false;
                    }
                    else
                    {
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(41);
                        }
                        
                        line.push_back(42);
                        line.push_back(0);
                        line.push_back(0);
                        line.push_back(40);
                        
                        for (int i = 0 ; i < (9 - obstacleSize) ; i++)
                        {
                            line.push_back(41);
                        }
                        
                        m_lastObstacleAtLeft = true;
                    }
                }
                
                line.push_back(3);
                line.push_back(0);
                
                m_tm.addLine(line);
                m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
                m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
                break;
            default: // 2 libres au début + 18 obstacles * 6 + 4 (le 19e obstacle + les deux lignes avant l'inter étape) + 5*10 pour l'inter étape = 162 lignes
                
                line2.push_back(0);
                line2.push_back(2);
                
                if(doubleObstacle < 12)
                {
                    if(m_lastObstacleAtLeft)
                    {
                        for (int i = 0 ; i < (12 - obstacleSize) ; i++)
                        {
                            line.push_back(0);
                            line2.push_back(0);
                        }
                        
                        line.push_back(30);
                        line2.push_back(36);
                        
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(31);
                            line2.push_back(37);
                        }
                        m_lastObstacleAtLeft = false;
                    }
                    else
                    {
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(31);
                            line2.push_back(37);
                        }
                        
                        line.push_back(32);
                        line2.push_back(38);
                        
                        for (int i = 0 ; i < (12 - obstacleSize) ; i++)
                        {
                            line.push_back(0);
                            line2.push_back(0);
                        }
                        
                        m_lastObstacleAtLeft = true;
                    }
                }
                else
                {
                    if(m_lastObstacleAtLeft)
                    {
                        for (int i = 0 ; i < (9 - obstacleSize) ; i++)
                        {
                            line.push_back(31);
                            line2.push_back(37);
                        }
                        
                        line.push_back(32);
                        line2.push_back(38);
                        line.push_back(0);
                        line2.push_back(0);
                        line.push_back(0);
                        line2.push_back(0);
                        line.push_back(30);
                        line2.push_back(36);
                        
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(31);
                            line2.push_back(37);
                        }
                        m_lastObstacleAtLeft = false;
                    }
                    else
                    {
                        for (int i = 0 ; i < obstacleSize - 1 ; i++)
                        {
                            line.push_back(31);
                            line2.push_back(37);
                        }
                        
                        line.push_back(32);
                        line2.push_back(38);
                        line.push_back(0);
                        line2.push_back(0);
                        line.push_back(0);
                        line2.push_back(0);
                        line.push_back(30);
                        line2.push_back(36);
                        
                        for (int i = 0 ; i < (9 - obstacleSize) ; i++)
                        {
                            line.push_back(31);
                            line2.push_back(37);
                        }
                        
                        m_lastObstacleAtLeft = true;
                    }
                }
                
                line.push_back(3);
                line2.push_back(3);
                line.push_back(0);
                line2.push_back(0);
                
                m_tm.addLine(line);
                m_tm.addLine(line2);
                m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
                break;
        }
        if (m_currObstaclesStep != 17)
        {
            m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
            m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
            m_currLine+=5;
        }
        else if(m_numSteps > 3 && m_currObstaclesStep == 17)
        {
            m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
            m_currLine+=4;
        }
        else
        {
            m_currLine+=3;
        }
    }
    
    m_currObstaclesStep++;
    if(m_currObstaclesStep >= 29)
    {
        m_currObstaclesStep = 0;
        m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
        m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
        m_currLine+=2;
        m_numSteps++;
    }
}

/*
 * Recrée le background generator avec des paramètres prédéfinis
 */
void PhysicGenerator::setup()
{
    reset();
    
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 21, 21, 21, 21, 21, 22, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_tm.addLine({0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0});
    m_currLine = 14;
    m_currObstaclesStep = 1;
    m_numSteps = 1;
    m_lastObstacleSize = 6;
    m_lastObstacleAtLeft = true;
    m_obstacleLines.push_back(10);
}

/*
 * Recrée un background generator vide
 */
void PhysicGenerator::reset()
{
    m_tm.clean();
    m_currLine = 0;
    m_numSteps = 0;
    m_currObstaclesStep = 0;
    m_lastObstacleAtLeft = false;
    m_lastObstacleSize = 0;
    
    int steps = m_obstacleLines.size();
    for (int i = 0 ; i < steps ; i++)
    {
        m_obstacleLines.pop_back();
    }
}

/*
 * Retourne la ligne actuelle
 */
vector<int> PhysicGenerator::getCurrLine()
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
int PhysicGenerator::getPos()
{
    return m_currLine;
}

/*
 * Retourne toute la tilemap
 */
Tilemap PhysicGenerator::getTilemap()
{
    return m_tm;
}

/*
 * Retourne l'étape en cours
 */
int PhysicGenerator::getStep()
{
    return m_numSteps;
}

/*
 * Retourne le vector d'obstacles (pour le scoring)
 */
vector<int> PhysicGenerator::getObstacleVector()
{
    return m_obstacleLines;
}
