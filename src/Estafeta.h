//
// Created by Mariana Ramos on 07/05/2020.
//

#ifndef CAL_FP05_ESTAFETA_H
#define CAL_FP05_ESTAFETA_H


class Estafeta {
    string nome;
    string nif;
    Vertex<T> pos;
    MeioTransporte transporte;
public:
    string getNome();
    void setNome(string n);
    string getNif();
    void setNif(string n);
    Vertex<T> getPos();
    void setPos(Vertex<T> v);
    MeioTransporte<T> getTransporte();
    void setTransporte(MeioTransporte<T> t);

};


#endif //CAL_FP05_ESTAFETA_H
