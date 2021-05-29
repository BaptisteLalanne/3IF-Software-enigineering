using namespace std;
#include <iostream>

#include "Mesure.h"

Mesure::Mesure(){
}

Mesure::Mesure(const string &laDate, string idMesure, double concentrationOzone, double concentrationDioxydeSoufre, double concentartionDioxydeAzote, double concentrationPM)
{
    dateMesure = laDate;
    id = idMesure;
    particulesFines = concentrationPM;
    ozone = concentrationOzone;
    dioxydeSoufre = concentrationDioxydeSoufre;
    dioxydeAzote = concentartionDioxydeAzote;
}

Mesure::~Mesure() {

}

int Mesure::calculerIndice() {
    int indice;

    if(ozone>=240 || dioxydeSoufre>=500 || dioxydeAzote>=400 || particulesFines>=80) {
        indice = 10;
    }
    else if(ozone>=210 || dioxydeSoufre>=400 || dioxydeAzote>=275 || particulesFines>=65) {
        indice = 9;
    }
    else if(ozone>=180 || dioxydeSoufre>=300 || dioxydeAzote>=200 || particulesFines>=50) {
        indice = 8;
    }
    else if(ozone>=150 || dioxydeSoufre>=250 || dioxydeAzote>=165 || particulesFines>=42) {
        indice = 7;
    }
    else if(ozone>=130 || dioxydeSoufre>=200 || dioxydeAzote>=135 || particulesFines>=35) {
        indice = 6;
    }
    else if(ozone>=105 || dioxydeSoufre>=160 || dioxydeAzote>=110 || particulesFines>=28) {
        indice = 5;
    }
    else if(ozone>=80 || dioxydeSoufre>=120 || dioxydeAzote>=85 || particulesFines>=21) {
        indice = 4;
    }
    else if(ozone>=55 || dioxydeSoufre>=80 || dioxydeAzote>=55 || particulesFines>=14) {
        indice = 3;
    }
    else if(ozone>=30 || dioxydeSoufre>=40 || dioxydeAzote>=30 || particulesFines>=7) {
        indice = 2;
    }
    else {
        indice = 1;
    }

    return indice;


}


const string& Mesure::getId() const {
    return id;
}

void Mesure::setDateMesure(const string &dateMesure) {
    cout << dateMesure << endl;
}

double Mesure::getOzone() const {
    return ozone;
}

void Mesure::setOzone(double ozone) {
    this->ozone = ozone;
}

double Mesure::getDioxydeAzote() const{
    return dioxydeAzote;
}

void Mesure::setDioxydeAzote(double dioxydeAzote) {
    this->dioxydeAzote = dioxydeAzote;
}

double Mesure::getDioxydeSoufre() const{
    return dioxydeSoufre;
}

void Mesure::setParticulesFines(double particulesFines) {
    this->particulesFines = particulesFines;
}

double Mesure::getParticulesFines() const{
    return particulesFines;
}

string& Mesure::getDateMesure(){
    return dateMesure;
}

ostream &operator<<(ostream &os, const Mesure &mesure) {
    os << "id: " << mesure.id << " dateMesure: " << mesure.dateMesure << " ozone: " << mesure.ozone << " dioxydeAzote: "
       << mesure.dioxydeAzote << " dioxydeSoufre: " << mesure.dioxydeSoufre << " particulesFines: "
       << mesure.particulesFines;
    return os;
}