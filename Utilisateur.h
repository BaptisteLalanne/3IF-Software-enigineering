
#ifndef PROJETCAPTEUR_UTILISATEUR_H
#define PROJETCAPTEUR_UTILISATEUR_H

#include <string>

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

    void empecherGagnerPoints();
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    Utilisateur ( const Utilisateur & unUtilisateur );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Utilisateur ();
    // Mode d'emploi :
    //
    // Contrat :
    //

    Utilisateur(const string utilisateurID);

    virtual ~Utilisateur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

private:
//----------------------------------------------------- Méthodes privées

//----------------------------------------------------- Attributs privés
    string utilisateurID;
    int points;
    bool gagnePoints;
};

//-------------------------------- Autres définitions dépendantes de <Utilisateur>

#endif // PROJETCAPTEUR_UTILISATEUR_H
