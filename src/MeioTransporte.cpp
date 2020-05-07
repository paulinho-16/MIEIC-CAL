//
// Created by Mariana Ramos on 07/05/2020.
//

#include "MeioTransporte.h"

void MeioTransporte::setNome(string n) {
    this->nome=n;
}
string MeioTransporte::getNome() {
    return this->nome;
}
int MeioTransporte::getCapacidade() {
    return this->capacidade;
}
void MeioTransporte::setCapacidade(int n) {
    this->capacidade=n;
}
int MeioTransporte::getVelocidade() {
    return this->velocidade;
}
void MeioTransporte::setVelocidade(int n) {
    this->velocidade=n;
}