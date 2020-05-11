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
    Cliente(string n, string ni, T id) {
        nome = n;
        ni = nif;
        morada = id;
    }

    string getNome() {
        return nome;
    }

    void setNome(string n) {
        this->nome=n;
    }

    T getMorada() {
        return morada;
    }

    void setMorada(T morada) {
        this->morada=morada;
    }

    string getNif() {
        return nif;
    }

    void setNif(string n) {
        this->nif=n;
    }
};

#endif //CAL_FP05_CLIENTE_H
