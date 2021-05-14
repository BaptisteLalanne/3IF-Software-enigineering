
#ifndef PROJETCAPTEUR_UTILISATEUR_H
#define PROJETCAPTEUR_UTILISATEUR_H

#include <string>
#include "Capteur.h"

class Utilisateur
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void donnerPoints();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void empecherGagnerPoints() {
        gagnePoints = false;
    }
//-------------------------------------------- Constructeurs - destructeur


    Utilisateur(const string & utilisateurID);

    virtual ~Utilisateur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void addCapteur(Capteur & capteur);

    friend ostream &operator<<(ostream &os, const Utilisateur &utilisateur);

    void afficherCapteurs();

//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Méthodes privées

//----------------------------------------------------- Attributs privés
    string utilisateurID;
    int points;
    bool gagnePoints;
    list<Capteur> listeCapteurs;
};

//-------------------------------- Autres définitions dépendantes de <Utilisateur>

#endif // PROJETCAPTEUR_UTILISATEUR_H
