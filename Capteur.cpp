using namespace std;
#include <iostream>
#include <algorithm>

#include "Capteur.h"

Capteur::Capteur(const string &capteurId, double longitude, double latitude, bool capteurPrive, const string &premiereMesure) : capteurID(capteurId), fiable(true),
                                                                                                            longitude(longitude), latitude(latitude),
                                                                                                            capteurPrive(capteurPrive),
                                                                                                            premiereMesure(premiereMesure),
                                                                                                            derniereMesure(""){}


Capteur::~Capteur ( )
{
}

void Capteur::desactiverCapteur() {
    fiable = false;
}

double* Capteur::obtenirMoyenne(string &dateDebut, string &dateFin) const {
    double moyenne[4];
    int nbMesures = 0;

    auto itDebut = find_if(listeMesures.begin(), listeMesures.end(), [&dateDebut](const Mesure& mesure){return mesure.getDateMesure() == dateDebut;});
    auto itFin = find_if(listeMesures.begin(), listeMesures.end(), [&dateFin](const Mesure& mesure){return mesure.getDateMesure() == dateFin;});

    for (auto it = itDebut; it != next(itFin); it++) {
        moyenne[0] += it->getOzone();
        moyenne[1] += it->getDioxydeAzote();
        moyenne[2] += it->getDioxydeSoufre();
        moyenne[3] += it->getParticulesFines();
        nbMesures++;
    }

    int i;
    for (i = 0; i<4; i++) {
        moyenne[i] /= nbMesures;
    }

    return moyenne;
}

Mesure* Capteur::obtenirMesureDate(string &date) const {
    auto it = find_if(listeMesures.begin(), listeMesures.end(), [&date](const Mesure& mesure){return mesure.getDateMesure() == date;});
    if(it != listeMesures.end()) {
        return const_cast<Mesure *>(&*it);
    }
    return nullptr;
}

ostream &operator<<(ostream &os, const Capteur &capteur) {
    os << "capteurID: " << capteur.capteurID << " fiable: " << capteur.fiable << " longitude: " << capteur.longitude
       << " latitude: " << capteur.latitude << " capteurPrive: " << capteur.capteurPrive << " premiereMesure: "
       << capteur.premiereMesure  << " derniereMesure: " << capteur.derniereMesure;
    return os;
}

void Capteur::afficherListeMesures() {
    cout << listeMesures.empty() << endl;
    for(list<Mesure>::iterator it = listeMesures.begin(); it != listeMesures.end(); it++) {
        cout << *it << endl;
    }
}
