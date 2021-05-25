#ifndef PROJETCAPTEUR_CAPTEUR_H
#define PROJETCAPTEUR_CAPTEUR_H

#include <list>
#include <string>
#include <ostream>
#include "Mesure.h"

class Utilisateur;

class Capteur
{

public:

    Mesure* obtenirMesureDate(string & date);

    double* obtenirMoyenne(string &dateDebut, string &dateFin);

    void desactiverCapteur();

    string getId() {
        return capteurID;
    }
    bool getFiable() {
        return fiable;
    }

    double getLongitude() {
        return longitude;}


        double getLatitude(){
        return latitude;
    }

    string getPremiereMesure(){
        return premiereMesure;
    }

    string getDerniereMesure() {
        return derniereMesure;
    }

    void setUtilisateur(Utilisateur * utilisateur) {
        utilisateurPrive = utilisateur;
    }

    void setDerniereMesure(string &derniereMes) {
        derniereMesure = derniereMes;
    }

    void addMesure(Mesure &mesure) {
        listeMesures.push_back(mesure);
    }

    list<Mesure>& getListeMesures() {
        return listeMesures;
}

    Utilisateur* getUtilisateurPrive(){
        return utilisateurPrive;
    }

    Capteur(const string &capteurId, double longitude, double latitude, const string &premiereMesure);

    virtual ~Capteur ( );

    friend ostream &operator<<(ostream &os, const Capteur &capteur);

    void afficherListeMesures();

private:
    string capteurID;
    bool fiable;
    double longitude;
    double latitude;
    Utilisateur * utilisateurPrive;
    string premiereMesure;
    string derniereMesure;
    list<Mesure> listeMesures;


};

#endif
