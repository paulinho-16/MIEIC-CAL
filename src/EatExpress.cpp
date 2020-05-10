//
// Created by Mariana Ramos on 10/05/2020.
//

#include "EatExpress.h"

/*template<class T>
EatExpress<T>::EatExpress() {
    this->clientes=new vector<Cliente<T>*>;
    this->estafetas=new vector<Restaurante<T>*>;
    this->restaurantes=new vector<Estafeta<T>*>;
}*/
template<class T>
vector<Cliente<T> *> EatExpress<T>::getClientes() {
    return this->clientes;
}

template<class T>
void EatExpress<T>::setClientes(vector<Cliente<T> *> c) {
    this->clientes=c;
}

template<class T>
vector<Restaurante<T> *> EatExpress<T>::getRestaurantes() {
    return this->restaurantes;
}

template<class T>
void EatExpress<T>::setRestaurantes(vector<Restaurante<T> *> r) {
    this->restaurantes=r;
}

template<class T>
vector<Estafeta<T> *> EatExpress<T>::getEstafetas() {
    return this->estafetas;
}

template<class T>
void EatExpress<T>::setEstafetas(vector<Estafeta<T> *> e) {
    this->estafetas=e;
}

template<class T>
Vertex<T>* EatExpress<T>::getCasaDosEstafetas() {
    return CasaDosEstafetas;
}

template<class T>
void EatExpress<T>::setCasaDosEstafetas(Vertex<T>* v) {
    this->casaDosEstafetas=v;
}


