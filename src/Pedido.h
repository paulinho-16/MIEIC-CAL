#ifndef CAL_FP05_PEDIDO_H
#define CAL_FP05_PEDIDO_H

#include "Cliente.h"
#include "Restaurante.h"

template <class T>
class Pedido {
    int id;
    Cliente<T> cliente;
    Restaurante<T> restaurante;
    Estafeta<T> estafeta;
public:
    int getId();
    void setId(int i);
    Cliente<T> getCliente();
    void setCliente(Cliente c);
    Restaurante<T> getRestaurante();
    void setRestaurante(Restaurante<T> r);
    Estafeta<T> getEstafeta();
    void setEstafeta(Estafeta<T> t);
};

#endif //CAL_FP05_PEDIDO_H
