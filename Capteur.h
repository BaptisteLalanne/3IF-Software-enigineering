#ifndef PROJETCAPTEUR_CAPTEUR_H
#define PROJETCAPTEUR_CAPTEUR_H

#include <list>
#include <string>
#include <ostream>
#include <iostream>
#include "Mesure.h"

class Utilisateur;

class Capteur {

public:

    Mesure *obtenirMesureDate(string &date);

    double *obtenirMoyenne(string &dateDebut, string &dateFin);

    void desactiverCapteur();

    string &getId();

    bool getFiable();

    double getLongitude();

    double getLatitude();

    string &getPremiereMesure();

    string &getDerniereMesure();

    void setUtilisateur(Utilisateur *utilisateur);

    void setDerniereMesure(string &derniereMes);

    void addMesure(Mesure &mesure);

    list <Mesure> &getListeMesures();

    Utilisateur *getUtilisateurPrive();

    Capteur(const string &capteurId, double longitude, double latitude, const string &premiereMesure);

    virtual ~Capteur();

    friend ostream &operator<<(ostream &os, const Capteur &capteur);

    bool operator==(const Capteur &rhs) const;

private:
    string capteurID;
    bool fiable;
    double longitude;
    double latitude;
    Utilisateur *utilisateurPrive;
    string premiereMesure;
    string derniereMesure;
    list <Mesure> listeMesures;


};

#endif
