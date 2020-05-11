#ifndef CAL_FP05_RESTAURANTE_H
#define CAL_FP05_RESTAURANTE_H

#include <string>
using namespace std;

template <class T>
class Restaurante {
    string nome;
    string descricao;
    T morada;
public:
    Restaurante(string n, string desc, T id) {
        nome = n;
        descricao = desc;
        morada = id;
    }

    string getNome() {
        return nome;
    }

    void setNome(string n){
        nome = n;
    }

    string getDescricao(){
        return descricao;
    }

    void setDescricao(string d){
        descricao = d;
    }

    T getMorada() {
        return morada;
    }

    void setMorada(T v) {
        morada = v;
    }
};

#endif //CAL_FP05_RESTAURANTE_H
