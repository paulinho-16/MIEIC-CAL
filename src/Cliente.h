#ifndef CAL_FP05_CLIENTE_H
#define CAL_FP05_CLIENTE_H

#include <string>

using namespace std;


        // Classe que trata dos dados de cada cliente da empresa
template <class T>
class Cliente {
    T morada;
    string nome;
    string nif;
    bool repetido = false;
public:
    Cliente(string n, string ni, T id) {
        nome = n;
        nif = ni;
        morada = id;
    }

    string getNome() {
        return nome;
    }

    void setNome(string n) {
        this->nome = n;
    }

    T getMorada() {
        return morada;
    }

    void setMorada(T morada) {
        this->morada = morada;
    }

    string getNif() {
        return nif;
    }

    void setNif(string n) {
        this->nif = n;
    }

    bool getRepetido() {
        return repetido;
    }

    void setRepetido(bool b) {
        this->repetido = b;
    }
};

#endif //CAL_FP05_CLIENTE_H
