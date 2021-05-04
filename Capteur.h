#ifndef PROJETCAPTEUR_CAPTEUR_H
#define PROJETCAPTEUR_CAPTEUR_H

#include <list>
#include <string>
#include <ostream>
#include "Mesure.h"

class Capteur
{

public:

    Mesure* obtenirMesureDate(string &date) const;

    double* obtenirMoyenne(string &dateDebut, string &dateFin) const;

    void desactiverCapteur();

    void setDerniereMesure(string &derniereMes) {
        derniereMesure = derniereMes;
    }

    void addMesure(Mesure &mesure) {
        listeMesures.push_back(mesure);
    }

    friend ostream &operator<<(ostream &os, const Capteur &capteur);

    Capteur(const string &capteurId, double longitude, double latitude, bool capteurPrive, const string &premiereMesure);

    virtual ~Capteur ( );

private:
    string capteurID;
    bool fiable;
    double longitude;
    double latitude;
    bool capteurPrive;
    string premiereMesure;
    string derniereMesure;
    list<Mesure> listeMesures;
};

#endif
