#ifndef PROJETCAPTEUR_MESURE_H
#define PROJETCAPTEUR_MESURE_H
using namespace std;
#include <string>
#include <ostream>

class Mesure
{
public:
    int calculerIndice();

    const string &getId() const {
        return id;
    }

    void setDateMesure(const string &dateMesure) {
        this->dateMesure = dateMesure;
    }

    double getOzone() const {
        return ozone;
    }

    void setOzone(double ozone) {
        this->ozone = ozone;
    };

    double getDioxydeAzote() const{
        return dioxydeAzote;
    }

    void setDioxydeAzote(double dioxydeAzote) {
        this->dioxydeAzote = dioxydeAzote;
    }

    double getDioxydeSoufre() const{
            return dioxydeSoufre;
    }

    void setParticulesFines(double particulesFines) {
        this->particulesFines = particulesFines;
    }

    double getParticulesFines() const{
        return particulesFines;
    }

    virtual ~Mesure();

    string & getDateMesure(){
        return dateMesure;
    }

    Mesure();
    Mesure(const string &laDate, string idMesure, double concentrationPM, double concentrationOzone, double concentartionDioxydeSoufre, double concentrationDioxydeAzote);

    friend ostream &operator<<(ostream &os, const Mesure &mesure);

private:
    string id;
    string dateMesure;
    double ozone;
    double dioxydeAzote;
    double dioxydeSoufre;
    double particulesFines;
};

#endif
