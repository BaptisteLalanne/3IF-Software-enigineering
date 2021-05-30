#ifndef PROJETCAPTEUR_UTILISATEUR_H
#define PROJETCAPTEUR_UTILISATEUR_H

#include <string>
#include "Capteur.h"

class Utilisateur {

public:

    void donnerPoints();

    void empecherGagnerPoints();

    Utilisateur(const string &utilisateurID);

    virtual ~Utilisateur();

    void addCapteur(Capteur &capteur);

    friend ostream &operator<<(ostream &os, const Utilisateur &utilisateur);

private:

    string utilisateurID;
    int points;
    bool gagnePoints;
    list <Capteur> listeCapteurs;
};

#endif
