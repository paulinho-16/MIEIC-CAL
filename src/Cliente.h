#ifndef CAL_FP05_CLIENTE_H
#define CAL_FP05_CLIENTE_H


#include <string>

using namespace std;

template <class T>
class Cliente {
    T morada;
    string nome;
    string nif;
public:
    Cliente(string n, string ni, int id) {
        nome = n;
        ni = nif;
        //morada = nullptr;
    }
    string getNome();
    void setNome(string n);
    T getMorada() {
        return morada;
    }
    void setMorada(T morada) {
        this->morada=morada;
    }
    string getNif();
    void setNif(string n);
};

#endif //CAL_FP05_CLIENTE_H
