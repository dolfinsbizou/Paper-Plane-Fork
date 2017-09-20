//
//  BackgroundGenerator.h
//  Paper Plane
//
//  Créé le 18/12/2013.
//  Header de BackgroundGenerator.cpp
//

#ifndef __Paper_Plane__BackgroundGenerator__
#define __Paper_Plane__BackgroundGenerator__

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Tilemap.h"

class BackgroundGenerator
{
public:
    
    BackgroundGenerator(Tilemap tm);
    void createLine();
    std::vector<int> getCurrLine();
    Tilemap getTilemap();
    int getPos();
    void setup();
    void reset();
    
private:
    
    Tilemap m_tm; // La tilemap que génère le générateur
    unsigned int m_currLine; // Le nombre actuel de lignes
    bool m_isWindowBeingCreated; // vaut vrai si une fenêtre de décor est en cours de création
    int m_windowLine; //ligne de fenêtre en cours de génération (1: haut, 2: milieu, 3:bas)
    int m_windowPos; //valeur de la colonne dans laquelle se situe le coin supérieur gauche de la fenêtre de décoration
    int m_lineSinceLastWindow; //nombre de lignes écoulées depuis la dernière fenêtre;
};

#endif /* defined(__Paper_Plane__BackgroundGenerator__) */
