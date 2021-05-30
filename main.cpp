#include <iostream>
#include <string>
#include "Service.h"
#include <fstream>
#include <stdio.h>
#include <chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

Service service = Service();

Capteur *trouverCapteur(string &id) {
    for (list<Capteur>::iterator it = service.getListeCapteurs().begin();
         it != service.getListeCapteurs().end(); it++) {
        if (!it->getId().compare(id)) {
            return &*it;
        }
    }
    return nullptr;
}

void initialiserUser(ifstream &fluxLectureUsers) {
    string strLigne, id, idCapteur, beforeId;
    while (!fluxLectureUsers.eof()) {
        getline(fluxLectureUsers, id, ';');
        Utilisateur user = Utilisateur(beforeId + id);
        getline(fluxLectureUsers, idCapteur, ';');
        while (idCapteur.find("Sensor") != string::npos) {
            user.addCapteur(*trouverCapteur(idCapteur));
            char c = char(fluxLectureUsers.get());
            if (c == '\n') {
                beforeId = char(fluxLectureUsers.get());
                break;
            } else {
                getline(fluxLectureUsers, idCapteur, ';');
                idCapteur =  c + idCapteur;
            }
        }
        service.addListeUtilisateurs(user);
    }
}

string *lireLigneMesures(ifstream &fluxLectureMesures) {
    string strLigne, ozone, azote, soufre, PM;
    static string tableauMesures[4];
    getline(fluxLectureMesures, strLigne, ';');
    getline(fluxLectureMesures, ozone, ';');
    getline(fluxLectureMesures, strLigne);
    getline(fluxLectureMesures, strLigne, 'N');
    getline(fluxLectureMesures, strLigne, ';');
    getline(fluxLectureMesures, azote, ';');
    getline(fluxLectureMesures, strLigne);
    getline(fluxLectureMesures, strLigne, 'O');
    getline(fluxLectureMesures, strLigne, ';');
    getline(fluxLectureMesures, soufre, ';');
    getline(fluxLectureMesures, strLigne);
    getline(fluxLectureMesures, strLigne, 'P');
    getline(fluxLectureMesures, strLigne, ';');
    getline(fluxLectureMesures, PM, ';');
    tableauMesures[0] = PM;
    tableauMesures[1] = ozone;
    tableauMesures[2] = soufre;
    tableauMesures[3] = azote;
    return tableauMesures;
}

string *lireLigneCapteur(ifstream &fluxLectureCapteurs) {
    string sensorID, buffer, latitude, longitude;
    static string tableauDonneesCapteur[3];
    getline(fluxLectureCapteurs, sensorID, ';');
    tableauDonneesCapteur[0] = sensorID;
    getline(fluxLectureCapteurs, buffer, ';');
    tableauDonneesCapteur[1] = buffer; //latitude
    getline(fluxLectureCapteurs, buffer, ';');
    tableauDonneesCapteur[2] = buffer; //longitude
    getline(fluxLectureCapteurs, buffer); //aller a la ligne suivante
    return tableauDonneesCapteur;
}

