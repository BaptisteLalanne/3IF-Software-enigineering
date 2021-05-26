#include <iostream>
using namespace std;
#include "Service.h"
#include "Mesure.h"
#include "Capteur.h"
#include <string>
#include <cassert>


void testerCalculerIndice(){
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


void testerObtenirMesureDate(){
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

void testerObtenirMoyenne(){
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
    dateDebut = "29/05/2021";
    dateFin= "30/05/2021";
    double* v2 = capteur.obtenirMoyenne(dateDebut,dateFin);
    dateDebut = "28/05/2021";
    dateFin= "29/05/2021";
    double*v3 = capteur.obtenirMoyenne(dateDebut,dateFin);
}
/*

void testerObtenirCapteursRegion(){
    bool testsValides=true;
    Service service = Service();
    string dateDeb="2021-05-26":
    string dateFin="2021-05-27";
    Capteur c1 = Capteur("001", 46.4, 2.5, dateRef);
    Capteur c2 = Capteur("002", 47.2, 2.5, dateRef);
    Capteur c3 = Capteur("003", 46.4, 3.2, dateRef);
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
    listesAttendues.push_back(listeTest1, listeTest2, listeTest3);

    for(int i = 0, i < listeCapteurs.size(); i++){
        list<Capteur> listeCapteursProches=service.obtenirCapteursRegion(longitude[i],latitude[i],dateDeb,dateFin, 0, rayonMax[i]); //
        for(int j=0; j<listeCapteursProches.size();j++){
            if(listeCapteursProches.size()!=listesAttendues[i].size()){
                testsValides=false;
                break;
            }
            list<Capteur>::iterator iter;
            iter = find (listeCapteursProches.begin(), listeCapteursProches.end(), listesAttendues[i][j]);
            if(iter==listeCapteursProches.end()){
                testsValides=false;
            }
        }
        if(testsValides==false){
        cerr<<"Resultat erroné pour la détermination des capteurs proches: \n"
                "Resultat trouvé :"<< afficherListe(listeCapteursProches) << "\n"<<
                "Résultat attendu : "<< afficherListe(listesAttendues[i]) << endl;
        }
    }
}


list<Capteur> Service::obtenirCapteursRegion(double centreRegionLongitude, double centreRegionLatitude, string dateDebut, string dateFin, double rayonMinRegion, double rayonMaxRegion){
    Capteur * capteur;
    list<double> tableauDistances;
    list<Capteur> listeCapteursRegion;
    for(auto & capteur : listeCapteurs){
        if(capteur.getFiable()) {
            if(comparerDates(capteur.getPremiereMesure(),dateDebut) && comparerDates(capteur.getDerniereMesure(),dateFin)) {
                double distanceCarreeCapteurRegion=pow(capteur.getLongitude()-centreRegionLongitude,2)+pow(capteur.getLatitude()-centreRegionLatitude,2);
                if(distanceCarreeCapteurRegion>=pow(rayonMinRegion,2) && distanceCarreeCapteurRegion<=pow(rayonMaxRegion,2)){
                    list<Capteur>::iterator itCapteur = listeCapteursRegion.begin();
                    list<double>::iterator it;
                    for(it = tableauDistances.begin(); it != tableauDistances.end(); it++){
                        if(tableauDistances.empty() || distanceCarreeCapteurRegion<*it) {
                            tableauDistances.insert(it,distanceCarreeCapteurRegion);
                            listeCapteursRegion.insert(itCapteur,capteur);
                            break;
                        }
                        itCapteur++;
                    }
                    if(it==tableauDistances.end()) {
                        tableauDistances.push_back(distanceCarreeCapteurRegion);
                        listeCapteursRegion.push_back(capteur);
                    }
                }
            }
        }
    }
    return listeCapteursRegion;
}*/

void testerComparerDates(){
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

void afficherListe(list<Capteur> liste) {
    int count = 1;
    for(list<Capteur>::iterator it = liste.begin(); it != liste.end(); it++) {
        cout << "Capteur "<< count << ":\n"
        << "latitude: " << it->getLatitude() <<"\n"
        << "longitude: " << it->getLongitude() <<"\n\n";
        count++;
    }
    cout <<"\n\n\n";
}



/*
double Service:: obtenirDensiteRegion(list<Capteur> listeDesCapteurs, double longitude, double latitude, double rayonRegion){ //centreRegionLongitude = longitude
    int compteurPresenceCapteur = 0;
    const int precision = 3;
    const int rayonMesureCapteur = 0.4*pow(10, precision);
    int tailleCarte = 2*rayonRegion*pow(10, precision);
    int debutMesureCapteurLongitude, finMesureCapteurLongitude, debutMesureCapteurLatitude, finMesureCapteurLatitude, centreCapteurLongitude, centreCapteurLatitude;
    bool carte[tailleCarte][tailleCarte];
    for (auto & capteur : listeDesCapteurs){
        centreCapteurLongitude = (capteur.getLongitude()-(longitude-rayonRegion))*pow(10, precision);
        centreCapteurLatitude = (capteur.getLatitude()-(latitude-rayonRegion))*pow(10, precision);
        debutMesureCapteurLongitude = centreCapteurLongitude - rayonMesureCapteur;
        if(debutMesureCapteurLongitude<0) {
            debutMesureCapteurLongitude=0;
        }
        finMesureCapteurLongitude = centreCapteurLongitude+rayonMesureCapteur;
        if(finMesureCapteurLongitude>=tailleCarte) {
            finMesureCapteurLongitude=tailleCarte-1;
        }
        //Ligne 46 pseudocode
        debutMesureCapteurLatitude=centreCapteurLatitude-rayonMesureCapteur;
        if(debutMesureCapteurLatitude<0) {
            debutMesureCapteurLatitude=0;
        }
        finMesureCapteurLatitude=centreCapteurLatitude+rayonMesureCapteur;
        if(finMesureCapteurLatitude>=tailleCarte) {
            finMesureCapteurLatitude=tailleCarte-1;
        }
        //ligne 54 pseudocode
        for(int i=debutMesureCapteurLongitude; i<finMesureCapteurLongitude; i++) {
            for(int j=debutMesureCapteurLatitude; j<finMesureCapteurLatitude; j++) {
                if(pow(i-longitude,2)+pow(j-latitude,2)<=pow(rayonMesureCapteur,2)) {
                    rayonRegion = rayonRegion*pow(10,precision);
                    if(pow(i-rayonRegion,2)+pow(j-rayonRegion,2)<=pow(rayonRegion,2)) {
                        if(!carte[j][i]) {
                            carte[j][i]=true;
                            compteurPresenceCapteur++;
                        }
                    }
                }
            }
        }
    }
    double compteurZoneRegion=pow(tailleCarte,2)*M_PI*pow(rayonRegion,2)/(2*pow(rayonRegion,2));
    double densite = 100*compteurPresenceCapteur/compteurZoneRegion;
    cout << "densité est" << densite << endl;
    return densite;

}*/

/*fonctions à tester:
calculer Indice (Mesure) --------------fait
obtenirMesureDate (Capteur) -----------fait
obtenirMoyenne (Capteur)-----------en cours
calculerMoyenneQualiteAir -> déjà fait dans les tests de bout en bout
verifierFonctionnement -> déjà fait dans les tests de bout en bout
obtenirCapteursRegion (Service)--------fait
comparerDates -------------------------fait, penser à modifier comparesDates dans Service.cpp
obtenirDensiteRegion



int main (int argc, char * argv[]) {
    testerCalculerIndice();
    testerObtenirMesureDate();
    testerObtenirMoyenne();
    testerCalculerMoyenneQualiteAir();
    testerVerifierFonctionnement();
    testerObtenirCapteursRegion();
    testerComparerDates();
    return 0;
}
 */