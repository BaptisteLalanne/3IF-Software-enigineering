#include <iostream>
using namespace std;
#include "Service.h"
#include "Mesure.h"
#include "Capteur.h"
#include <string>
#include <cassert>
#include <algorithm>


void testerCalculerIndice(){
    cout << "---------------- TESTS UNITAIRES - CALCULER INDICE ----------------" << endl << endl;
    const string date="25/05/2021";
    double ozone [10] = { 36.0, 40.0, 145.0, 103.0, 135.0, 102.0, 67.0, 52.0, 29.7, 28.0 };
    double soufre[10] = { 240.0, 404.0, 287.0, 85.6, 198.0, 178.0, 122.3, 21.0, 21.2, 32.2 };
    double azote[10] = { 300.0, 270.0, 210.0, 111.0, 112.0, 43.0, 80.0, 67.0, 33.3, 10.4 };
    double pm[10] = { 55.0, 60.0, 48.0, 44.0, 23.0, 7.2, 2.0, 7.4, 1.2, 6.9 };
    int indice_attendu[10]= { 9, 9, 8, 7, 6, 5, 4, 3, 2,1 };
    bool testsValides = true;
    for(int i = 0; i<10;i++){
        Mesure mesure = Mesure(date,"mesure"+i,ozone[i], soufre[i], azote[i], pm[i]);
        int indice_exp = mesure.calculerIndice();
        if(indice_exp != indice_attendu[i]){
            testsValides=false;
            cerr<<"Resultat erroné pour le calcul de l'indice ATMO avec comme paramètre \n"<<
                "Ozone : "<<mesure.getOzone()<<"\n"<<
                "Soufre : " << mesure.getDioxydeSoufre()<<"\n"<<
                "Azote : " << mesure.getDioxydeAzote()<<"\n"<<
                "Particules Fines : " << mesure.getParticulesFines()<<"\n"<<
                "Resultat trouvé : "<< indice_exp << "\n"<<
                "Résultat attendu : "<< indice_attendu[i] <<endl << endl;
        }
    }
    if(testsValides){
        cout<<"Tests unitaires CalculerIndice corrects."<<endl << endl;
    }else{
        cout<<"Tests unitaires CalculerIndice incorrects."<<endl << endl;
    }
    cout << "-------------------------------------------------------------------" << endl << endl << endl << endl;
}


void testerObtenirMesureDate(){
    cout << "-------------- TESTS UNITAIRES - OBTENIR MESURE DATE --------------" << endl << endl;
    string date_ref="25/05/2021";
    Mesure mesure1 = Mesure("","mesure1", 40.0, 145.0, 103.0, 36.0); //sans date
    Mesure mesure_recherchee = Mesure(date_ref,"mesure2", 43.0, 149.0, 183.0, 366.0); //date recherchée
    Mesure mesure3 = Mesure("26/05/2003","mesure3", 4.0, 45.0, 13.0, 65.0); //date incorre

    Capteur capteur= Capteur("001",-44.0, 100.0, ""); //Capteur(const string &capteurId, double longitude, double latitude, const string &premiereMesure);
    capteur.addMesure(mesure1);
    capteur.addMesure(mesure_recherchee);
    capteur.addMesure(mesure3);

    Mesure* mesure_exp= capteur.obtenirMesureDate(date_ref);
    if((*mesure_exp).getId()!=mesure_recherchee.getId()){
        cerr<<"Resultat erroné pour la recherche de Mesure par date \n"<<
            "Résultat trouvé : " << (*mesure_exp).getDateMesure() <<"\n" <<
            "Résultat attendu : " << mesure_recherchee.getDateMesure()<<endl << endl;
        cout<<"Tests unitaires ObtenirMesureDate incorrects."<<endl << endl;
    }else{
        cout<<"Tests unitaires ObtenirMesureDate corrects."<<endl << endl;
    }
    cout << "-------------------------------------------------------------------" << endl << endl << endl << endl;
}

bool verificationMoyenne(string dateDebut, string dateFin, double *v, double * moyenne) {
    bool testObtenirMoyenne = true;
    for(int i=0; i<4; i++) {

        if(v[i]!=moyenne[i]) {
            cerr<<"Resultat erroné pour le calcul de moyenne par date pour concentration " << i << endl <<
                "Résultat trouvé : " << v[i] <<"\n" <<
                "Résultat attendu : " << moyenne[i]<< " Pour les dates : " << dateDebut << " et " << dateFin<<endl << endl;
            testObtenirMoyenne = false;
        }
    }
    return testObtenirMoyenne;

}

// A FINIR
void testerObtenirMoyenne(){
    cout << "---------------- TESTS UNITAIRES - OBTENIR MOYENNE ----------------" << endl << endl;
    Capteur capteur = Capteur("002",-44.0,100.0,"");//Capteur(const string &capteurId, double longitude, double latitude, const string &premiereMesure);
    Mesure mesure1 = Mesure("2021-05-19","mesure1",43.75,75.25,38.75,50.5);
    Mesure mesure2 = Mesure("2021-05-20","mesure2",20.75,90.25,40.75,40);
    Mesure mesure3 = Mesure("2021-05-21","mesure3",43.75,75.25,38.75,50.5);
    Mesure mesure4 = Mesure("2021-05-22","mesure4",43.75,75.25,38.75,50.5);
    Mesure mesure5 = Mesure("2021-05-23","mesure5",43.75,75.25,38.75,50.5);
    Mesure mesure6 = Mesure("2021-05-24","mesure6",43.75,75.25,38.75,50.5);
    Mesure mesure7 = Mesure("2021-05-25","mesure7",43.75,75.25,38.75,50.5);
    Mesure mesure8 = Mesure("2021-05-26","mesure8",43.75,75.25,38.75,50.5);
    Mesure mesure9 = Mesure("2021-05-27","mesure9",43.75,75.25,38.75,50.5);
    Mesure mesure10 = Mesure("2021-05-28","mesure10",43.75,75.25,38.75,50.5);
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
    string dateDebut = "2021-05-19";
    string dateFin = "2021-05-28";
    double* v1 = capteur.obtenirMoyenne(dateDebut,dateFin);
    double moyenne1[4] = {41.45, 76.75, 38.95, 49.45};
    bool testObtenirMoyenne [4];
    testObtenirMoyenne[0] = verificationMoyenne(dateDebut, dateFin, v1, moyenne1);
    dateDebut = "2021-05-29";
    dateFin= "2021-05-30";
    double* v2 = capteur.obtenirMoyenne(dateDebut,dateFin);
    double moyenne2[4] = {0, 0, 0, 0};
    testObtenirMoyenne[1] = verificationMoyenne(dateDebut, dateFin, v2, moyenne2);
    dateDebut = "2021-05-28";
    dateFin= "2021-05-29";
    double*v3 = capteur.obtenirMoyenne(dateDebut,dateFin);
    double moyenne3[4] = {43.75, 75.25, 38.75, 50.5};
    testObtenirMoyenne[2] = verificationMoyenne(dateDebut, dateFin, v3, moyenne3);
    dateDebut = "2021-05-01";
    dateFin= "2021-05-20";
    double *v4 = capteur.obtenirMoyenne(dateDebut, dateFin);
    double moyenne4[4] = {32.25, 82.75, 39.75, 45.25};
    testObtenirMoyenne[3] = verificationMoyenne(dateDebut, dateFin, v4, moyenne4);
    bool affichage = true;
    for(int i=0; i<4; i++) {
        if(!testObtenirMoyenne[i]) {
            affichage = false;
        }
    }
    if(affichage) {
        cout << "Tests unitaires obtenirMoyenne corrects." << endl << endl;
    } else {
        cout << "Tests unitaires obtenirMoyenne incorrects." << endl << endl;
    }
    cout << "-------------------------------------------------------------------" << endl << endl << endl << endl;
}

void afficherListe(list<Capteur> & liste) {
    int count = 1;
    if(!liste.empty()) {
        for (list<Capteur>::iterator it = liste.begin(); it != liste.end(); it++) {
            cerr << "Capteur " << count << " : "
                 << "latitude: " << it->getLatitude() << ", "
                 <<  "longitude: " << it->getLongitude() << endl;
            count++;
        }
    } else {
        cerr << "Liste vide" << endl;
    }
}

void testerObtenirCapteursRegion(){
    cout << "------------ TESTS UNITAIRES - OBTENIR CAPTEURS REGION ------------" << endl << endl;
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
    service.getListeCapteurs().push_back(c1);
    service.getListeCapteurs().push_back(c2);
    service.getListeCapteurs().push_back(c3);
    double longitude[3] = {46.5,46.5,44.1};
    double latitude[3] = {2.5,2.5,2.5};
    double rayonMax[3]={3.0,0.7,0.1};
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

    bool allTestsValides = true;
    auto it = listesAttendues.begin();
    for(int i = 0; i < 3; i++){
        list<Capteur> listeCapteursProches = service.obtenirCapteursRegion(longitude[i], latitude[i], dateDeb, dateFin, 0, rayonMax[i]);
        auto it_sousliste = (*it).begin();
        testsValides = true;
        if(listeCapteursProches.size()!=(*it).size()){
            testsValides=false;

        } else {
            for (auto itListeTrouvee = listeCapteursProches.begin(); itListeTrouvee != listeCapteursProches.end(); itListeTrouvee++) {
                if(!(*itListeTrouvee == *it_sousliste)) {
                    testsValides = false;
                }
                it_sousliste++;
            }
        }
        if(!testsValides) {
            allTestsValides = false;
            cerr << "Resultat erroné pour la détermination des capteurs proches" << endl
                 << "Région : latitude: " << latitude[i] << ", longitude: " << longitude[i] << ", rayonMax: " << rayonMax[i] << endl << endl
                 << "Resultat trouvé : " << endl;
            afficherListe(listeCapteursProches);
            cerr << endl << "Résultat attendu : " << endl;
            afficherListe((*it));
            cerr << endl;
        }

        it++;
    }
    if (!allTestsValides){
        cout<<"Tests unitaires obtenirCapteursRegion incorrect"<<endl << endl;
    }else{
        cout<<"Tests unitaires obtenirCapteursRegion corrects."<<endl << endl;
    }
    cout << "-------------------------------------------------------------------" << endl << endl << endl << endl;
}
/*
int main() {
    testerCalculerIndice();
    testerObtenirMesureDate();
    testerObtenirMoyenne();
    testerObtenirCapteursRegion();
    return 0;
}*/