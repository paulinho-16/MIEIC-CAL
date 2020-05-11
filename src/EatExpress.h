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
    public:
    vector<Cliente<T>*> getClientes() {
        return this->clientes;
    }
    void setClientes(vector<Cliente<T>*> c) {
        this->clientes=c;
    }
    vector<Restaurante<T>*> getRestaurantes(){
        return this->restaurantes;
    }
    void setRestaurantes(vector<Restaurante<T>*> r){
        this->restaurantes=r;
    }
};

#endif //CAL_FP05_EATEXPRESS_H
