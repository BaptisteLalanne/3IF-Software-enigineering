/*************************************************************************
                           Utilisateur  -  description
                             -------------------
    début                : 04/05/21
    copyright            : (C) 2021 par Lalanne Baptiste, El Rifai Rami,
	                 Rossello-Poulet Arthur, Bois Capucine
*************************************************************************/

//---------- Réalisation de la classe <Utilisateur> (fichier Utilisateur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Utilisateur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeurs - destructeur



Utilisateur::Utilisateur (string utilisateurID)
{
    Utilisateur::utilisateurID = utilisateurID;
    points = 0;
    gagnePoints = true;
} //----- Fin de Utilisateur


Utilisateur::~Utilisateur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Utilisateur>" << endl;
#endif
} //----- Fin de ~Utilisateur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées