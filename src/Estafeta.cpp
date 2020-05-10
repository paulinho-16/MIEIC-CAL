//
// Created by Mariana Ramos on 07/05/2020.
//

#include "Estafeta.h"

string Estafeta::getNif() {
    return this->nif;
}
void Estafeta::setNif(string n) {
    this->nif = n;
}

string Estafeta::getNome() {
    return this->nome;
}
void Estafeta::setNome(string n) {
    this->nome = n;
}

Vertex<T> Estafeta::getPos() {
    return this->pos;
}
void Estafeta::setPos(Vertex <T> v) {
    this->pos=v;
}
MeioTransporte Estafeta::getTransporte() {
    return this->transporte;
}
void Estafeta::setTransporte(MeioTransporte t) {
    this->transporte=t;
}

