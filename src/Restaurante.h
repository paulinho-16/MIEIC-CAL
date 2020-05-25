#ifndef CAL_FP05_RESTAURANTE_H
#define CAL_FP05_RESTAURANTE_H

#include <string>
using namespace std;

// Classe que trata dos dados de cada restaurante da empresa
template <class T>
class Restaurante {
    string nome;
    string descricao;
    T morada;
    bool ja_pedido;
    bool repetido = false;
public:
    Restaurante(string n, string desc, T id) {
        nome = n;
        descricao = desc;
        morada = id;
        ja_pedido = false;
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

    bool RestauranteJaPedido() {
        return ja_pedido;
    }

    void setJaPedido(bool b) {
        ja_pedido = b;
    }

    bool getRepetido() {
        return repetido;
    }

    void setRepetido(bool b) {
        repetido = b;
    }
};

#endif //CAL_FP05_RESTAURANTE_H
