#ifndef CAL_FP05_UTILS_H
#define CAL_FP05_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>

#include "../GraphViewerLib/graphviewer.h"

#include "Cliente.h"
#include "Estafeta.h"
#include "Restaurante.h"
#include "Pedido.h"

#include "Graph.h"
#include "EatExpress.h"

extern Graph<int> graph;
extern EatExpress<int> eatExpress;
extern bool bidirectional_edges;
extern Estafeta<int>* estafeta_ativo;
GraphViewer *gv;

using namespace std;


        // Apresenta o Logotipo da Empresa
void Logotipo() {
    cout << "        ______      _   ______" << endl;
    cout << "       |  ____|    | | |  ____|" << endl;
    cout << "       | |__   __ _| |_| |__  __  ___ __  _ __ ___  ___ ___" << endl;
    cout << "       |  __| / _` | __|  __| \\ \\/ / '_ \\| '__/ _ \\/ __/ __|" << endl;
    cout << "       | |___| (_| | |_| |____ >  <| |_) | | |  __/\\__ \\__ \\ " << endl;
    cout << "       |______\\__,_|\\__|______/_/\\_\\ .__/|_|  \\___||___/___/" << endl;
    cout << "                                   | |" << endl;
    cout << "                                   |_|" << endl;
}


template <class T>      // Lê os vértices do ficheiro enviado como parâmetro
void readNodes(string file_directory) {
    ifstream ler;
    string number;
    string tuple;
    ler.open(file_directory);
    getline(ler, number);
    int n = stoi(number);
    for (unsigned int i = 0 ; i < n ; i++) {
        getline(ler, tuple);
        tuple = tuple.substr(1, tuple.size() - 2);

        stringstream ss(tuple);
        string id, latitude, longitude;
        getline(ss, id, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        Vertex<T>* vertex = new Vertex<T>(stoi(id), stof(latitude), stof(longitude));
        graph.addVertex(vertex);
    }
    cout << "Vertex Lidos: " << graph.getNumVertex() << endl;
   // graph.printVertexs();
    ler.close();
}


template <class T>      // Lê as arestas do ficheiro enviado como parâmetro
void readEdges(string file_directory) {
    ifstream ler;
    string number;
    string tuple;
    ler.open(file_directory);
    getline(ler, number);
    int n = stoi(number);
    if (bidirectional_edges) {
        for (unsigned int i = 0 ; i < 2*n ; i += 2) {
            getline(ler, tuple);
            tuple = tuple.substr(1, tuple.size() - 2);

            stringstream ss(tuple);
            string id1, id2;
            getline(ss, id1, ',');
            getline(ss, id2, ',');
            graph.addEdge(i + 1, stoi(id1), stoi(id2));
            graph.addEdge(i + 2, stoi(id2), stoi(id1));
        }
    }
    else {
        for (unsigned int i = 0; i < n; i++) {
            getline(ler, tuple);
            tuple = tuple.substr(1, tuple.size() - 2);

            stringstream ss(tuple);
            string id1, id2;
            getline(ss, id1, ',');
            getline(ss, id2, ',');
            graph.addEdge(i + 1, stoi(id1), stoi(id2));
        }
    }
    cout << "Edge Lidos: " << graph.getNumEdges() << endl;
    ler.close();
    //graph.printEdges();
}


template <class T>       // Constrói os paths dos ficheiros e lê os vértices e as arestas destes
void readMap(string directory) {
    string nodes_path = directory + "/nodes.txt";
    string edges_path = directory + "/edges.txt";
    graph.reset();
    readNodes<int>(nodes_path);
    readEdges<int>(edges_path);

    for(Vertex<T>* v: graph.getVertexSet()){
        for(Edge<T> e: v->getAdj()){
            double i=graph.getDist(v->getInfo(),e.getDest()->getInfo());
            e.setWeight(i);
        }
    }
}


        // Apresenta o grafo completo, mostrando todos os clientes, restaurantes, e estafetas que estão presentes na empresa
void Visualizar_Mapa() {
    gv = new GraphViewer(1200, 900, false);
    gv->createWindow(1200, 900);
    //gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        switch (vertex->getType()) {
            case 0:     // Não é ponto de interesse
                gv->setVertexColor(vertex->getInfo(), "blue"); break;
            case 1:     // Morada de Cliente
                gv->setVertexColor(vertex->getInfo(), "green"); break;
            case 2:     // Restaurante
                gv->setVertexColor(vertex->getInfo(), "red"); break;
            case 3:     // Posição de Estafeta
                gv->setVertexColor(vertex->getInfo(), "yellow"); break;
            case 4:     // Casa dos Estafetas
                gv->setVertexColor(vertex->getInfo(), "orange"); break;
        }
        gv->addNode(vertex->getInfo(), vertex->getLatitude(), vertex->getLongitude());
    }
    int edgeID = 0;
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            gv->addEdge(edgeID,vertex->getInfo(), edge.getDest()->getInfo(), EdgeType::DIRECTED);
            edgeID++;
        }
    }
    gv->rearrange();
}


