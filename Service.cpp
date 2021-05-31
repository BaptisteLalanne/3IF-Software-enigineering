#define _USE_MATH_DEFINES

#include "Service.h"
#include <cmath>
#include <cstring>
#include <sstream>

Service::Service() {

}

Service::~Service() {

}


void Service::addListeCapteurs(Capteur &capteur) {
    listeCapteurs.push_back(capteur);
}

list<Capteur> &Service::getListeCapteurs() {
    return listeCapteurs;
}

void Service::addListeUtilisateurs(Utilisateur &utilisateur) {
    listeUtilisateurs.push_back(utilisateur);
}

double Service::distanceDeuxPointsTerre(double latitudeA, double longitudeA, double latitudeB, double longitudeB) {
    int rayonTerre = 6373;
    latitudeA = latitudeA * M_PI / 180;
    latitudeB = latitudeB * M_PI / 180;
    double diffLongitude = (longitudeB - longitudeA) * M_PI / 180;
    return rayonTerre * acos(sin(latitudeA) * sin(latitudeB) + cos(latitudeA) * cos(latitudeB) * cos(diffLongitude));
}

void Service::verifierFonctionnementCapteur() {

    double moyenne[4];
    double distanceEntreCapteurs;
    Mesure *moyenneDate;
    double moyenneDateTab[4];
    int nombreDonneesComparaison;
    const int differencePourFiabilite = 3;
    const double rayonVerification = 90;
    const int nbVoisinsRequis = 3;
    Mesure *mesureMoyenne;
    list<Capteur> capteursProches;

    for (auto &capteur : listeCapteurs) {

        for (auto &capteur2 : listeCapteurs) {
            if (capteur2.getId() != capteur.getId()) {
                distanceEntreCapteurs = distanceDeuxPointsTerre(capteur2.getLatitude(), capteur2.getLongitude(),
                                                                capteur.getLatitude(), capteur.getLongitude());
                if (distanceEntreCapteurs <= rayonVerification) {
                    capteursProches.push_back(capteur2);
                }
            }
        }

        for (auto &mesure : capteur.getListeMesures()) {
            for (int i = 0; i < 4; i++) {
                moyenne[i] = 0;
            }
            nombreDonneesComparaison = 0;
            for (auto &capteurComp : capteursProches) {
                if (capteurComp.obtenirMesureDate(mesure.getDateMesure()) != nullptr) {
                    moyenneDate = capteurComp.obtenirMesureDate(mesure.getDateMesure());
                    moyenneDateTab[0] = moyenneDate->getOzone();
                    moyenneDateTab[1] = moyenneDate->getDioxydeSoufre();
                    moyenneDateTab[2] = moyenneDate->getDioxydeAzote();
                    moyenneDateTab[3] = moyenneDate->getParticulesFines();
                    for (int i = 0; i < 4; i++) {
                        moyenne[i] += moyenneDateTab[i];
                    }
                    nombreDonneesComparaison++;
                }
            }
            if (nombreDonneesComparaison >= nbVoisinsRequis) {
                for (int i = 0; i < 4; i++) {
                    moyenne[i] /= nombreDonneesComparaison;
                }
                mesureMoyenne = new Mesure("", "", moyenne[0], moyenne[1], moyenne[2], moyenne[3]);

                if (abs(mesureMoyenne->calculerIndice() - mesure.calculerIndice()) > differencePourFiabilite) {
                    capteur.desactiverCapteur();
                    if (capteur.getUtilisateurPrive()) {
                        capteur.getUtilisateurPrive()->empecherGagnerPoints();
                        break;
                    }
                }

                delete mesureMoyenne;
            } else {
                capteur.desactiverCapteur();
                if (capteur.getUtilisateurPrive() != nullptr) {
                    capteur.getUtilisateurPrive()->empecherGagnerPoints();
                    break;
                }
            }
        }
        capteursProches.clear();
    }
}

list<Capteur>
Service::obtenirCapteursRegion(double centreRegionLongitude, double centreRegionLatitude, string dateDebut,
                               string dateFin, double rayonMinRegion, double rayonMaxRegion) {
    list<double> tableauDistances;
    list<Capteur> listeCapteursRegion;
    if (strcmp(dateDebut.c_str(), dateFin.c_str()) <= 0) {
	    for (auto &capteur : listeCapteurs) {
		if (capteur.getFiable()) {
		    if (strcmp(capteur.getPremiereMesure().c_str(), dateDebut.c_str()) <= 0 &&
		        strcmp(capteur.getDerniereMesure().c_str(), dateFin.c_str()) >= 0) {
		        double distanceCapteurRegion = distanceDeuxPointsTerre(capteur.getLatitude(), capteur.getLongitude(),
		                                                               centreRegionLatitude, centreRegionLongitude);
		        if (distanceCapteurRegion >= rayonMinRegion && distanceCapteurRegion <= rayonMaxRegion) {
		            list<Capteur>::iterator itCapteur = listeCapteursRegion.begin();
		            list<double>::iterator it;
		            for (it = tableauDistances.begin(); it != tableauDistances.end(); it++) {
		                if (tableauDistances.empty() || distanceCapteurRegion < *it) {
		                    tableauDistances.insert(it, distanceCapteurRegion);
		                    listeCapteursRegion.insert(itCapteur, capteur);
		                    break;
		                }
		                itCapteur++;
		            }
		            if (it == tableauDistances.end()) {
		                tableauDistances.push_back(distanceCapteurRegion);
		                listeCapteursRegion.push_back(capteur);
		            }
		        }
		    }
		}
	    }
    }
    return listeCapteursRegion;
}


