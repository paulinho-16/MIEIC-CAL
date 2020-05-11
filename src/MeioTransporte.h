#ifndef CAL_FP05_MEIOTRANSPORTE_H
#define CAL_FP05_MEIOTRANSPORTE_H

#include <iostream>

using namespace std;

class MeioTransporte {
    string nome;
    int velocidade;
    int capacidade;
public:
    string getNome();
    void setNome(string n);
    int getVelocidade();
    void setVelocidade(int n);
    int getCapacidade();
    void setCapacidade(int n);
};

#endif //CAL_FP05_MEIOTRANSPORTE_H