bool initialiserDonnees(const string &dataset) {
    cout << "Acces aux donnees..." << endl;
    string nomFichier = dataset + "/measurements.csv";
    string fichierCapteurs = dataset + "/sensors.csv";
    string fichierUtilisateur = dataset + "/users.csv";
    ifstream fluxLectureMesures, fluxLectureCapteurs, fluxLectureUsers;
    fluxLectureUsers.open(fichierUtilisateur);
    fluxLectureMesures.open(nomFichier);
    fluxLectureCapteurs.open(fichierCapteurs);
    if (fluxLectureUsers.is_open() && fluxLectureMesures.is_open() && fluxLectureCapteurs.is_open()) {
        string strLigne, date, id, idAjoute, datePrev, ozone, soufre, azote, PM, sensorID, buffer, derniereMesure;
        bool premierCapteurVu = false;
        double latitude, longitude;
        size_t offset = 0;
        while (!fluxLectureMesures.eof()) {
            getline(fluxLectureMesures, date, ' '); //date initialisee
            if (date == "") {
                break;
            }
            getline(fluxLectureMesures, strLigne, ';');
            getline(fluxLectureMesures, id, ';'); //id initialise
            if (idAjoute != id) {
                if (premierCapteurVu) {
                    service.getListeCapteurs().back().setDerniereMesure(datePrev);
                } else {
                    premierCapteurVu = true;
                }

                string *tableauDonneesCapteur = lireLigneCapteur(fluxLectureCapteurs);
                sensorID = tableauDonneesCapteur[0];
                latitude = stod(tableauDonneesCapteur[1], &offset);
                longitude = stod(tableauDonneesCapteur[2], &offset);

                Capteur c = Capteur(sensorID, longitude, latitude, date);
                service.addListeCapteurs(c);

                idAjoute = id;
            }

            datePrev = date;
            string *tableauMesures = lireLigneMesures(fluxLectureMesures);
            PM = tableauMesures[0];
            ozone = tableauMesures[1];
            soufre = tableauMesures[2];
            azote = tableauMesures[3];

            Mesure mesure = Mesure(date, id, stod(ozone, &offset), stod(soufre, &offset), stod(azote, &offset),
                                   stod(PM, &offset));

            service.getListeCapteurs().back().addMesure(mesure);
            getline(fluxLectureMesures, strLigne);
        }
        service.getListeCapteurs().back().setDerniereMesure(datePrev);

        initialiserUser(fluxLectureUsers);
    } else {
        cerr << "Probleme de lecture des donnees, merci de verifier le chemin d'acces et son contenu\n"
                "Rappel d'un contenu de fichier valide:\n"
                "    - mesurements.csv\n"
                "    - sensors.csv\n"
                "    - users.csv";
        return false;
    }
    return true;

}

void effectuerMoyenne(bool affichageTemps) {
    double longitude, latitude, rayon;
    string dateDeb, dateFin, info_user;
    cout << "Veuillez-renseigner les informations suivantes:" << endl;

    cout << "Longitude : ";
    cin >> info_user;
    longitude = stod(info_user);

    cout << "Latitude : ";
    cin >> info_user;
    latitude = stod(info_user);

    cout << "Rayon (km) : ";
    cin >> info_user;
    rayon = stod(info_user);

    cout << "Date de debut (AAAA-MM-JJ) : ";
    cin >> info_user;
    dateDeb = info_user;

    cout << "Date de fin (AAAA-MM-JJ) : ";
    cin >> info_user;
    dateFin = info_user;

    cout << endl;

    auto t1 = high_resolution_clock::now();

    service.calculerMoyenneQualiteAir(longitude, latitude, rayon, dateDeb, dateFin);

    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    if (affichageTemps) {
        cout << "Le calcul de l'indice de qualite de l'air a pris " << ms_int.count() << " ms.\n";
    }

}


void menuGeneral(bool affichageTemps) {
    char choix_user;

    cout << endl << "Bienvenue dans le Menu Principal !" << endl;

    do {
        cout << endl << "---------------------------MENU---------------------------" << endl;
        cout << "Choississez parmi les propositions suivantes" << endl;
        cout << "1: Calculer moyenne de la qualite de l'air dans une region" << endl;
        cout << "0: Quitter" << endl;

        cout << "Votre choix : ";
        cin >> choix_user;
        cout << "----------------------------------------------------------" << endl;
        cout << endl;

        switch (choix_user) {
            case '0' :
                cout << "A bientot !" << endl;
                break;
            case '1' : {
                effectuerMoyenne(affichageTemps);
                break;
            }
            default : //si l'utilisateur a rentre n'importe quoi
                cout << "Votre choix est incorrect. Pour rappel, vous avez ces possibilites: 0,1" << endl;
        }
    } while (choix_user != '0');
} //-------------------------------------------------------------------------- Fin de menuGeneral


int main(int argc, char *argv[]) {
    bool affichageTemps = (string(argv[1]) != "../../dataset-test");

    if (!initialiserDonnees(argv[1])) {
        return 1;
    }
    cout << "Donnees ajoutees avec succes!" << endl;

    auto t1 = high_resolution_clock::now();
    service.verifierFonctionnementCapteur();
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    if (affichageTemps) {
        cout << "La detection des capteurs non fiables a pris " << ms_int.count() << " ms." << endl;
    }

    int nonFiables = 0;

    for (auto &capteur : service.getListeCapteurs()) {
        if (!capteur.getFiable()) {
            nonFiables++;
        }
    }

    cout << nonFiables << " capteurs non fiables detectes" << endl;

    menuGeneral(affichageTemps);

    return 0;
}