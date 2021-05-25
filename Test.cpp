#include <iostream>
using namespace std;
#include "Service.h"
#include "Mesure.h"
#include "Capteur.h"
#include <string>
#include <cassert>

Service service = Service();

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



void testerVerifierFonctionnement(){

}

void testerObtenirCapteursRegion(){

}

void testerCalculerMoyenneQualiteAir(){

}

void testerComparerDates(){
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


/*fonctions à tester:
calculer Indice (Mesure) --------------fait
obtenirMesureDate (Capteur) -----------fait



obtenirMoyenne (Capteur)
calculerMoyenneQualiteAir -> déjà fait dans les tests de bout en bout
verifierFonctionnement -> déjà fait dans les tests de bout en bout
obtenirCapteursRegion (Service)
comparerDates -------------------------fait, penser à modifier comparesDates dans Service.cpp
obtenirDensiteRegion
*/

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