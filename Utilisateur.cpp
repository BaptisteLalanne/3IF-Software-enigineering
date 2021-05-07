using namespace std;
#include <iostream>

#include "Utilisateur.h"




Utilisateur::Utilisateur(const string & utilisateurID) {
    Utilisateur::utilisateurID = utilisateurID;
    points = 0;
    gagnePoints = true;
}


Utilisateur::~Utilisateur ( )
{

}
void Utilisateur::donnerPoints(){
    points++;
}
void Utilisateur::addCapteur(Capteur & capteur) {
    listeCapteurs.push_back(capteur);
    capteur.setUtilisateur(this);
}

void Utilisateur::afficherCapteurs() {
    for(list<Capteur>::iterator it = listeCapteurs.begin(); it != listeCapteurs.end(); it++) {
        cout << *it << endl;
    }
}

ostream &operator<<(ostream &os, const Utilisateur &utilisateur) {
    os << "UserID: " << utilisateur.utilisateurID << " points: " << utilisateur.points;
    return os;
}




//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées