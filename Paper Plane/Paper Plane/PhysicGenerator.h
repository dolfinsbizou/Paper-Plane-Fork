//
//  PhysicGenerator.h
//  Paper Plane
//
//  Créé le 21/12/2013.
//  Header de PhysicGenerator.cpp
//

#ifndef __Paper_Plane__PhysicGenerator__
#define __Paper_Plane__PhysicGenerator__

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Tilemap.h"

class PhysicGenerator
{
public:
    
    PhysicGenerator(Tilemap tm);
    void addObstacle();
    std::vector<int> getCurrLine();
    Tilemap getTilemap();
    int getPos();
    void setup();
    void reset();
    int getStep();
    std::vector<int> getObstacleVector();
    
private:
    
    Tilemap m_tm; // La tilemap que génère le générateur
    unsigned int m_currLine; // Le nombre actuel de lignes
    int m_numSteps; // Contient le nombre d'étapes jouées (y compris celle en cours)
    int m_currObstaclesStep; // Contient le nombre d'obstacles générés pour l'étape en cours
    bool m_lastObstacleAtLeft; // Est vrai si le dernier obstacle était à gauche
    int m_lastObstacleSize; // La taille du dernier obstacle
    std::vector<int> m_obstacleLines; //Stocke les lignes comportant un début d'obstacle pour le scoring)
};

#endif /* defined(__Paper_Plane__PhysicGenerator__) */