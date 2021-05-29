#define _USE_MATH_DEFINES
#include "Service.h"
#include <cmath>
#include <chrono>
#include <thread>
#include <cstring>
#include <sstream>

Service::Service(){

}

Service::~Service() {

}



void Service::addListeCapteurs(Capteur & capteur) {
    this->listeCapteurs.push_back(capteur);
}

list<Capteur>& Service::getListeCapteurs() {
    return this->listeCapteurs;
}

double Service::distanceDeuxPointsTerre(double latitudeA, double longitudeA,double latitudeB,double longitudeB){
    int rayonTerre = 6373;
    return rayonTerre*acos(sin(latitudeA)*sin(latitudeB)+cos(latitudeA)*cos(latitudeB)*cos(longitudeB-longitudeA));
}

void Service::verifierFonctionnementCapteur() {

    double moyenne[4];
    double distanceEntreCapteurs;
    Mesure *moyenneDate;
    double moyenneDateTab[4];
    int nombreDonneesComparaison;
    const int differencePourFiabilite = 2;
    const double rayonVerification = 0.75;
    const int nbVoisinsRequis = 2;
    Mesure *mesureMoyenne;
    list<Capteur> capteursProches;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    //auto t1 = high_resolution_clock::now();
    for (auto & capteur : listeCapteurs) {

        for (auto &capteur2 : listeCapteurs) {
            if (capteur2.getId() != capteur.getId()) {
                distanceEntreCapteurs = distanceDeuxPointsTerre(capteur2.getLatitude(),capteur2.getLongitude(),capteur.getLatitude(),capteur.getLongitude());
                if (distanceEntreCapteurs <= rayonVerification) {
                    capteursProches.push_back(capteur2);
                }
            }
        }

        for (auto &mesure : capteur.getListeMesures()) {
            for (int i = 0; i < 3; i++) {
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
    //auto t2 = high_resolution_clock::now();
    //auto ms_int = duration_cast<milliseconds>(t2 - t1);
    //std::cout << ms_int.count() << "ms\n";
}




bool Service::comparerDates(const string date1, const string date2){
    istringstream flux1(date1);
    istringstream flux2(date2);
    string jour1, jour2, mois1, mois2, annee1, annee2;
    getline(flux1, annee1, '-');
    getline(flux1, mois1, '-');
    getline(flux1, jour1);
    getline(flux2, annee2, '-');
    getline(flux2, mois2, '-');
    getline(flux2,jour2);

    return(strcmp(annee1.c_str(),annee2.c_str())==-1 || (strcmp(annee1.c_str(), annee2.c_str())==0 && strcmp(mois1.c_str(), mois2.c_str())==-1) || (strcmp(annee1.c_str(), annee2.c_str())==0 && strcmp(mois1.c_str(), mois2.c_str())==-1 && (strcmp(jour1.c_str(), jour2.c_str())==-1 || strcmp(jour1.c_str(),jour2.c_str())==0) )) ;
}


list<Capteur> Service::obtenirCapteursRegion(double centreRegionLongitude, double centreRegionLatitude, string dateDebut, string dateFin, double rayonMinRegion, double rayonMaxRegion){
    Capteur * capteur;
    list<double> tableauDistances;
    list<Capteur> listeCapteursRegion;
    for(auto & capteur : listeCapteurs){
        if(capteur.getFiable()) {
            if(strcmp(capteur.getPremiereMesure().c_str(),dateDebut.c_str()) <= 0 && strcmp(capteur.getDerniereMesure().c_str(),dateFin.c_str())>=0) {
                double distanceCapteurRegion= distanceDeuxPointsTerre(capteur.getLatitude(), capteur.getLongitude(), centreRegionLatitude, centreRegionLongitude);
                if(distanceCapteurRegion >= rayonMinRegion && distanceCapteurRegion <= rayonMaxRegion){
                    list<Capteur>::iterator itCapteur = listeCapteursRegion.begin();
                    list<double>::iterator it;
                    for(it = tableauDistances.begin(); it != tableauDistances.end(); it++){
                        if(tableauDistances.empty() || distanceCapteurRegion < *it) {
                            tableauDistances.insert(it, distanceCapteurRegion);
                            listeCapteursRegion.insert(itCapteur,capteur);
                            break;
                        }
                        itCapteur++;
                    }
                    if(it==tableauDistances.end()) {
                        tableauDistances.push_back(distanceCapteurRegion);
                        listeCapteursRegion.push_back(capteur);
                    }
                }
            }
        }
    }
    return listeCapteursRegion;
}


double Service:: obtenirDensiteRegion(list<Capteur> listeDesCapteurs, double longitude, double latitude, double rayonRegion, double rayonMesCapteur){ //centreRegionLongitude = longitude
    int compteurPresenceCapteur = 0;
    const int precision = 1;
    const int rayonMesureCapteur = rayonMesCapteur*pow(10, precision);
    int tailleCarte = 2*rayonRegion*pow(10, precision);
    int debutMesureCapteurLongitude, finMesureCapteurLongitude, debutMesureCapteurLatitude, finMesureCapteurLatitude, centreCapteurLongitude, centreCapteurLatitude;
    bool ** carte = new bool*[tailleCarte];
    for (int i = 0; i < tailleCarte; i++) {
        carte[i] = new bool[tailleCarte];
        for(int j = 0; j < tailleCarte; j++) {
            carte[i][j] = false;
        }
    }
    int rayonTailleTab = rayonRegion*pow(10,precision);

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

        for(int i=debutMesureCapteurLongitude; i<finMesureCapteurLongitude; i++) {
            for(int j=debutMesureCapteurLatitude; j<finMesureCapteurLatitude; j++) {
                if(pow(i-centreCapteurLongitude,2)+pow(j-centreCapteurLatitude,2)<=pow(rayonMesureCapteur,2)) {
                    if(pow(i-rayonTailleTab,2)+pow(j-rayonTailleTab,2)<=pow(rayonTailleTab,2)) {
                        if(!carte[j][i]) {
                            carte[j][i]=true;
                            compteurPresenceCapteur++;
                        }
                    }
                }
            }
        }
    }

    double compteurZoneRegion=pow(tailleCarte/2,2)*M_PI;
    double densite = 100*compteurPresenceCapteur/compteurZoneRegion;
    cout << "densité est " << densite << endl;
    for (int i = 0; i < tailleCarte; i++) {
        delete[] carte[i];
    }
    delete[] carte;
    return densite;

}

void Service::calculerMoyenneQualiteAir(double longitude, double latitude, double rayon, string dateDebut, string dateFin){
    double moyenne[4];
    int nombreCapteursValides = 0;
    for (double & i : moyenne) {
        i = 0;
    }
    double rayonMesureCapteur = 0.4;
    list<Capteur> capteursProches = obtenirCapteursRegion(longitude, latitude, dateDebut, dateFin, 0, rayon + rayonMesureCapteur);
    if(capteursProches.empty()){
        cerr << "Aucune donnée dans la zone ou au cours de la période sélectionnée" << endl;
        return;
    }

    for(Capteur & capteur : capteursProches){
        double* moyenneTousPolluants = capteur.obtenirMoyenne(dateDebut,dateFin);
        for(int i = 0 ; i < 4; i++ ){
            moyenne[i] = moyenne[i] + moyenneTousPolluants[i];
        }
        nombreCapteursValides++;
        if( capteur.getUtilisateurPrive() != nullptr ) {
            capteur.getUtilisateurPrive()->donnerPoints();
        }
    }

    //On fait la moyenne des concentrations
    for(int i = 0; i<4; i++){
        moyenne[i]= moyenne[i]/ nombreCapteursValides;
    }

    Mesure * mesureMoyenne = new Mesure("", "", moyenne[0],moyenne[1], moyenne[2],moyenne[3]);
    int indiceRegion = (*mesureMoyenne).calculerIndice();

    double densite = obtenirDensiteRegion(capteursProches,longitude,latitude,rayon,rayonMesureCapteur);
    if(densite > 0.5){
        cout << "L'indice ATMO dans la région est de "<< indiceRegion << endl;
    }else{
        cout << "Attention, la zone sélectionnée n'est couverte par les capteurs qu'à " << densite*100 <<"%. La moyenne est de " << indiceRegion <<"." << endl;
    }
}
