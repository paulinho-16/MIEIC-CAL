//
// Created by Mariana Ramos on 10/05/2020.
//

#ifndef CAL_FP05_EATEXPRESS_H
#define CAL_FP05_EATEXPRESS_H

#include "Cliente.h"
#include "Restaurante.h"
#include"Estafeta.h"

template <class T>
class EatExpress {
    vector<Cliente<T>*> clientes;
    vector<Restaurante<T>*> restaurantes;
    vector<Estafeta<T>*> estafetas;
    Vertex<T>* casaDosEstafetas;
public:
    //EatExpress();
    vector<Cliente<T>*> getClientes();
    void setClientes(vector<Cliente<T>*> c);
    vector<Restaurante<T>*> getRestaurantes();
    void setRestaurantes(vector<Restaurante<T>*> r);
    vector<Estafeta<T>*> getEstafetas();
    void setEstafetas(vector<Estafeta<T>*> e);
    void setCasaDosEstafetas(Vertex<T>* v);
    Vertex<T> getCasaDosEstafetas();

};



#endif //CAL_FP05_EATEXPRESS_H