template<class T>       // Trata da informação da Casa dos Estafetas
void recolher_info_casaEstafetas() {
    eatExpress.setCasaEstafetas(graph.getVertexSet()[0]->getInfo());
    Vertex<T>* vertex = graph.findVertex(eatExpress.getCasaEstafetas());
    vertex->setType(4);
}


template<class T>       // Lê as informações relativas aos clientes do ficheiro
void recolher_info_clientes() {

    vector<Cliente<T>*> v;
    ifstream ler;
    ler.open("../files/clientes.txt");
    while(!ler.eof()){
        string nome, nif, morada, separacao;
        getline(ler, nome);
        getline(ler, nif);
        getline(ler, morada);
        getline(ler, separacao);
        Cliente<int>* cliente = new Cliente<int>(nome, nif, stoi(morada));
        Vertex<T>* vertex = graph.findVertex(cliente->getMorada());
        if(vertex==nullptr){continue;}
        else{v.push_back(cliente);}
    }
    eatExpress.setClientes(v);
    ler.close();

    for (Cliente<T>* cliente : eatExpress.getClientes()) {
        Vertex<T>* vertex = graph.findVertex(cliente->getMorada());
        if (vertex->getType() == 0) {
            vertex->setType(1);
        }
    }
}


template <class T>      // Lê as informações relativas aos restaurantes do ficheiro
void recolher_info_restaurantes() {
    vector<Restaurante<T>*> v;
    ifstream ler;
    ler.open("../files/restaurantes.txt");
    while(!ler.eof()){
        string nome, morada, desc, separacao;
        getline(ler, nome);
        getline(ler, desc);
        getline(ler, morada);
        getline(ler, separacao);
        Restaurante<T>* restaurante = new Restaurante<T>(nome, desc, stoi(morada));
        Vertex<T>* vertex = graph.findVertex(restaurante->getMorada());
        if(vertex==nullptr){continue;}
        else{v.push_back(restaurante);}
    }
    eatExpress.setRestaurantes(v);
    ler.close();

    for (Restaurante<T>* restaurante : eatExpress.getRestaurantes()) {
        Vertex<T>* vertex = graph.findVertex(restaurante->getMorada());
        if (vertex->getType() == 0) {
            vertex->setType(2);
        }
    }
}


        // Lê as informações relativas aos transportes do ficheiro
void recolher_info_transportes() {
    vector<MeioTransporte> t;
    ifstream ler;
    ler.open("../files/transportes.txt");
    while(!ler.eof()) {
        string nome, velocidade, capacidade, separacao;
        getline(ler, nome);
        getline(ler, velocidade);
        getline(ler, capacidade);
        getline(ler, separacao);
        MeioTransporte transporte = MeioTransporte(nome, stoi(velocidade), stoi(capacidade));
        t.push_back(transporte);
    }
    eatExpress.setTransportes(t);
    ler.close();
}


template <class T>      // Lê as informações relativas aos estafetas do ficheiro
void recolher_info_estafetas() {
    vector<Estafeta<T>*> v;
    ifstream ler;
    ler.open("../files/estafetas.txt");
    while(!ler.eof()){
        string nome, nif, pos, transporte, separacao;
        getline(ler, nome);
        getline(ler, nif);
        getline(ler, pos);
        getline(ler, transporte);
        getline(ler, separacao);
        Estafeta<T>* estafeta = new Estafeta<T>(nome, nif, stoi(pos), eatExpress.findMeioTransporte(transporte));
        Vertex<T>* vertex = graph.findVertex(estafeta->getPos());
        if(vertex==nullptr){continue;}
        else{v.push_back(estafeta);}
    }
    eatExpress.setEstafetas(v);
    ler.close();

    for (Estafeta<T>* estafeta : eatExpress.getEstafetas()) {
        Vertex<T>* vertex = graph.findVertex(estafeta->getPos());
        if (vertex->getType() == 0) {
            vertex->setType(3);
        }
    }
}


        // Lê as informações dos clientes, restaurantes e estafetas presentes na empresa
