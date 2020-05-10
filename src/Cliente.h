//
// Created by Mariana Ramos on 06/05/2020.
//

#ifndef CAL_FP05_CLIENTE_H
#define CAL_FP05_CLIENTE_H

//#include "Graph.h"

template <class T>
class Cliente {
    Vertex<T> morada;
    string nome;
    string nif;
public:
    Cliente();
    string getNome();
    void setNome(string n);
    Vertex<T> getMorada();
    void setMorada(Vertex<T>* morada);
    string getNif();
    void setNif(string n);

};



#endif //CAL_FP05_CLIENTE_H
