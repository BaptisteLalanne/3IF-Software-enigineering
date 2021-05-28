#include <iostream>
using namespace std;
#include "Service.h"
#include "Mesure.h"
#include "Capteur.h"
#include "Test.h"
#include <string>
#include <cassert>
#include <algorithm>


void Test::testerCalculerIndice(){
    const string date="25/05/2021";
    double ozone [10] = { 36.0, 40.0, 145.0, 103.0, 135.0, 102.0, 67.0, 52.0, 29.7, 28.0 };
    double soufre[10] = { 240.0, 404.0, 287.0, 85.6, 198.0, 178.0, 122.3, 21.0, 21.2, 32.2 };
    double azote[10] = { 300.0, 270.0, 210.0, 111.0, 112.0, 43.0, 80.0, 67.0, 33.3, 10.4 };
    double pm[10] = { 55.0, 60.0, 48.0, 44.0, 23.0, 7.2, 2.0, 7.4, 1.2, 6.9 };
    int indice_attendu[10]= { 10, 9, 8, 7, 6, 5, 4, 3, 2,1 };
    bool testsValides = true;
    for(int i = 0; i<10;i++){
        Mesure mesure = Mesure(date,"mesure"+i,pm[i],ozone[i], soufre[i], azote[i]);
        int indice_exp = mesure.calculerIndice();
        if(indice_exp != indice_attendu[i]){
            testsValides=false;
            cerr<<"Resultat erroné pour le calcul de l'indice ATMO avec comme paramètre \n"<<
                "Ozone :"<<mesure.getOzone()<<"\n"<<
                "Soufre :" << mesure.getDioxydeSoufre()<<"\n"<<
                "Azote :" << mesure.getDioxydeAzote()<<"\n"<<
                "Particules Fines :" << mesure.getDioxydeSoufre()<<"\n"<<
                "Resultat trouvé :"<< indice_exp << "\n"<<
                "Résultat attendu : "<< indice_attendu[i] <<endl;
        }
    }
    if(testsValides){
        cout<<"Tests unitaires CalculerIndice corrects."<<endl;
    }else{
        cout<<"Tests unitaires CalculerIndice incorrects."<<endl;
    }
}


void Test::testerObtenirMesureDate(){
    string date_ref="25/05/2021";
    Mesure mesure1 = Mesure("","mesure1",36.0, 40.0, 145.0, 103.0); //sans date
    Mesure mesure_recherchee = Mesure(date_ref,"mesure2",366.0, 43.0, 149.0, 183.0); //date recherchée
    Mesure mesure3 = Mesure("26/05/2003","mesure3",65.0, 4.0, 45.0, 13.0); //date incorre

    Capteur capteur= Capteur("001",-44.0, 100.0, ""); //Capteur(const string &capteurId, double longitude, double latitude, const string &premiereMesure);
    capteur.addMesure(mesure1);
    capteur.addMesure(mesure_recherchee);
    capteur.addMesure(mesure3);

    Mesure* mesure_exp= capteur.obtenirMesureDate(date_ref);
    if((*mesure_exp).getId()!=mesure_recherchee.getId()){
        cerr<<"Resultat erroné pour la recherche de Mesure par date \n"<<
            "Résultat trouvé :" << (*mesure_exp).getDateMesure() <<"\n" <<
            "Résultat attendu :" << mesure_recherchee.getDateMesure()<<endl;
        cout<<"Test unitaire ObtenirMesureDate incorrect."<<endl;
    }else{
        cout<<"Test unitaire ObtenirMesureDate correct."<<endl;
    }
}

void Test::afficherListe(list<Capteur> & liste) {
    int count = 1;
    for(list<Capteur>::iterator it = liste.begin(); it != liste.end(); it++) {
        cerr << "Capteur "<< count << ":\n"
             << "latitude: " << it->getLatitude() <<"\n"
             << "longitude: " << it->getLongitude() <<"\n\n";
        count++;
    }
    cerr <<"\n\n\n";
}



bool Test::verificationMoyenne(string dateDebut, string dateFin, double *v, double * moyenne) {
    bool testObtenirMoyenne = true;
    for(int i=0; i<4; i++) {

        if(v[i]!=moyenne[i]) {
            cerr<<"Resultat erroné pour le calcul de moyenne par date \n"<<
                "Résultat trouvé :" << v[i] <<"\n" <<
                "Résultat attendu :" << moyenne[i]<< " Pour les dates : " << dateDebut << " et " << dateFin<<endl;
            testObtenirMoyenne = false;
        }
    }
    return testObtenirMoyenne;

}

