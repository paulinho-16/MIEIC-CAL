#ifndef CAL_FP05_PEDIDO_H
#define CAL_FP05_PEDIDO_H

#include "Cliente.h"
#include "Restaurante.h"

template <class T>
class Pedido {
    Cliente<T> cliente;
    Restaurante<T> restaurante;

};

#endif //CAL_FP05_PEDIDO_H