void Recolher_Info() {
    recolher_info_casaEstafetas<int>();
    recolher_info_clientes<int>();
    recolher_info_restaurantes<int>();
    recolher_info_transportes();
    recolher_info_estafetas<int>();
}


template <class T>      // Verifica se um dado vertex é um dos vertices envolvidos nos pedidos
int isInPedidos(Vertex<T>* vertex) {
    int numero_pedido = 0;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        numero_pedido++;
        Vertex<T>* rest = graph.findVertex(pedido->getRestaurante()->getMorada());
        Vertex<T>* cl = graph.findVertex(pedido->getCliente()->getMorada());
        Vertex<T>* est = graph.findVertex(pedido->getEstafeta()->getPos());
        if (rest->getInfo() == vertex->getInfo() || cl->getInfo() == vertex->getInfo() || est->getInfo() == vertex->getInfo())
            return numero_pedido;
    }
    return 0;
}


template <class T>
bool isIn( Vertex<T>* vertex,vector<Vertex<T>*> v) {
    for (Vertex<T>* vert : v) {
        if (vert->getInfo() == vertex->getInfo())
            return true;
    }
    return false;
}

template <class T>
bool isInEstafeta( Estafeta<T>* estafeta,vector<Estafeta<T>*> v) {
    for (Estafeta<T>* vert : v) {
        if (vert->getPos() == estafeta->getPos())
            return true;
    }
    return false;
}


template <class T>      // Atribui o estafeta que estiver mais perto do restaurante indicado no pedido a esse pedido
void atribuirEstafeta(Pedido<T> *pedido) {
    double minDist = 10000;
    for(Estafeta<T>* estafeta : eatExpress.getEstafetas()) {
        double d=graph.getDist(pedido->getRestaurante()->getMorada(),estafeta->getPos());
        if(d < minDist) {
            minDist = d;
            pedido->setEstafeta(estafeta);
        }
    }
}

