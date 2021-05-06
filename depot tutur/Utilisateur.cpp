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



Utilisateur::Utilisateur(const string & utilisateurID) {
    Utilisateur::utilisateurID = utilisateurID;
    points = 0;
    gagnePoints = true;
}


Utilisateur::~Utilisateur ( )
{

}

void Utilisateur::addCapteur(Capteur capteur) {
    listeCapteurs.push_back(capteur);
}

void Utilisateur::afficherCapteurs() {
    for(list<Capteur>::iterator it = listeCapteurs.begin(); it != listeCapteurs.end(); it++) {
        cout << *it << endl;
    }
}

ostream &operator<<(ostream &os, const Utilisateur &utilisateur) {
    os << "UserID: " << utilisateur.utilisateurID << " points: " << utilisateur.points << " liste de capteurs: " ;
    return os;
}




//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées