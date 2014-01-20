//
//  Tilemap.cpp
//  Paper Plane
//
//  Créé le 16/12/2013.
//  Données d'une Tilemap, c.à.d stocke les données de chaque case de la map
//

#include "Tilemap.h"

using namespace std;

/*
 * Constructeur de classe
 * map : le vecteur 2D utilisé pour remplir la tilemap
 */
Tilemap::Tilemap(vector<vector<int>> &map)
{
    m_map = map;
    m_width = m_map.size();
    m_height = m_map[0].size();
}

/*
 * Constructeur de classe par défaut
 */
Tilemap::Tilemap(): m_width(0), m_height(0)
{
    
}

/*
 * Ajoute une ligne "line" à la tilemap.
 */
bool Tilemap::addLine(std::vector<int> const&line)
{
    if(line.size() == m_width || m_height == 0) //Si la ligne fait la bonne taille OU que c'est la première ligne
    {
        if (m_height == 0) //Si c'est la première ligne du tableau, alors on crée x=line.size() colonnes vides
        {
            vector<int> voidV; //cette ligne est dégueulasse :x
            m_width = line.size();
            for (int i = 0 ; i < m_width ; i++)
            {
                m_map.push_back(voidV);
            }
        }
        
        //Puis on ajoute une case à chaque colonne pour faire la ligne
        for(int i = 0 ; i < line.size() ; i++)
        {
            m_map[i].push_back(line[i]);
        }
        
        m_height++; //Une ligne a été créée, on incrémente l'attribut m_height
        
        return true;
    }
    else
    {
        cout << "ERREUR CRITIQUE : la ligne doit faire la même taille que les lignes déjà existantes.";
        return false;
    }
}

/*
 * Fonction de debug : affiche dans la console la tilemap
 */
void Tilemap::debugDisplayTilemap()
{
    for(int i = 0 ; i < m_height ; i++)
    {
        for(int j = 0 ; j < m_width ; j++)
        {
            cout << m_map[j][i] << "   ";
        }
        cout << endl << endl;
    }
    cout << "width: " << m_width << endl;
    cout << "height: " << m_height << endl;
}

/*
 * Retourne la largeur en colonnes de la tilemap
 */
int Tilemap::getWidth()
{
    return m_width;
}

/*
 * Retourne la hauteur en lignes de la tilemap
 */
int Tilemap::getHeight()
{
    return m_height;
}

/*
 * Lit la donnée aux coordonnées (i, j)
 */
int Tilemap::readPos(int i, int j)
{
    return m_map[i][j];
}

/*
 * Vide la tilemap
 */
void Tilemap::clean()
{
    int steps = m_width;
    for (int i = 0 ; i < steps ; i++)
    {
        m_map.pop_back();
    }
    m_width = 0;
    m_height = 0;
}