template <class T>      // Apresenta o grafo e o percurso indicado no parâmetro
void showPathGV(vector<Vertex<T>*> v) {
    gv = new GraphViewer(1000, 900, false);
    gv->createWindow(1200, 900);
    gv->defineEdgeColor("black");
    int n_pedido;
    // Desenha o grafo, indicando os clientes, restaurantes e estafetas envolvidos nos pedidos
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        if (vertex->getType() == 4) {
            gv->setVertexColor(vertex->getInfo(), "yellow");
            gv->setVertexLabel(vertex->getInfo(), "Casa dos Estafetas");
        }
        else if (vertex->getType() == 1 && (n_pedido = isInPedidos(vertex))) {
            gv->setVertexColor(vertex->getInfo(), "orange");
            gv->setVertexLabel(vertex->getInfo(), "Cliente " + to_string(n_pedido));
        }
        else if (vertex->getType() == 2 && (n_pedido = isInPedidos(vertex))) {
            gv->setVertexColor(vertex->getInfo(), "green");
            gv->setVertexLabel(vertex->getInfo(), "Restaurante " + to_string(n_pedido));
        }
        else if (vertex->getType() == 3 && (n_pedido = isInPedidos(vertex))) {
            gv->setVertexColor(vertex->getInfo(), "yellow");
            gv->setVertexLabel(vertex->getInfo(), "Estafeta " + to_string(n_pedido));
        }
        else {
            gv->setVertexColor(vertex->getInfo(), "blue");
        }
        gv->addNode(vertex->getInfo(), vertex->getLatitude(), vertex->getLongitude());
    }
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            gv->addEdge(edge.getID(),vertex->getInfo(), edge.getDest()->getInfo(), EdgeType::DIRECTED);
        }
    }

    if(v.size()==0){return;}

    // Mostra na consola a conexão entre os dados apresentados no ecrã e os dados dos clientes, restaurantes e estafetas da empresa
    cout << "\n Dados: " << endl << endl;

    n_pedido = 0;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        n_pedido++;
        if (!pedido->getCliente()->getRepetido()) {
            cout << "Cliente " + to_string(n_pedido) << " - " << pedido->getCliente()->getNome() << " (" << pedido->getCliente()->getNif() << ")\n";
            pedido->getCliente()->setRepetido(true);
        }
    }

    n_pedido = 0;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        n_pedido++;
        if (!pedido->getRestaurante()->getRepetido()) {
            cout << "Restaurante " + to_string(n_pedido) << " - " << pedido->getRestaurante()->getNome() << " (" << pedido->getRestaurante()->getDescricao() << ")\n";
            pedido->getRestaurante()->setRepetido(true);
        }
    }

    n_pedido = 0;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        n_pedido++;
        //calculo do tempo demorado consoante a velocidade do estafeta:
        double distancia_total_pedido=0;
        double tempo_total_pedido=0;
        for (unsigned int i = 0 ; i < v.size() - 1 ; i++) {
            for (Edge<int> edge : v[i]->getAdj()) {
                if (edge.getDest() == v[i+1]) {
                    distancia_total_pedido+=edge.getWeight();
                    break;
                }
            }
        }
        tempo_total_pedido=distancia_total_pedido/pedido->getEstafeta()->getTransporte().getVelocidade();
        if (!pedido->getEstafeta()->getRepetido()) {
            cout << "Estafeta " + to_string(n_pedido) << " - " << pedido->getEstafeta()->getNome() << " (" << pedido->getEstafeta()->getNif() << ") - Duracao da entrega: "<<tempo_total_pedido<<endl;
            pedido->getEstafeta()->setRepetido(true);
        }
    }

    // Limpeza dos boleanos que permitiram a organização do output da consola
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        pedido->getCliente()->setRepetido(false);
        pedido->getRestaurante()->setRepetido(false);
        pedido->getEstafeta()->setRepetido(false);
    }

    Sleep(2000);

    // Desenha o percurso enviado como parâmetro
    for (unsigned int i = 0 ; i < v.size() - 1 ; i++) {
        Sleep(750);
        if (!isInPedidos(v[i+1]))     // Para evitar pintar os restaurante e as moradas dos Clientes.
            gv->setVertexColor(v[i+1]->getInfo(), "red");
        for (Edge<int> edge : v[i]->getAdj()) {
            if (edge.getDest() == v[i+1]) {
                gv->setEdgeColor(edge.getID(), "red");
                break;
            }
        }
        gv->rearrange();
    }
}


