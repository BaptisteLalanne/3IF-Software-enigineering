
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
#include <iostream>
using namespace std;

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



    int calculerMoyenneQualiteAir(double Longitude, double Latitude, double rayon, string dateDebut, string dateFin);


    list<Capteur> obtenirCapteursRegion(double longitude, double latitude, string dateDeb, string dateFin, double rayonMax, double rayonMin);

    */
    double distanceDeuxPointsTerre(double latitudeA, double longitudeA,double latitudeB,double longitudeB);
    double obtenirDensiteRegion(list<Capteur> listeDesCapteurs,double longitude, double latitude, double rayonRegion);
    void verifierFonctionnementCapteur();

    void addListeCapteurs(Capteur & capteur) {
        listeCapteurs.push_back(capteur);
    }

    list<Capteur>& getListeCapteurs() {
        return listeCapteurs;
    }

    void addListeUtilisateurs(Utilisateur & utilisateur) {
        listeUtilisateurs.push_back(utilisateur);
    }

    list<Utilisateur>& getListeUtilisateurs() {
        return listeUtilisateurs;
    }

    void calculerMoyenneQualiteAir(double longitude, double latitude, double rayon, string dateDebut, string dateFin);

    list<Capteur>
    obtenirCapteursRegion(double centreRegionLongitude, double centreRegionLatitude, string dateDebut, string dateFin,
                          double rayonMaxRegion, double rayonMinRegion);

    Service ();

    virtual ~Service ( );

//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    list<Capteur> listeCapteurs;
    list<Utilisateur> listeUtilisateurs;



};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // PROJETCAPTEUR_SERVICE_H
