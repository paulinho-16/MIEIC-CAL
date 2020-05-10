#ifndef CAL_FP05_RESTAURANTE_H
#define CAL_FP05_RESTAURANTE_H

#include "Graph.h"

template <class T>
class Restaurante {
    string nome;
    string descricao;
    Vertex<T> morada;
public:
    Restaurante();
    string getNome();
    void setNome(string n);
    string getDescricao();
    void setDescricao(string d);
    Vertex<T> getMorada();
    void setMorada(Vertex<T> v);

};

#endif //CAL_FP05_RESTAURANTE_H
