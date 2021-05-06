
#include "Service.h"
#include <cmath>

Service::Service(){

}

Service::~Service() {

}

/*
void Service::seConnecter(string utilisateurID) {

}*/

void Service::verifierFonctionnementCapteur() {


    double moyenne[4];
    double moyenneDate, distanceCarreeEntreCapteurs;
    int nombreDonneesComparaison;
    const int differencePourFiabilite=2;
    Mesure mesureMoyenne;
    list<Capteur> capteursProches;
    for (int i=0;i<3;i++){
        moyenne[i]=0;
    }

    for (auto & capteur : listeCapteurs){
        for(auto & capteur2 : service.getListeCapteurs()){
            distanceCarreeEntreCapteurs = pow((capteur.getLongitude()-capteur2.getLongitude()),2) + (capteur.getLatitude()-capteur2.getLatitude()),2);
            if(distanceCarreeEntreCapteurs <= pow(1.0,2)){
                capteursProches.push_back(capteur2);
            }
        }

        for(auto & mesure : capteur.getListeMesures()){
            nombreDonneesComparaison=0;
            for(auto &c capteurComp : capteursProches){
                if(capteurComp.obtenirMesureDate(mesure.getDateMesure())!=null){
                    moyenneDate= capteurComp.obtenirMesureDate(mesure.getDate());
                    for(int i=0;i<4;i++){
                        moyenne[i]+=moyenneDate;
                        nombreDonneesComparaison ++;
                    }
                }
            }
            if(nombreDonneesComparaison >=3){
                for(int i=0; i<4; i++){
                    moyenne[i]/=nombreDonneesComparaison;
                }
                mesureMoyenne=Mesure(moyenne[0],moyenne[1], moyenne[2],moyenne[3]);
                if((abs(mesureMoyenne.calculerIndice() - mesure.calculerIndice()))>differencePourFiabilite){
                    capteur.desactiverCapteur();
                    if(capteur.getCapteurPrive()){
                        capteur.getUtilisateur().empecherGagnerPoints();
                        break;
                    }
                }
            }else{
                capteur.desactiverCapteur();
                if(capteur.getCapteurPrive()){
                    capteur.getUtilisateur().empecherGagnerPoints();
                    break;
                }
            }
        }
    }
}
/*
int Service::calculerMoyenneQualiteAir(double Longitude, double Latitude, double rayon, string dateDebut, string dateFin) {

}


list<Capteur> Service :: obtenirCapteursRegion(double longitude, double latitude, string dateDeb, string dateFin, double rayonMax, double rayonMin){

}

double Service:: obtenirDensiteRegion(list<Capteur> listeCapteurs, double longitude, double latitude){

}*/

