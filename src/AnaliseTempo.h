#ifndef CAL_FP05_ANALISETEMPO_H
#define CAL_FP05_ANALISETEMPO_H

#include <fstream>
#include <chrono>

#include "Graph.h"
#include "Algoritmos.h"
#include "utils.h"

// Funções de auxílio à criação dos gráficos de análise da complexidade temporal dos algortimos, apresentados no relatório

template <class T>
void Tempo_Fase_1() {
    srand(time(NULL));
    ofstream escrever;
    escrever.open("GraficoFase1.csv");
    escrever << "size;time" << endl;

    //-------------------------------         Para Grid 4x4         ------------------------------------------
    // Geração Random do Pedido
    int cliente_ind = rand() % eatExpress.getNumClientes();
    int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    int estafeta_ind = rand() % eatExpress.getNumEstafetas();
    Cliente<T>* cliente = eatExpress.getClientes().at(cliente_ind);
    Restaurante<T>* restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    Pedido<T>* pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));

    // Medição do tempo do algoritmo
    auto start = std::chrono::high_resolution_clock::now();
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    vector<Vertex<T>*> vetor = algFase1(pedido);
    auto finish = std::chrono::high_resolution_clock::now();
    auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    escrever << 25 << ";" << mili << endl;
    escrever.close();
    //-------------------------------         Para Grid 4x4         ------------------------------------------

}

#endif //CAL_FP05_ANALISETEMPO_H
