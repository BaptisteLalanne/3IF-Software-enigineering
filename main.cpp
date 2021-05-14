
#include <iostream>
#include <string>
#include "Service.h"
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
using namespace std;
/*
void effectuerMoyenne(){
    Service s;
    double longitude, latitude, rayon;
    string dateDeb, dateFin, info_user;
    cout<<"Veuillez-renseigner les informations suivantes:"<<endl;

    cout<<"Latitude : "<<endl;
    getline(cin, info_user);
    latitude=stoi(info_user);
    cin.ignore();

    cout<<"Longitude : "<<endl;
    getline(cin,info_user);
    longitude=stoi(info_user);
    cin.ignore();

    cout<<"Rayon : "<<endl;
    getline(cin,info_user);
    rayon=stoi(info_user);
    cin.ignore();

    cout<<"Date de début : "<<endl;
    getline(cin,info_user) ;
    dateDeb=info_user;
    cin.ignore();

    cout<<"Date de fin : "<<endl;
    getline(cin,info_user);
    dateFin=info_user;

    double resultat=s.calculerMoyenneQualiteAir(longitude, latitude, rayon, dateDeb, dateFin);
    cout<<"La moyenne de la qualité de l'air dans la zone spécifiée durant la période de "+ dateDeb + " à "+dateFin+" est de "+resultat+ " (indice ATMO)";

}
*/
Service service = Service();

Capteur * trouverCapteur(string &id) {
    for(list<Capteur>::iterator it = service.getListeCapteurs().begin(); it != service.getListeCapteurs().end(); it++) {
        if(!it->getId().compare(id)) {
            return &*it;
        }
    }
    return nullptr;
}

void initialiserUser(ifstream &fluxLectureUsers) {
    string strLigne, id, idCapteur, beforeId;
    while(!fluxLectureUsers.eof()) {
        getline(fluxLectureUsers, id, ';');
        Utilisateur user = Utilisateur(beforeId + id);
        getline(fluxLectureUsers, idCapteur, ';');
        while(idCapteur.find("Sensor") != string::npos) {
            user.addCapteur(*trouverCapteur(idCapteur));
            char c = char(fluxLectureUsers.get());
            if(c == '\n') {
                beforeId = char(fluxLectureUsers.get());
                break;
            } else {
                getline(fluxLectureUsers, idCapteur, ';');
                idCapteur = c + idCapteur;
            }
        }
        service.addListeUtilisateurs(user);
    }
}

bool initialiserDonnees(const string dataset) {
    cout << "Accès aux données..." << endl;
    string nomFichier = dataset + "/measurements.csv";
    string fichierCapteurs = dataset + "/sensors.csv";
    string fichierUtilisateur = dataset + "/users.csv";
    ifstream fluxLectureMesures, fluxLectureCapteurs, fluxLectureUsers;
    fluxLectureUsers.open(fichierUtilisateur);
    fluxLectureMesures.open(nomFichier);
    fluxLectureCapteurs.open(fichierCapteurs);
    if(fluxLectureUsers.is_open() && fluxLectureMesures.is_open() && fluxLectureCapteurs.is_open()){
        string strLigne, date, id, idAjoute, datePrev, ozone, soufre, azote, PM, sensorID, buffer, derniereMesure;
        bool premierCapteurVu = false;
        double latitude, longitude;
        Capteur *capteur = nullptr;
        size_t offset = 0;
        while (!fluxLectureMesures.eof()) {
            getline(fluxLectureMesures, date, ' '); //date initialisée
            getline(fluxLectureMesures, strLigne, ';');
            getline(fluxLectureMesures, id, ';'); //id initialisé
            if (idAjoute != id) {
                if (premierCapteurVu) {
                    capteur->setDerniereMesure(datePrev);
                } else {
                    premierCapteurVu = true;
                }

                getline(fluxLectureCapteurs, sensorID, ';');
                getline(fluxLectureCapteurs, buffer, ';');
                latitude = stod(buffer, &offset);
                getline(fluxLectureCapteurs, buffer, ';');
                longitude = stod(buffer, &offset);
                getline(fluxLectureCapteurs, buffer); //aller à la ligne suivante
                Capteur c = Capteur(sensorID, longitude, latitude, date);
                capteur = &c;
                service.addListeCapteurs(c);

                idAjoute = id;
            }

            datePrev = date;
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

            Mesure mesure = Mesure(date, id, stod(PM, &offset), stod(ozone, &offset), stod(soufre, &offset),
                                   stod(azote, &offset));

            service.getListeCapteurs().back().addMesure(mesure);
            getline(fluxLectureMesures, strLigne);
        }
        capteur->setDerniereMesure(date);

        initialiserUser(fluxLectureUsers);
    }else{
        cerr <<"Problème de lecture des données, merci de vérifier le chemin d'accès et son contenu\n"
               "Rappel d'un contenu de fichier valide:\n"
               "    - mesurements.csv\n"
               "    - sensors.csv\n"
               "    - users.csv";
        return false;
    }
    return true;

}



void menuGeneral()
{
    char choix_user;
    double donnee_user;

    cout << "Bienvenue dans le Menu Principal"<<endl;

    do{
        cout<<"--------------MENU-----------------"<<endl;
        cout<<"Choississez parmi les propositions suivantes"<<endl;
        cout<<"1: Calculer Moyenne "<<endl;
        cout<<"0: Quitter "<<endl;

        cout<<"Votre choix: ";
        cin >> choix_user;
        cout<<"------------------------------------------"<<endl;
        cout<<endl;

        switch(choix_user){
            case '0' :
                cout<<"A bientôt !"<<endl;
                break;
            case '1' :
                //effectuerMoyenne();
                break;

            default : //si l'utilisateur a rentré n'importe quoi
                cout << "Votre choix est incorrect. Pour rappel, vous avez ces possibilités: 0,1"<<endl;
        }
    }while (choix_user !='0');
} //-------------------------------------------------------------------------- Fin de menuGénéral



void afficher(string chaine){


}



int main(int argc, char *argv[]) {
    if(argc != 2) {
        cerr << "Problème de lecture des données, merci de vérifier le chemin d'accès et son contenu\n"
                "Rappel d'un contenu de fichier valide:\n"
                "    - mesurements.csv\n"
                "    - sensors.csv\n"
                "    - users.csv";
    }
    if(!initialiserDonnees(argv[1])){
        return 1;
    }
    cout<<"Données ajoutées avec succés!"<<endl;

    service.verifierFonctionnementCapteur();

    int nonFiables = 0;

    for(auto & capteur : service.getListeCapteurs()) {
        //cout << capteur << endl;
        if(!capteur.getFiable()) {
            nonFiables++;
        }
        //capteur.afficherListeMesures();
    }

    cout << nonFiables << " capteurs non fiables" << endl;
/*
    for(auto & user : service.getListeUtilisateurs()) {
        cout << user << endl;
        user.afficherCapteurs();
    }*/
    menuGeneral();
    return 0;
}