//
// Created by Mariana Ramos on 06/05/2020.
//

#include "Restaurante.h"

template<class T>
string Restaurante<T>::getNome() {
    return this->nome;
}
template<class T>
void Restaurante<T>::setNome(string n){
    this->nome=n;
}
template<class T>
string Restaurante<T>::getDescricao(){
    return descricao;
}
template<class T>
void Restaurante<T>::setDescricao(string d){
    this->descricao=d;
}
template<class T>
Vertex<T> Restaurante<T>::getMorada(){
    return morada;
}
template<class T>
void Restaurante<T>::setMorada(Vertex<T> v){
    this->morada=v;
}
template<class T>
vector<Prato> Restaurante<T>::getPratos(){
    return pratos;
}
template<class T>
void Restaurante<T>::setPratos(vector<Prato> p){
    this->pratos=p;
}
