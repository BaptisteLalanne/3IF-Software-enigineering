#ifndef PROJETCAPTEUR_SERVICE_H
#define PROJETCAPTEUR_SERVICE_H

#include <list>
#include "Capteur.h"
#include "Mesure.h"
#include "Utilisateur.h"
#include <iostream>

using namespace std;

class Service {

public:

    double distanceDeuxPointsTerre(double latitudeA, double longitudeA, double latitudeB, double longitudeB);

    double obtenirDensiteRegion(list<Capteur> listeDesCapteurs, double longitude, double latitude, double rayonRegion,
                                double rayonMesCapteur);

    void verifierFonctionnementCapteur();

    void addListeCapteurs(Capteur &capteur);

    list<Capteur> &getListeCapteurs();

    void addListeUtilisateurs(Utilisateur &utilisateur);

    void calculerMoyenneQualiteAir(double longitude, double latitude, double rayon, string dateDebut, string dateFin);

    list<Capteur>
    obtenirCapteursRegion(double centreRegionLongitude, double centreRegionLatitude, string dateDebut, string dateFin,
                          double rayonMinRegion, double rayonMaxRegion);

    Service();

    virtual ~Service();

private:

    list<Capteur> listeCapteurs;
    list<Utilisateur> listeUtilisateurs;

};

#endif