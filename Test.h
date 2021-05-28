//
// Created by Rami EL RIFAI on 28/05/2021.
//

#ifndef PROJETCAPTEUR_TEST_H
#define PROJETCAPTEUR_TEST_H
class Test {

public:
    void mainTests();
    Test();
    virtual ~Test();

private :
    void testerCalculerIndice();
    void testerObtenirMesureDate();
    void afficherListe(list<Capteur> & liste);
    void testerObtenirMoyenne();
    void testerObtenirCapteursRegion();
    bool verificationMoyenne(string dateDebut, string dateFin, double *v, double *moyenne);
};
#endif //PROJETCAPTEUR_H
