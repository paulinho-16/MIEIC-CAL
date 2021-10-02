#ifndef CAL_FP05_PEDIDO_H
#define CAL_FP05_PEDIDO_H

#include "Cliente.h"
#include "Restaurante.h"
#include "Estafeta.h"

// Classe que trata dos dados de cada pedido da empresa
template <class T>
class Pedido {
    Cliente<T>* cliente;
    Restaurante<T>* restaurante;
    Estafeta<T>* estafeta;
    bool requisitado;
public:

    Pedido(Cliente<T>* c, Restaurante<T>* r) {
        cliente = c;
        restaurante = r;
    }

    Cliente<T>* getCliente() {
        return cliente;
    }

    Restaurante<T>* getRestaurante() {
        return restaurante;
    }

    void setRequisitado(bool a){
        requisitado=a;
    }

    bool isRequisitado() {
        return requisitado;
    }

    Estafeta<T>* getEstafeta() {
        return estafeta;
    }

    void setEstafeta(Estafeta<T>* e) {
        estafeta = e;
    }
};

#endif //CAL_FP05_PEDIDO_H