// A FINIR
void Test::testerObtenirMoyenne(){
    Capteur capteur = Capteur("002",-44.0,100.0,"");//Capteur(const string &capteurId, double longitude, double latitude, const string &premiereMesure);
    Mesure mesure1 = Mesure("19/05/2021","mesure1",50.5,43.75,75.25,38.75);
    Mesure mesure2 = Mesure("20/05/2021","mesure2",40,20.75,90.25,40.75);
    Mesure mesure3 = Mesure("21/05/2021","mesure3",50.5,43.75,75.25,38.75);
    Mesure mesure4 = Mesure("22/05/2021","mesure4",50.5,43.75,75.25,38.75);
    Mesure mesure5 = Mesure("23/05/2021","mesure5",50.5,43.75,75.25,38.75);
    Mesure mesure6 = Mesure("24/05/2021","mesure6",50.5,43.75,75.25,38.75);
    Mesure mesure7 = Mesure("25/05/2021","mesure7",50.5,43.75,75.25,38.75);
    Mesure mesure8 = Mesure("26/05/2021","mesure8",50.5,43.75,75.25,38.75);
    Mesure mesure9 = Mesure("27/05/2021","mesure9",50.5,43.75,75.25,38.75);
    Mesure mesure10 = Mesure("28/05/2021","mesure10",50.5,43.75,75.25,38.75);
    capteur.addMesure(mesure1);
    capteur.addMesure(mesure2);
    capteur.addMesure(mesure3);
    capteur.addMesure(mesure4);
    capteur.addMesure(mesure5);
    capteur.addMesure(mesure6);
    capteur.addMesure(mesure7);
    capteur.addMesure(mesure8);
    capteur.addMesure(mesure9);
    capteur.addMesure(mesure10);
    string dateDebut = "19/05/2021";
    string dateFin = "21/05/2021";
    double* v1 = capteur.obtenirMoyenne(dateDebut,dateFin);
    double moyenne1[4] = {49.45, 41.45, 76.75, 38.95};
    bool testObtenirMoyenne [4];
    testObtenirMoyenne[0] = verificationMoyenne(dateDebut, dateFin, v1, moyenne1);
    dateDebut = "29/05/2021";
    dateFin= "30/05/2021";
    double* v2 = capteur.obtenirMoyenne(dateDebut,dateFin);
    double moyenne2[4] = {0, 0, 0, 0};
    testObtenirMoyenne[1] = verificationMoyenne(dateDebut, dateFin, v2, moyenne2);
    dateDebut = "28/05/2021";
    dateFin= "29/05/2021";
    double*v3 = capteur.obtenirMoyenne(dateDebut,dateFin);
    double moyenne3[4] = {50.5, 43.75, 72.25, 38.75};
    testObtenirMoyenne[2] = verificationMoyenne(dateDebut, dateFin, v3, moyenne3);
    dateDebut = "01/05/2021";
    dateFin= "20/05/2021";
    double *v4 = capteur.obtenirMoyenne(dateDebut, dateFin);
    double moyenne4[4] = {45.25, 32.25, 82.75, 39.75};
    testObtenirMoyenne[3] = verificationMoyenne(dateDebut, dateFin, v4, moyenne4);
    bool affichage = true;
    for(int i=0; i<4; i++) {
        if(!testObtenirMoyenne[i]) {
            affichage = false;
        }
    }
    if(!affichage) {
        cout << "Test unitaire obtenirMoyenne() succès" << endl;
    } else {
        cout << "Test unitaire obtenirMoyenne() échec" << endl;
    }
}


