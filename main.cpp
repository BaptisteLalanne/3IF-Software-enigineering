
#include <iostream>
#include <string>
#include "Service.h"
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
using namespace std;


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

string* lireLigneMesures(ifstream &fluxLectureMesures) {
    string strLigne, ozone, azote, soufre, PM;
    static string tableauMesures[4];
    getline(fluxLectureMesures,strLigne,';');
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
    tableauMesures[0]=PM;
    tableauMesures[1]=ozone;
    tableauMesures[2]=soufre;
    tableauMesures[3]=azote;
    return tableauMesures;
}

string* lireLigneCapteur(ifstream &fluxLectureCapteurs){
    string sensorID, buffer,latitude, longitude;
    static string tableauDonneesCapteur[3];
    const size_t offset = 0;
    getline(fluxLectureCapteurs, sensorID, ';');
    tableauDonneesCapteur[0]=sensorID;
    getline(fluxLectureCapteurs, buffer, ';');
    tableauDonneesCapteur[1]=buffer; //latitude
    getline(fluxLectureCapteurs, buffer, ';');
    tableauDonneesCapteur[2]=buffer; //longitude
    getline(fluxLectureCapteurs, buffer); //aller à la ligne suivante
    return tableauDonneesCapteur;
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
        size_t offset = 0;
        while (!fluxLectureMesures.eof()) {
            getline(fluxLectureMesures, date, ' '); //date initialisée
            if (date == "") {
                break;
            }
            getline(fluxLectureMesures, strLigne, ';');
            getline(fluxLectureMesures, id, ';'); //id initialisé
            if (idAjoute != id) {
                if (premierCapteurVu) {
                    service.getListeCapteurs().back().setDerniereMesure(datePrev);
                } else {
                    premierCapteurVu = true;
                }

                string* tableauDonneesCapteur=lireLigneCapteur(fluxLectureCapteurs);
                sensorID=tableauDonneesCapteur[0];
                latitude = stod(tableauDonneesCapteur[1],&offset);
                longitude = stod(tableauDonneesCapteur[2], &offset);

                Capteur c = Capteur(sensorID, longitude, latitude, date);
                service.addListeCapteurs(c);

                idAjoute = id;
            }

            datePrev = date;
            string * tableauMesures= lireLigneMesures(fluxLectureMesures);
            PM=tableauMesures[0];
            ozone=tableauMesures[1];
            soufre=tableauMesures[2];
            azote=tableauMesures[3];

            Mesure mesure = Mesure(date, id, stod(PM, &offset), stod(ozone, &offset), stod(soufre, &offset),stod(azote, &offset));

            service.getListeCapteurs().back().addMesure(mesure);
            getline(fluxLectureMesures, strLigne);
        }
        service.getListeCapteurs().back().setDerniereMesure(datePrev);

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
/*
void effectuerMoyenne(){
    double longitude, latitude, rayon;
    string dateDeb, dateFin, info_user;
    cin.clear();
    fflush(stdin);
    cout<<"Veuillez-renseigner les informations suivantes:"<<endl;

    cout<<"Latitude :";
    cin.ignore();
    getline(cin, info_user);
    latitude=atof(info_user.c_str());

    cout<<"Longitude :";
    cin.ignore();
    getline(cin,info_user);
    longitude=atof(info_user.c_str());

    cout<<"Rayon :";
    cin.ignore();
    getline(cin,info_user);
    rayon=atof(info_user.c_str());

    cout<<"Date de début (AAAA-MM-JJ) :";
    cin.ignore();
    getline(cin,info_user) ;
    dateDeb=info_user;

    cout<<"Date de fin (AAAA-MM-JJ) :";
    cin.ignore();
    getline(cin,info_user);
    dateFin=info_user;

    service.calculerMoyenneQualiteAir(longitude, latitude, rayon, dateDeb, dateFin);
    //cout<<"La moyenne de la qualité de l'air dans la zone spécifiée durant la période de "+ dateDeb + " à "+dateFin+" est de "+resultat+ " (indice ATMO)";
}
*/

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

        cout<<"Votre choix :";
        cin >> choix_user;
        cout<<"-----------------------------------"<<endl;
        cout<<endl;

        switch(choix_user){
            case '0' :
                cout<<"A bientôt !"<<endl;
                break;
            case '1' :
                service.calculerMoyenneQualiteAir(2.0, 44.0, 1.2, "2019-01-01", "2019-01-04");
                //effectuerMoyenne();
                break;

            default : //si l'utilisateur a rentré n'importe quoi
                cout << "Votre choix est incorrect. Pour rappel, vous avez ces possibilités: 0,1"<<endl;
        }
    }while (choix_user !='0');
} //-------------------------------------------------------------------------- Fin de menuGénéral


int main(int argc, char *argv[]) {
    if((argc==3 && string(argv[2]) != "-test") || (argc!=2 && argc !=3)) {
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
            cout << capteur << endl;
        }
        //capteur.afficherListeMesures();
        /*
        for (auto & mesure : capteur.getListeMesures()) {
            cout << capteur.getId() <<";" << mesure.getDateMesure() << ";" << mesure.calculerIndice() << endl;
        }*/
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