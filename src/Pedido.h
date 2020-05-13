#ifndef CAL_FP05_PEDIDO_H
#define CAL_FP05_PEDIDO_H

#include "Cliente.h"
#include "Restaurante.h"
#include "Estafeta.h"

template <class T>
class Pedido {
    //int id;
    Cliente<T>* cliente;
    Restaurante<T>* restaurante;
    //Estafeta<T>* estafeta;
    bool temComida;
public:
    //int getId();
    //void setId(int i);

    Pedido(Cliente<T>* c, Restaurante<T>* r) {
        cliente = c;
        restaurante = r;
    }

    Cliente<T>* getCliente() {
        return cliente;
    }

    void setCliente(Cliente<T>* c) {
        cliente = c;
    }

    Restaurante<T>* getRestaurante() {
        return restaurante;
    }

    void setRestaurante(Restaurante<T>* r) {
        restaurante = r;
    }

    void setTemComida(bool a){
        this->temComida=a;
    }

    bool getTemComida(){
        return this->temComida;
    }

    //Estafeta<T> getEstafeta();
    //void setEstafeta(Estafeta<T> t);
};

#endif //CAL_FP05_PEDIDO_H