double
Service::obtenirDensiteRegion(list<Capteur> listeDesCapteurs, double longitude, double latitude, double rayonRegion,
                              double rayonMesCapteurs) { //centreRegionLongitude = longitude
    int compteurPresenceCapteur = 0;
    int compteurZoneRegion = 0;
    const int precision = 1;
    const int rayonMesureCapteur = rayonMesCapteurs * pow(10, precision);
    int tailleCarte = 2 * rayonRegion * pow(10, precision);
    int debutMesureCapteurLongitude, finMesureCapteurLongitude, debutMesureCapteurLatitude, finMesureCapteurLatitude, centreCapteurLongitude, centreCapteurLatitude;
    int rayonTailleTab = rayonRegion * pow(10, precision);

    bool **carte = new bool *[tailleCarte];
    for (int i = 0; i < tailleCarte; i++) {
        carte[i] = new bool[tailleCarte];
        for (int j = 0; j < tailleCarte; j++) {
            carte[i][j] = false;
            if (pow(i - rayonTailleTab, 2) + pow(j - rayonTailleTab, 2) <= pow(rayonTailleTab, 2)) {
                compteurZoneRegion++;
            }
        }
    }

    for (auto &capteur : listeDesCapteurs) {
        if (capteur.getLongitude() < longitude) {
            centreCapteurLongitude =
                    (rayonRegion - distanceDeuxPointsTerre(latitude, capteur.getLongitude(), latitude, longitude)) *
                    pow(10, precision);
        } else {
            centreCapteurLongitude =
                    (rayonRegion + distanceDeuxPointsTerre(latitude, capteur.getLongitude(), latitude, longitude)) *
                    pow(10, precision);
        }

        if (capteur.getLatitude() < latitude) {
            centreCapteurLatitude =
                    (rayonRegion - distanceDeuxPointsTerre(capteur.getLatitude(), longitude, latitude, longitude)) *
                    pow(10, precision);
        } else {
            centreCapteurLatitude =
                    (rayonRegion + distanceDeuxPointsTerre(capteur.getLatitude(), longitude, latitude, longitude)) *
                    pow(10, precision);
        }

        debutMesureCapteurLongitude = centreCapteurLongitude - rayonMesureCapteur;
        if (debutMesureCapteurLongitude < 0) {
            debutMesureCapteurLongitude = 0;
        }
        finMesureCapteurLongitude = centreCapteurLongitude + rayonMesureCapteur;
        if (finMesureCapteurLongitude > tailleCarte) {
            finMesureCapteurLongitude = tailleCarte;
        }

        debutMesureCapteurLatitude = centreCapteurLatitude - rayonMesureCapteur;
        if (debutMesureCapteurLatitude < 0) {
            debutMesureCapteurLatitude = 0;
        }
        finMesureCapteurLatitude = centreCapteurLatitude + rayonMesureCapteur;
        if (finMesureCapteurLatitude > tailleCarte) {
            finMesureCapteurLatitude = tailleCarte;
        }

        for (int i = debutMesureCapteurLongitude; i < finMesureCapteurLongitude; i++) {
            for (int j = debutMesureCapteurLatitude; j < finMesureCapteurLatitude; j++) {
                if (pow(i - centreCapteurLongitude, 2) + pow(j - centreCapteurLatitude, 2) <=
                    pow(rayonMesureCapteur, 2)) {
                    if (pow(i - rayonTailleTab, 2) + pow(j - rayonTailleTab, 2) <= pow(rayonTailleTab, 2)) {
                        if (!carte[j][i]) {
                            carte[j][i] = true;
                            compteurPresenceCapteur++;
                        }
                    }
                }
            }
        }
    }

    double densite = 100 * double(compteurPresenceCapteur) / double(compteurZoneRegion);
    for (int i = 0; i < tailleCarte; i++) {
        delete[] carte[i];
    }
    delete[] carte;
    return densite;

}

void
Service::calculerMoyenneQualiteAir(double longitude, double latitude, double rayon, string dateDebut, string dateFin) {
    double moyenne[4];
    int nombreCapteursValides = 0;
    for (double &i : moyenne) {
        i = 0;
    }
    double rayonMesureCapteur = 25;
    list<Capteur> capteursProches = obtenirCapteursRegion(longitude, latitude, dateDebut, dateFin, 0,
                                                          rayon + rayonMesureCapteur);
    if (capteursProches.empty()) {
        cout << "Aucune donnee dans la zone ou au cours de la periode selectionnee." << endl;
        return;
    }

    for (Capteur &capteur : capteursProches) {
        double *moyenneTousPolluants = capteur.obtenirMoyenne(dateDebut, dateFin);
        for (int i = 0; i < 4; i++) {
            moyenne[i] = moyenne[i] + moyenneTousPolluants[i];
        }
        nombreCapteursValides++;
    }

    //On fait la moyenne des concentrations
    for (int i = 0; i < 4; i++) {
        moyenne[i] = moyenne[i] / nombreCapteursValides;
    }

    Mesure *mesureMoyenne = new Mesure("", "", moyenne[0], moyenne[1], moyenne[2], moyenne[3]);
    int indiceRegion = (*mesureMoyenne).calculerIndice();

    int densite = int(obtenirDensiteRegion(capteursProches, longitude, latitude, rayon, rayonMesureCapteur));
    if (densite > 30) {
        cout << "L'indice ATMO dans la region est de " << indiceRegion
             << " (la zone selectionnee est recouverte par les capteurs a " << densite << "%)." << endl;
    } else {
        cout << "Attention, la zone selectionnee n'est couverte par les capteurs qu'a " << densite
             << "%. L'indice ATMO dans la region est de " << indiceRegion << "." << endl;
    }
    delete mesureMoyenne;
}
