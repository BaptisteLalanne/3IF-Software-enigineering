/*
#include <iostream>
using namespace std;
#include "Service.h"
#include <string>
Service service = Service();

void testerCalculerIndice(){
        const string date="25/05/2021";
        Mesure mesure1= new Mesure(date, idMesure, 36.0, 240.0, 300.0, 55.0);
        Mesure mesure1= new Mesure(&date,&idMesure, 36.0, 240.0, 300.0, 55.0);
        Mesure mesure1= new Mesure(&date,&idMesure, 36.0, 240.0, 300.0, 55.0);
    Mesure mesure1= new Mesure(&date,&idMesure, 36.0, 240.0, 300.0, 55.0);

    Mesure(const string &laDate, string idMesure, double concentrationPM, double concentrationOzone, double concentrationDioxydeSoufre, double concentrationDioxydeAzote);


}


/*fonctions à tester:
calculer Indice (Mesure)
obtenirMesureDate (Capteur)
obtenirMoyenne (Capteur)
calculerMoyenneQualiteAir -> déjà fait dans les tests de bout en bout
verifierFonctionnement -> déjà fait dans les tests de bout en bout
obtenirCapteursRegion (Service)
obtenirDensiteRegion
comparerDates


int main (int argc, char * argv[]){
    testerCalculerIndice();
testerObtenirMesureDate
 }

 */