#ifndef CAL_FP05_EATEXPRESS_H
#define CAL_FP05_EATEXPRESS_H

#include <vector>
#include "Cliente.h"
#include "Restaurante.h"
#include "Estafeta.h"

template <class T>
class EatExpress {
    private:
        vector<Cliente<T>*> clientes;
        vector<Restaurante<T>*> restaurantes;
        vector<Estafeta<T>*> estafetas;
        T casaEstafetas;

    public:
    vector<Cliente<T>*> getClientes() {
        return clientes;
    }

    void setClientes(vector<Cliente<T>*> c) {
        clientes = c;
    }

    vector<Restaurante<T>*> getRestaurantes() {
        return restaurantes;
    }

    void setRestaurantes(vector<Restaurante<T>*> r) {
        restaurantes = r;
    }

    vector<Estafeta<T>*> getEstafetas() {
        return estafetas;
    }

    void setEstafetas(vector<Estafeta<T>*> e) {
        estafetas = e;
    }

    T getCasaEstafetas() {
        return casaEstafetas;
    }

    void setCasaEstafetas(T c) {
        casaEstafetas = c;
    }

    int getNumClientes() {
        return clientes.size();
    }

    int getNumRestaurantes() {
        return restaurantes.size();
    }

    int getNumEstafetas() {
        return estafetas.size();
    }
};

#endif //CAL_FP05_EATEXPRESS_H
