#include "Cliente.h"

template <class T>
Cliente<T>::Cliente(string n, string ni, int id) {
    nome = n;
    ni = nif;
    //morada = nullptr;
}

template <class T>
string Cliente<T>::getNome() {
    return this->nome;
}

template <class T>
void Cliente<T>::setNome(string n) {
    this->nome=n;
}

/*template <class T>
void Cliente<T>::setMorada(Vertex<T>* morada) {
    this->morada=morada;
}*/

/*template <class T>
Vertex<T>* Cliente::getMorada() {
    return morada;
}*/

template <class T>
string Cliente<T>::getNif() {
    return nif;
}

template <class T>
void Cliente<T>::setNif(string n) {
    this->nif=n;
}
