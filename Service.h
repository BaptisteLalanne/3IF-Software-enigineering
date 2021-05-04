
/*************************************************************************
                           Service  -  description
                             -------------------
    début                : 04/05/21
    copyright            : (C) 2021 par Lalanne Baptiste, El Rifai Rami,
	                 Rossello-Poulet Arthur, Bois Capucine
*************************************************************************/

//---------- Interface de la classe <Service> (fichier Service.h) ----------------
#ifndef PROJETCAPTEUR_SERVICE_H
#define PROJETCAPTEUR_SERVICE_H
#include <list>

//--------------------------------------------------- Interfaces utilisées
#include "Capteur.h"
#include "Mesure.h"
#include "Utilisateur.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Service>
//
//
//------------------------------------------------------------------------

class Service
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
/*
    void seConnecter(string utilisateurID);

    void verifierFonctionnementCapteur();

    int calculerMoyenneQualiteAir(double Longitude, double Latitude, double rayon, string dateDebut, string dateFin);


    list<Capteur> obtenirCapteursRegion(double longitude, double latitude, string dateDeb, string dateFin, double rayonMax, double rayonMin);

    double obtenirDensiteRegion(list<Capteur> listeCapteurs, double longitude, double latitude);
*/

    Service ();

    virtual ~Service ( );

//------------------------------------------------------------------ PRIVE
    list<Capteur> listeCapteurs;
    list<Utilisateur> listeUtilisateurs;
    list<Mesure> listeDonnees;
private:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés


};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // PROJETCAPTEUR_SERVICE_H
