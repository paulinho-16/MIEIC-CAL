#ifndef CAL_FP05_CLIENTE_H
#define CAL_FP05_CLIENTE_H

#include "Graph.h"
#include <string>

using namespace std;

template <class T>
class Cliente {
    Vertex<T>* morada;
    string nome;
    string nif;
public:
    Cliente(string n, string ni, int id);
    string getNome();
    void setNome(string n);
    Vertex<T>* getMorada();
    void setMorada(Vertex<T>* morada);
    string getNif();
    void setNif(string n);
};

#endif //CAL_FP05_CLIENTE_H
