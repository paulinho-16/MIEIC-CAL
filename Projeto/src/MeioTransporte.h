#ifndef CAL_FP05_MEIOTRANSPORTE_H
#define CAL_FP05_MEIOTRANSPORTE_H

#include <iostream>

using namespace std;

// Classe que trata dos dados de cada meio de transporte da empresa
class MeioTransporte {
    string nome;
    int velocidade;
    int capacidade;
public:
    MeioTransporte();
    MeioTransporte(string n, int v, int c);
    string getNome();
    int getVelocidade();
    int getCapacidade();
};

#endif //CAL_FP05_MEIOTRANSPORTE_H
