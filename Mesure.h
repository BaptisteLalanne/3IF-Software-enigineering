#ifndef PROJETCAPTEUR_MESURE_H
#define PROJETCAPTEUR_MESURE_H
using namespace std;
#include <string>
#include <ostream>

class Mesure
{
public:
    int calculerIndice();

    const string &getId() const ;

    void setDateMesure(const string &dateMesure);

    double getOzone() const ;

    void setOzone(double ozone);

    double getDioxydeAzote() const;

    void setDioxydeAzote(double dioxydeAzote);

    double getDioxydeSoufre() const;

    void setParticulesFines(double particulesFines);

    double getParticulesFines() const;

    virtual ~Mesure();

    string& getDateMesure();

    Mesure();
    Mesure(const string &laDate, string idMesure, double concentrationOzone, double concentrationDioxydeSoufre, double concentrationDioxydeAzote, double concentrationPM);

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
