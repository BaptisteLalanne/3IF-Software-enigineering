using namespace std;
#include <iostream>
#include <algorithm>
#include <cstring>

#include "Capteur.h"

Capteur::Capteur(const string &capteurId, double longitude, double latitude, const string &premiereMesure) : capteurID(capteurId), fiable(true),
                                                                                                            longitude(longitude), latitude(latitude),
                                                                                                            utilisateurPrive(nullptr),
                                                                                                            premiereMesure(premiereMesure),
                                                                                                            derniereMesure(""){}


Capteur::~Capteur ( )
{
}

void Capteur::desactiverCapteur() {
    fiable = false;
}

double* Capteur::obtenirMoyenne(string &dateDebut, string &dateFin) {
    static double moyenne[4];
    for (double & i : moyenne) {
        i = 0;
    }

    int nbMesures = 0;

    list<Mesure>::iterator it = listeMesures.begin();

    while(it!=listeMesures.end() && strcmp((it->getDateMesure()).c_str(), dateDebut.c_str()) != 0) {
        it++;
    }

    while (it!=listeMesures.end() && strcmp(it->getDateMesure().c_str(), dateFin.c_str()) != 0){
        moyenne[0] += it->getOzone();
        moyenne[1] += it->getDioxydeAzote();
        moyenne[2] += it->getDioxydeSoufre();
        moyenne[3] += it->getParticulesFines();
        nbMesures++;
        it++;
    }

    int i;
    for (i = 0; i<4; i++) {
        moyenne[i] /= nbMesures;
    }

    return moyenne;
}

Mesure* Capteur::obtenirMesureDate(string & date) {
    //auto it = std::find_if(listeMesures.begin(), listeMesures.end(), [](Mesure & obj, string & date){return obj.getDateMesure() == date;});
    for (auto & mesure : listeMesures) {
        if(mesure.getDateMesure() == date) {
            return &mesure;
        }
    }
    return nullptr;
}

ostream &operator<<(ostream &os, const Capteur &capteur) {
    os << "capteurID: " << capteur.capteurID << " fiable: " << capteur.fiable << " longitude: " << capteur.longitude
       << " latitude: " << capteur.latitude << " utilisateurPrive: " << capteur.utilisateurPrive << " premiereMesure: "
       << capteur.premiereMesure  << " derniereMesure: " << capteur.derniereMesure;
    return os;
}

void Capteur::afficherListeMesures() {
    for(list<Mesure>::iterator it = listeMesures.begin(); it != listeMesures.end(); it++) {
        cout << *it << endl;
    }
}
