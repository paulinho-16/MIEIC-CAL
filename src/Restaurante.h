//
// Created by Mariana Ramos on 06/05/2020.
//

#ifndef CAL_FP05_RESTAURANTE_H
#define CAL_FP05_RESTAURANTE_H

#include <d2d1helper.h>
#include "Prato.h"
#include "Graph.h"

template <class T>

class Restaurante {
    string nome;
    string descricao;
    vector<Prato> pratos;
    Vertex<T> morada;
public:
    string getNome();
    void setNome(string n);
    string getDescricao();
    void setDescricao(string d);
    Vertex<T> getMorada();
    void setMorada(Vertex<T> v);
    vector<Prato> getPratos();
    void setPratos(vector<Prato> p);

};




#endif //CAL_FP05_RESTAURANTE_H
