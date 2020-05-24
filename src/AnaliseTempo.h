#ifndef CAL_FP05_ANALISETEMPO_H
#define CAL_FP05_ANALISETEMPO_H

#include <fstream>
#include <time.h>

#include "Graph.h"
#include "Algoritmos.h"
#include "utils.h"
#include "Conetividade.h"

extern Estafeta<int>* estafeta_ativo;

// Funções de auxílio à criação dos gráficos de análise da complexidade temporal dos algortimos, apresentados no relatório

template <class T>
void Tempo_Alg_1() {
    srand(time(NULL));
    ofstream escrever;
    escrever.open("GraficoAlg1.csv");
    escrever << "pedidos;time;vertices" << endl;

    struct timespec start, finish;
    double elapsed;

    //-------------------------------         Para Grid 4x4         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    Recolher_Info();

    Pedido<T> *pedido;
    // Geração Random dos Pedidos
    int cliente_ind = rand() % eatExpress.getNumClientes();
    int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    int estafeta_ind = rand() % eatExpress.getNumEstafetas();
    Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
    Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));

    // Medição do tempo do algoritmo

    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T>*> vetor = algFase1(pedido);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "25" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Grid 8x8         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    Recolher_Info();

    // Geração Random dos Pedidos
    cliente_ind = rand() % eatExpress.getNumClientes();
    restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    estafeta_ind = rand() % eatExpress.getNumEstafetas();
    cliente = eatExpress.getClientes().at(cliente_ind);
    restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase1(pedido);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "81" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Grid 16x16         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    Recolher_Info();

    // Geração Random dos Pedidos
    cliente_ind = rand() % eatExpress.getNumClientes();
    restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    estafeta_ind = rand() % eatExpress.getNumEstafetas();
    cliente = eatExpress.getClientes().at(cliente_ind);
    restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase1(pedido);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "289" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Penafiel         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Penafiel");
    Recolher_Info();

    // Geração Random dos Pedidos
    cliente_ind = rand() % eatExpress.getNumClientes();
    restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    estafeta_ind = rand() % eatExpress.getNumEstafetas();
    cliente = eatExpress.getClientes().at(cliente_ind);
    restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase1(pedido);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "3964" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Espinho         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Espinho");
    Recolher_Info();

    // Geração Random dos Pedidos
    cliente_ind = rand() % eatExpress.getNumClientes();
    restaurante_ind = rand() % eatExpress.getNumRestaurantes();
    estafeta_ind = rand() % eatExpress.getNumEstafetas();
    cliente = eatExpress.getClientes().at(cliente_ind);
    restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
    pedido = new Pedido<int>(cliente, restaurante);
    pedido->setEstafeta(eatExpress.getEstafetas().at(estafeta_ind));

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase1(pedido);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "7108" << ";" << elapsed*1000 << endl;

    escrever.close();
}

template <class T>
void Tempo_Alg_2() {
    srand(time(NULL));
    ofstream escrever;
    escrever.open("GraficoAlg2.csv");
    escrever << "vertex;time" << endl;

    struct timespec start, finish;
    double elapsed;

    //-------------------------------         Para Grid 4x4         ------------------------------------------

    // Iniciar Grafo e Dados da EatExpress
    vector<Pedido<T>*> pedidos;
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T> *> vetor = algFase2(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "25" << ";" << elapsed*1000 << endl;
    //-------------------------------         Para Grid 8x8         ------------------------------------------

    // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase2(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "81" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Grid 16x16         ------------------------------------------
        // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase2(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "289" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Penafiel         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Penafiel");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase2(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "3964" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Espinho         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Espinho");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase2(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "7108" << ";" << elapsed*1000 << endl;

    escrever.close();
}

template <class T>
void Tempo_Alg_4() {
    srand(time(NULL));
    ofstream escrever;
    escrever.open("GraficoAlg4.csv");
    escrever << "vertex;time" << endl;

    struct timespec start, finish;
    double elapsed;

    //-------------------------------         Para Grid 4x4         ------------------------------------------

    // Iniciar Grafo e Dados da EatExpress
    vector<Pedido<T>*> pedidos;
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T> *> vetor = algFase4(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "25" << ";" << elapsed*1000 << endl;
    //-------------------------------         Para Grid 8x8         ------------------------------------------

    // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase4(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "81" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Grid 16x16         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase4(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "289" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Penafiel         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Penafiel");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase4(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "3964" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Espinho         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    pedidos.clear();
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Espinho");
    Recolher_Info();

    // Criação de Pedidos Random
    for (unsigned int i = 0 ; i < 10 ; i++) {
        int estafeta_ind = rand() % eatExpress.getNumEstafetas();
        estafeta_ativo = eatExpress.getEstafetas().at(estafeta_ind);
        int cliente_ind = rand() % eatExpress.getNumClientes();
        int restaurante_ind = rand() % eatExpress.getNumRestaurantes();
        Cliente<T> *cliente = eatExpress.getClientes().at(cliente_ind);
        Restaurante<T> *restaurante = eatExpress.getRestaurantes().at(restaurante_ind);
        Pedido<T> *pedido = new Pedido<int>(cliente, restaurante);
        pedido->setEstafeta(estafeta_ativo);
        pedidos.push_back(pedido);
    }
    eatExpress.setPedidos(pedidos);


    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = algFase4(estafeta_ativo, eatExpress.getPedidos());
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "7108" << ";" << elapsed*1000 << endl;

    escrever.close();
}

template <class T>
void Tempo_DFS() {
    srand(time(NULL));
    ofstream escrever;
    escrever.open("GraficoDFS.csv");
    escrever << "vertex;time" << endl;

    struct timespec start, finish;
    double elapsed;

    //-------------------------------         Para Grid 4x4         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");
    Recolher_Info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vector<Vertex<T>*> vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "25" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Grid 8x8         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");
    Recolher_Info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "81" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Grid 16x16         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");
    Recolher_Info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "289" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Penafiel         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Penafiel");
    Recolher_Info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "3964" << ";" << elapsed*1000 << endl;

    //-------------------------------         Para Mapa Espinho         ------------------------------------------
    // Iniciar Grafo e Dados da EatExpress
    bidirectional_edges = true;
    readMap<T>("../maps/MapasConexos/Espinho");
    Recolher_Info();

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    vetor = dfs(&graph, graph.getVertexSet()[0]);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "7108" << ";" << elapsed*1000 << endl;

    escrever.close();
}

template <class T>
void Tempo_Dijkstra() {
    srand(time(NULL));
    ofstream escrever;
    escrever.open("GraficoDijkstra.csv");
    escrever << "vertices;time" << endl;

    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/4x4");

    struct timespec start, finish;
    double elapsed;

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "25" << ";" << elapsed*1000 << endl;

    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/8x8");

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    escrever << "81" << ";" << elapsed*1000 << endl;

    bidirectional_edges = true;
    readMap<T>("../maps/GridGraphs/16x16");

    // Medição do tempo do algoritmo
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (unsigned int i = 1 ; i <= 50 ; i++) {
        Vertex<T> *src = graph.findVertex(rand() % graph.getNumVertex());
        graph.dijkstraShortestPath(src->getInfo());
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    escrever << "289" << ";" << elapsed*1000 << endl;
}

void Analise_Temporal() {
    Tempo_DFS<int>();
    Tempo_Dijkstra<int>();
    Tempo_Alg_1<int>();
    Tempo_Alg_2<int>();
    Tempo_Alg_4<int>();
    system("pause");
}

#endif //CAL_FP05_ANALISETEMPO_H
