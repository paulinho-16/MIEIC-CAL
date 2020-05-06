//
// Created by Mariana Ramos on 06/05/2020.
//

#include "Cliente.h"

string Cliente::getNome() {
    return this->nome;
}
void Cliente::setNome(string n) {
    this->nome=n;
}
void Cliente::setMorada(Vertex <T> morada) {
    this->morada=morada;
}
Vertex<T> Cliente::getMorada() {
    return this->morada;
}
string Cliente::getNif() {
    return nif;
}
string Cliente::setNif(string n) {
    this->nif=n;
}