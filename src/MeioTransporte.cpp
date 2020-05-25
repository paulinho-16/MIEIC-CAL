#include "MeioTransporte.h"

using namespace std;

// Funções de gestão dos dados de um meio de transporte

MeioTransporte::MeioTransporte() {
    nome = "Default";
    velocidade = 50;
    capacidade = 1;
}

MeioTransporte::MeioTransporte(string n, int v, int c) {
    nome = n;
    velocidade = v;
    capacidade = c;
}

string MeioTransporte::getNome() {
    return this->nome;
}

int MeioTransporte::getCapacidade() {
    return this->capacidade;
}

int MeioTransporte::getVelocidade() {
    return this->velocidade;
}
