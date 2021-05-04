#ifndef PROJETCAPTEUR_MESURE_H
#define PROJETCAPTEUR_MESURE_H
using namespace std;
#include <string>
#include <ostream>

class Mesure
{
public:
    int calculerIndice();

    virtual ~Mesure();

    const string& getDateMesure() const;

    Mesure(const string &laDate, string idMesure, double concentrationPM, double concentrationOzone, double concentartionDioxydeSoufre, double concentrationDioxydeAzote);

    void setDateMesure(const string &dateMesure);

    double getOzone() const;

    void setOzone(double ozone);

    double getDioxydeSoufre() const;

    void setDioxydeSoufre(double dioxydeSoufre);

    double getDioxydeAzote() const;

    void setDioxydeAzote(double dioxydeAzote);

    double getParticulesFines() const;

    void setParticulesFines(double particulesFines);

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
