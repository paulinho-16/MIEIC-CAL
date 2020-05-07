#include "Pedido.h"


int Pedido::getId(){
    return this->id;
}
void Pedido::setId(int i) {
    this->id=i;
}
Restaurante<T> Pedido::getRestaurante() {
    return this->restaurante;
}
Cliente<T> Pedido::getCliente() {
    return this->cliente;
}
void Pedido::setCliente(Cliente c) {
    this->cliente=c;
}
Estafeta<T> Pedido::getEstafeta() {
    return this->estafeta;
}
void Pedido::setEstafeta(Estafeta <T> t) {
    this->estafeta=t;
}