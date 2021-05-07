
#include "Service.h"
#include <cmath>

Service::Service(){

}

Service::~Service() {

}

/*
void Service::seConnecter(string utilisateurID) {

}*/
/*
void Service::verifierFonctionnementCapteur() {

    double moyenne[4];
    double distanceCarreeEntreCapteurs;
    Mesure moyenneDate=Mesure();
    double moyenneDateTab[4];
    int nombreDonneesComparaison;
    const int differencePourFiabilite=2;
    Mesure mesureMoyenne=Mesure();
    list<Capteur> capteursProches;
    for (int i=0;i<3;i++){
        moyenne[i]=0;
        moyenneDateTab[i]=0;
    }

    for (auto & capteur : listeCapteurs){
        for(auto & capteur2 : listeCapteurs){
            distanceCarreeEntreCapteurs = pow((capteur.getLongitude()-capteur2.getLongitude()),2) + (capteur.getLatitude()-capteur2.getLatitude()),2);
            if(distanceCarreeEntreCapteurs <= pow(1.0,2)){
                capteursProches.push_back(capteur2);
            }
        }

        for(auto & mesure : capteur.getListeMesures()){
            nombreDonneesComparaison=0;
            for(auto & capteurComp : capteursProches){
                if(capteurComp.obtenirMesureDate(mesure.getDateMesure())!=nullptr){
                    moyenneDate= *(capteurComp.obtenirMesureDate(mesure.getDateMesure()));
                    moyenneDateTab[0]=moyenneDate.getParticulesFines();
                    moyenneDateTab[1]=moyenneDate.getOzone();
                    moyenneDateTab[2]=moyenneDate.getDioxydeSoufre();
                    moyenneDateTab[3]=moyenneDate.getDioxydeAzote();
                    for(int i=0;i<4;i++){
                        moyenne[i]+=moyenneDateTab[i];
                        nombreDonneesComparaison ++;
                    }
                }
            }
            if(nombreDonneesComparaison >=3){
                for(int i=0; i<4; i++){
                    moyenne[i]/=nombreDonneesComparaison;
                }
                //mesureMoyenne=Mesure(moyenne[0],moyenne[1], moyenne[2],moyenne[3]);
                if((abs(mesureMoyenne.calculerIndice() - mesure.calculerIndice()))>differencePourFiabilite){
                    capteur.desactiverCapteur();
                    if(capteur.getCapteurPrive()){
                        capteur.getUtilisateur(Prive().empecherGagnerPoints();
                        break;
                    }
                }
            }else{
                capteur.desactiverCapteur();
                if(capteur.getUtilisateur()!=nullptr){
                    *(capteur.getUtilisateur()).empecherGagnerPoints();
                    break;
                }
            }
        }
    }
}*/

/*
 *
int Service::calculerMoyenneQualiteAir(double longitude, double latitude, double rayon, string dateDebut, string dateFin){
    double[4] moyenne;
    int nombreCapteursValides;
    list<Capteur> capteursProches = obtenirCapteursRegion(longitude,latitude,rayon,dateDebut,dateFin);
    double densite = obtenirDensiteRegion(capteursProches,longitude,latitude);
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

    //On fait la moyenne des concetrations
    for(int j = 0; j<4; j++){
        moyenne[i]= moyenne[i]/ nombreCapteursValides;
    }

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

}

double Service:: obtenirDensiteRegion(list<Capteur> listeCapteurs, double longitude, double latitude){

}*/

