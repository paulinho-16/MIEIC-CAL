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
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    Recolher_Info();

    // Geração Random do Pedido
    int cliente_ind = rand() % eatExpress.getNumClientes();
    int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    int estafeta_ind = rand() % eatExpress.getNumEstafetas();
    cout << "DEPOIS DOS ind: " << cliente_ind << " " << restaurante_ind << " " << estafeta_ind << endl;
    Cliente<T>* cliente = eatExpress.getClientes().at(cliente_ind);
    Restaurante<T>* restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    Pedido<T>* pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));

    // Medição do tempo do algoritmo
    auto start = std::chrono::high_resolution_clock::now();
    vector<Vertex<T>*> vetor = algFase1(pedido);
    auto finish = std::chrono::high_resolution_clock::now();
    auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    escrever << graph.getNumVertex() << ";" << mili << endl;
    //-------------------------------         Para Grid 8x8         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    Recolher_Info();

    // Geração Random do Pedido
    /*cliente_ind = rand() % eatExpress.getNumClientes();
    restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    estafeta_ind = rand() % eatExpress.getNumEstafetas();
    cout << "DEPOIS DOS ind: " << cliente_ind << " " << restaurante_ind << " " << estafeta_ind << endl;
    cliente = eatExpress.getClientes().at(cliente_ind);
    restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));*/

    // Medição do tempo do algoritmo
    start = std::chrono::high_resolution_clock::now();
    vetor = algFase1(pedido);
    finish = std::chrono::high_resolution_clock::now();
    mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    escrever << graph.getNumVertex() << ";" << mili << endl;
    //-------------------------------         Para Grid 16x16         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    Recolher_Info();

    // Geração Random do Pedido
    /*cliente_ind = rand() % eatExpress.getNumClientes();
    restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    estafeta_ind = rand() % eatExpress.getNumEstafetas();
    cout << "DEPOIS DOS ind: " << cliente_ind << " " << restaurante_ind << " " << estafeta_ind << endl;
    cliente = eatExpress.getClientes().at(cliente_ind);
    restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));*/

    // Medição do tempo do algoritmo
    start = std::chrono::high_resolution_clock::now();
    vetor = algFase1(pedido);
    finish = std::chrono::high_resolution_clock::now();
    mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    escrever << graph.getNumVertex() << ";" << mili << endl;
    escrever.close();
}

void Analise_Temporal() {
    Tempo_Fase_1<int>();
}

#endif //CAL_FP05_ANALISETEMPO_H
