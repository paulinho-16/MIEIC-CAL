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
    Restaurante(){
        this->morada = nullptr;
    }
    string getNome();
    void setNome(string n);
    string getDescricao();
    void setDescricao(string d);
    T getMorada(){
        return this->morada;
    }
    void setMorada(T v){
        this->morada=v;
    }

};

#endif //CAL_FP05_RESTAURANTE_H