void Test::testerObtenirCapteursRegion(){
    bool testsValides=true;
    Service service = Service();
    string dateDeb="2021-05-26";
    string dateFin="2021-05-27";
    Capteur c1 = Capteur("001", 46.4, 2.5, dateDeb);
    Capteur c2 = Capteur("002", 47.2, 2.5, dateDeb);
    Capteur c3 = Capteur("003", 46.4, 3.2, dateDeb);
    c1.setDerniereMesure(dateFin);
    c2.setDerniereMesure(dateFin);
    c3.setDerniereMesure(dateFin);
    list<Capteur> listeCapteurs;
    listeCapteurs.push_back(c1);
    listeCapteurs.push_back(c2);
    listeCapteurs.push_back(c3);
    double latitude[3] = {46.5,46.5,44.1};
    double longitude[3] = {2.5,2.5,2.5};
    double rayonMax[3]={95.0,75.0,50.0};
    list<Capteur> listeTest1;
    list<Capteur> listeTest2;
    list<Capteur> listeTest3; //liste vide
    listeTest1.push_back(c1);
    listeTest1.push_back(c2);
    listeTest1.push_back(c3);
    listeTest2.push_back(c1);
    listeTest2.push_back(c3);

    list<list<Capteur>> listesAttendues;
    listesAttendues.push_back(listeTest1);
    listesAttendues.push_back(listeTest2);
    listesAttendues.push_back(listeTest3);
    auto it = listesAttendues.begin();
    for(int i = 0; i < listeCapteurs.size(); i++){
        list<Capteur> listeCapteursProches =service.obtenirCapteursRegion(longitude[i],latitude[i],dateDeb,dateFin, 0, rayonMax[i]);
        auto it_sousliste = (*it).begin();
        if(listeCapteursProches.size()!=(*it).size()){
            testsValides=false;
            for (int j = 0; j < listeCapteursProches.size(); j++) {
                list<Capteur>::iterator iter = find(listeCapteursProches.begin(), listeCapteursProches.end(), (*it_sousliste));
                if(iter == listeCapteursProches.end()) {
                    //FAIRE : ostream &operator==(ostream &os,
                    testsValides = false;
                }
                it_sousliste++;
            }
        it++;
        }
        if(testsValides==false){
        cerr<<"Resultat erroné pour la détermination des capteurs proches: \n"
                << "Resultat trouvé :";
                afficherListe(listeCapteursProches);
                cerr<< endl << "Résultat attendu : ";
                afficherListe((*it));
                cerr<< endl;
                cout<<"Tests unitaires obtenirCapteursRegion correct"<<endl;
        }else{
                cout<<"Tests unitaires obtenirCapteursRegion incorrects."<<endl;
        }

    }
}



/*
void Test::testerComparerDates(){
    Service service = Service();
    const string dates1 [4]={"","21/03/2019","25/05/2021","29mars2001"}; //modifier la méthode dans Service.cpp pour vérifier que la date a bien un format Date
    const string dates2 [4]={"","22/03/2019","25/05/2021","29/03/2001"};
    bool resultat_attendu [4] ={true,false,true,false};
    bool testsValides=true;
    for (int i=0; i<4;i++){
        bool resultat_exp =service.comparerDates(dates1[i], dates2[i]);
        if(resultat_exp!=resultat_attendu[i]){
            testsValides=false;
            cerr<<"Resultat erroné pour le calcul de l'indice ATMO avec comme paramètre \n"<<
               "Première date :"<<dates1[i]<<"\n"<<
               "Deuxième date :" <<dates2[i]<<"\n"<<
               "Resultat trouvé :"<< resultat_exp << "\n"<<
               "Résultat attendu : "<< resultat_attendu[i] <<endl;
        }
        if(testsValides){
            cout<<"Tests unitaires ComparerDates corrects."<<endl;
        }else{
            cout<<"Tests unitaires ComparerDates incorrects."<<endl;
        }
    }
}
*/

/*fonctions à tester:
calculer Indice (Mesure) --------------fait
obtenirMesureDate (Capteur) -----------fait
obtenirMoyenne (Capteur)-----------en cours
calculerMoyenneQualiteAir -> déjà fait dans les tests de bout en bout
verifierFonctionnement -> déjà fait dans les tests de bout en bout
obtenirCapteursRegion (Service)--------fait
comparerDates -------------------------fait, penser à modifier comparesDates dans Service.cpp
obtenirDensiteRegion

*/

void Test::mainTests() {
    testerCalculerIndice();
    testerObtenirMesureDate();
    testerObtenirMoyenne();
    //testerCalculerMoyenneQualiteAir();
    testerObtenirCapteursRegion();
    //testerComparerDates();
}