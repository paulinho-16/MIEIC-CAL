#ifndef CAL_FP05_ESTAFETA_H
#define CAL_FP05_ESTAFETA_H

#include "Graph.h"
#include "MeioTransporte.h"

using namespace std;

template <class T>
class Estafeta {
    string nome;
    string nif;
    Vertex<T> pos;
    MeioTransporte transporte;
public:
    string getNome();
    void setNome(string n);
    string getNif();
    void setNif(string n);
    Vertex<T> getPos();
    void setPos(Vertex<T> v);
    MeioTransporte getTransporte();
    void setTransporte(MeioTransporte t);

};

#endif //CAL_FP05_ESTAFETA_H
