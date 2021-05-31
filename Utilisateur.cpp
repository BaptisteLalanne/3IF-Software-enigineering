using namespace std;

#include <iostream>
#include "Utilisateur.h"

Utilisateur::Utilisateur(const string &utilisateurID_) {
    utilisateurID = utilisateurID_;
    points = 0;
    gagnePoints = true;
}

Utilisateur::~Utilisateur() {

}

void Utilisateur::donnerPoints() {
    points++;
}

void Utilisateur::empecherGagnerPoints() {
    gagnePoints = false;
}

void Utilisateur::addCapteur(Capteur &capteur) {
    listeCapteurs.push_back(capteur);
    capteur.setUtilisateur(this);
}

ostream &operator<<(ostream &os, const Utilisateur &utilisateur) {
    os << "UserID: " << utilisateur.utilisateurID << " points: " << utilisateur.points;
    return os;
}
