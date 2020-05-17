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
    Estafeta(string n, string ni, T id) {
        nome = n;
        nif = ni;
        pos = id;
    }

    string getNome() {
        return nome;
    }

    void setNome(string n) {
        nome = n;
    }

    string getNif() {
        return nif;
    }

    void setNif(string n) {
        nif = n;
    }

    T getPos() {
        return pos;
    }

    void setPos(T v) {
        pos = v;
    }

    MeioTransporte getTransporte() {
        return transporte;
    }

    void setTransporte(MeioTransporte t) {
        transporte = t;
    }

};

#endif //CAL_FP05_ESTAFETA_H
