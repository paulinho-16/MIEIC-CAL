#ifndef CAL_FP05_ESTAFETA_H
#define CAL_FP05_ESTAFETA_H

#include "MeioTransporte.h"

using namespace std;

template <class T>
class Estafeta {
    string nome;
    string nif;
    T pos;
    MeioTransporte transporte;
public:
    string getNome();
    void setNome(string n);
    string getNif();
    void setNif(string n);
    T getPos();
    void setPos(T v);
    MeioTransporte getTransporte();
    void setTransporte(MeioTransporte t);

};

#endif //CAL_FP05_ESTAFETA_H