template <class T>       // Apresenta o grafo e os vários percursos dos vários estafetas
void showMultiplePathsGV(vector<vector<Vertex<T>*>> percursos) {
    gv = new GraphViewer(1000, 900, false);
    gv->createWindow(1200, 900);
    gv->defineEdgeColor("black");
    int n_pedido;

    // Desenha o grafo, indicando os clientes, restaurantes e estafetas envolvidos nos pedidos
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        if (vertex->getType() == 4) {
            gv->setVertexColor(vertex->getInfo(), "yellow");
            gv->setVertexLabel(vertex->getInfo(), "Casa dos Estafetas");
        }
        else if (vertex->getType() == 1 && (n_pedido = isInPedidos(vertex))) {
            gv->setVertexColor(vertex->getInfo(), "orange");
            gv->setVertexLabel(vertex->getInfo(), "Cliente " + to_string(n_pedido));
        }
        else if (vertex->getType() == 2 && (n_pedido = isInPedidos(vertex))) {
            gv->setVertexColor(vertex->getInfo(), "green");
            gv->setVertexLabel(vertex->getInfo(), "Restaurante " + to_string(n_pedido));
        }
        else if (vertex->getType() == 3 && (n_pedido = isInPedidos(vertex))) {
            gv->setVertexColor(vertex->getInfo(), "yellow");
            gv->setVertexLabel(vertex->getInfo(), "Estafeta " + to_string(n_pedido));
        }
        else {
            gv->setVertexColor(vertex->getInfo(), "black");
        }
        gv->addNode(vertex->getInfo(), vertex->getLatitude(), vertex->getLongitude());
    }
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            gv->addEdge(edge.getID(),vertex->getInfo(), edge.getDest()->getInfo(), EdgeType::DIRECTED);
        }
    }

    if(percursos.size()==0) return;

    // Mostra na consola a conexão entre os dados apresentados no ecrã e os dados dos clientes, restaurantes e estafetas da empresa
    cout << "\n Dados: " << endl << endl;

    n_pedido = 0;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        n_pedido++;
        if (!pedido->getCliente()->getRepetido()) {
            cout << "Cliente " + to_string(n_pedido) << " - " << pedido->getCliente()->getNome() << " (" << pedido->getCliente()->getNif() << ")\n";
            pedido->getCliente()->setRepetido(true);
        }
    }

    n_pedido = 0;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        n_pedido++;
        if (!pedido->getRestaurante()->getRepetido()) {
            cout << "Restaurante " + to_string(n_pedido) << " - " << pedido->getRestaurante()->getNome() << " (" << pedido->getRestaurante()->getDescricao() << ")\n";
            pedido->getRestaurante()->setRepetido(true);
        }
    }

    n_pedido = 0;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        n_pedido++;
        if (!pedido->getEstafeta()->getRepetido()) {
            n_pedido++;
            double distancia_total_pedido = 0;
            double tempo_total_pedido = 0;
            for(vector<Vertex<T>*> v: percursos) {
                for (unsigned int i = 0; i < v.size() - 1; i++) {
                    for (Edge<int> edge : v[i]->getAdj()) {
                        if (edge.getDest() == v[i + 1]) {
                            distancia_total_pedido += edge.getWeight();
                            break;
                        }
                    }
                }
            }
            tempo_total_pedido=distancia_total_pedido/pedido->getEstafeta()->getTransporte().getVelocidade();
            cout << "Estafeta " + to_string(n_pedido) << " - " << pedido->getEstafeta()->getNome() << " (" << pedido->getEstafeta()->getNif() << ") - "<<pedido->getEstafeta()->getTransporte().getNome()<<" de capacidade: "<<pedido->getEstafeta()->getTransporte().getCapacidade()<<" pedidos - Duracao da entrega: "<<tempo_total_pedido<<endl;
            pedido->getEstafeta()->setRepetido(true);
            distancia_total_pedido=0;
            tempo_total_pedido=0;
        }
    }

    // Limpeza dos boleanos que permitiram a organização do output da consola
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        pedido->getCliente()->setRepetido(false);
        pedido->getRestaurante()->setRepetido(false);
        pedido->getEstafeta()->setRepetido(false);
    }

    Sleep(2000);

    string color;
    int num_percurso=1;
    // Desenha os percursos dos vários estafetas
    for(vector<Vertex<T>*> v: percursos) {
        for (unsigned int i = 0 ; i < v.size() - 1 ; i++) {
            if(num_percurso % 4 == 1) {color ="red";}
            if(num_percurso % 4 == 2) {color = "blue";}
            if(num_percurso % 4 == 3) {color = "green";}
            if(num_percurso % 4 == 0) {color = "orange";}
            Sleep(750);
            if (!isInPedidos(v[i+1]))
                gv->setVertexColor(v[i+1]->getInfo(), color);
            for (Edge<int> edge : v[i]->getAdj()) {
                if (edge.getDest() == v[i+1]) {
                    gv->setEdgeColor(edge.getID(), color);
                    break;
                }
            }
            gv->rearrange();
        }
        num_percurso++;
    }
}


template <class T>       // Devolve o id do vertex onde se encontra o restaurante mais próximo do estafeta
T getRestauranteProximo(vector<T> vetor) {
    int i = 0;
    T proximo;
    for (T rest : vetor) {
        if (i == 0)
            proximo = vetor[0];
        else {
            if (graph.getDist(estafeta_ativo->getPos(), rest) < graph.getDist(estafeta_ativo->getPos(), proximo))
                proximo = rest;
        }
        i++;
    }
    return proximo;
}


template <class T>      // Apaga o id de um dado vertex de um vetor de ids de vertices
void apagar(T inf, vector<T> &vetor) {
    for (typename vector<T>::iterator it = vetor.begin() ; it != vetor.end() ; it++) {
        if ((*it) == inf) {
            vetor.erase(it);
            break;
        }
    }
}


template <class T>      //Apaga pedido de um vetor de pedidos
void apagarPedido(Pedido<T>* pedido, vector<Pedido<T>*> &pedidos){
    for (typename vector<Pedido<T>*>::iterator it = pedidos.begin() ; it != pedidos.end() ; it++) {
        if ((*it) == pedido) {
            pedidos.erase(it);
            break;
        }
    }
}
#endif //CAL_FP05_UTILS_H
