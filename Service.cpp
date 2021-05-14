
#include "Service.h"
#include <cmath>
#include <chrono>
#include <thread>

Service::Service(){

}

Service::~Service() {

}

/*
void Service::seConnecter(string utilisateurID) {

}*/

void Service::verifierFonctionnementCapteur() {

    double moyenne[4];
    double distanceCarreeEntreCapteurs;
    Mesure * moyenneDate;
    double moyenneDateTab[4];
    int nombreDonneesComparaison;
    const int differencePourFiabilite = 3;
    const double rayonVerification = 0.8;
    Mesure * mesureMoyenne;
    list<Capteur> capteursProches;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    for (auto & capteur : listeCapteurs){

        for(auto & capteur2 : listeCapteurs){
            distanceCarreeEntreCapteurs = pow((capteur.getLongitude()-capteur2.getLongitude()),2) + pow((capteur.getLatitude()-capteur2.getLatitude()),2);
            if(distanceCarreeEntreCapteurs <= pow(rayonVerification,2)) {
                capteursProches.push_back(capteur2);
            }
        }

        for(auto & mesure : capteur.getListeMesures()){
            for (int i=0;i<3;i++){
                moyenne[i]=0;
            }
            nombreDonneesComparaison=0;
            for(auto & capteurComp : capteursProches){
                if(capteurComp.obtenirMesureDate(mesure.getDateMesure()) != nullptr){
                    moyenneDate= capteurComp.obtenirMesureDate(mesure.getDateMesure());
                    moyenneDateTab[0]=moyenneDate->getParticulesFines();
                    moyenneDateTab[1]=moyenneDate->getOzone();
                    moyenneDateTab[2]=moyenneDate->getDioxydeSoufre();
                    moyenneDateTab[3]=moyenneDate->getDioxydeAzote();
                    for(int i=0;i<4;i++){
                        moyenne[i]+=moyenneDateTab[i];
                        nombreDonneesComparaison ++;
                    }
                }
            }
            if(nombreDonneesComparaison >=2){
                for(int i=0; i<4; i++){
                    moyenne[i]/=nombreDonneesComparaison;
                }
                mesureMoyenne = new Mesure("", "", moyenne[0],moyenne[1], moyenne[2],moyenne[3]);
                if((abs(mesureMoyenne->calculerIndice() - mesure.calculerIndice()))>differencePourFiabilite){
                    capteur.desactiverCapteur();
                    if(capteur.getUtilisateurPrive()){
                        capteur.getUtilisateurPrive()->empecherGagnerPoints();
                        break;
                    }
                }
            }else{
                capteur.desactiverCapteur();
                if(capteur.getUtilisateurPrive()!=nullptr){
                    capteur.getUtilisateurPrive()->empecherGagnerPoints();
                    break;
                }
            }
        }
        capteursProches.clear();
    }
    delete mesureMoyenne;
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";
}


/*
 *
int Service::calculerMoyenneQualiteAir(double longitude, double latitude, double rayon, string dateDebut, string dateFin){
    double[4] moyenne;
    int nombreCapteursValides;
    list<Capteur> capteursProches = obtenirCapteursRegion(longitude,latitude,rayon,dateDebut,dateFin);
    double densite = obtenirDensiteRegion(capteursProches,longitude,latitude,rayon);
    for( const Capteur & capteur : lst){
        double* moyenneTousPolluants = capteur.obtenirMoyenne(dateDebut,dateFin);
        for(int i = 0 ; i < 4; i++ ){
            moyenne[i] = moyenne[i] + moyenneTousPolluants[i];
        }
        nombreCapteursValides++;
        if( capteur.getUtilisateurPrive() != nullptr ) {
            capteur.getUtilisateurPrive().donnerPoints();
        }
    }

    //On fait la moyenne des concentrations
    for(int j = 0; j<4; j++){
        moyenne[i]= moyenne[i]/ nombreCapteursValides;
    }

    mesureMoyenne = new Mesure("", "", moyenne[0],moyenne[1], moyenne[2],moyenne[3]);
    indiceRegion = mesureMoyenne.calculerIndice();


    if(densite > 0.5){
        cout << "La moyenne dans la région est de "<< moyenne << endl;
    }else if (densite == 0){
        cerr << "Aucune données dans la zone sélectionnée << endl;
        return -1;
    }else{
        cout << "Attention, la zone sélectionnée n'est couverte par les capteurs qu'à " << densite*100 <<"%. La moyenne
        est de" << moyenne <<endl;
    }
}


list<Capteur> Service :: obtenirCapteursRegion(double longitude, double latitude, string dateDeb, string dateFin, double rayonMax, double rayonMin){
    Capteur * capteur;
    double distanceCarreeCapteurRegion;
    list<double> tableauDistances;
    list<Capteur> listeCapteursRegion;
    for(auto & capteur : listeCapteurs){
        if(capteur.getFiable()) {
            if(capteur.getPremiereMesure()<= dateDebut && capteur.getDateDerniereMesure()>=dateFin) {
                distanceCarreeCapteurRegion=pow(capteur.getLongitude()-centreRegionLongitude,2)+pow(capteur.getLatitude()-centreRegionLatitude,2);
                if(distanceCarreCapteurRegion>pow(rayonMinRegion,2) && distanceCarreeCapteurRegion<=pow(rayonMaxRegion,2)){
                    list<double>::iterator it;
                    list<Capteur>::iterator itCapteur;
                    it = tableauDistances.begin();
                    itCapteur = listeCapteursRegion.begin();
                    for(int i=0; i<tableauDistances.size(){
                        if(tableauDistances.isEmpty() || distanceCarreeCapteurRegion<it) {
                            tableauDistances.insert(it,distanceCarreeCapteurRegion);
                            listeCapteursRegion.insert(itCapteur,capteur);
                            it++;
                            itCapteur++;
                            break;
                        }
                    }
                    if(i==tableauDistances.size()) {
                        tableauDistances=push_back(distanceCarreeCapteurRegion);
                        listeCapteursRegion = push_back(capteur);
                    }
                }
            }
        }
    }
}


double Service:: obtenirDensiteRegion(list<Capteur> listeDesCapteurs, double longitude, double latitude, double rayonRegion){ //centreRegionLongitude = longitude
    int compteurPresenceCapteur=0;
    int precision = 3;
    int rayonMesureCapteur = 0.4*pow(10, precision);
    double centreCapteurLongitude, centreCapteurLatitude, compteurZoneRegion;
    int tailleCarte = 2*rayonRegion*pow(10, precision), debutMesureCapteurLongitude, finMesureCapteurLongitude, debutMesureCapteurLatitude, finMesureCapteurLatitude;
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
                            compteurPresenceCapteur=compteurPresenceCapteur+1;
                        }
                    }
                }
            }
        }
    }
    compteurZoneRegion=pow(tailleCarte,2)*3.14159*pow(rayonRegion,2)/(2*pow(rayonRegion,2));
    double densite = 100*compteurPresenceCapteur/compteurZoneRegion;
    return densite;

}
*/


