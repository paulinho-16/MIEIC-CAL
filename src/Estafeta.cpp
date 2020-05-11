#include "Estafeta.h"

template <class T>
string Estafeta<T>::getNif() {
    return this->nif;
}
template <class T>
void Estafeta<T>::setNif(string n) {
    this->nif = n;
}

template <class T>
string Estafeta<T>::getNome() {
    return this->nome;
}

template <class T>
void Estafeta<T>::setNome(string n) {
    this->nome = n;
}

template <class T>
T Estafeta<T>::getPos() {
    return this->pos;
}

template <class T>
void Estafeta<T>::setPos(T v) {
    this->pos=v;
}

template <class T>
MeioTransporte Estafeta<T>::getTransporte() {
    return this->transporte;
}

template <class T>
void Estafeta<T>::setTransporte(MeioTransporte t) {
    this->transporte=t;
}
