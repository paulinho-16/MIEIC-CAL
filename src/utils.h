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

template <class T>
void showConnection(vector<T> vector);

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

/*template <class T>
Vertex<T>* readNode(string tuple) {
    tuple = tuple.substr(1, tuple.size() - 2);
    stringstream ss(tuple);
    string id, latitude, longitude;
    getline(ss, id, ',');
    getline(ss, latitude, ',');
    getline(ss, longitude, ',');
    auto* vertex = new Vertex<T>(stoi(id), stof(latitude), stof(longitude));
    return vertex;
}*/

template <class T>
void readNodes(string file_directory) {     // Lê os vértices do ficheiro enviado como parâmetro
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

template <class T>
void readEdges(string file_directory) {          // Lê as arestas do ficheiro enviado como parâmetro
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

template <class T>
void readMap(string directory) {             // Constrói os paths dos ficheiros e lê os vértices e as arestas destes
    string nodes_path = directory + "/nodes.txt";
    string edges_path = directory + "/edges.txt";
    readNodes<int>(nodes_path);
    readEdges<int>(edges_path);
}

template <class T>
void Avaliar_Conetividade() {               // Avalia a Conetividade do Grafo
    cout<<"\nTesting Connectivity..."<<endl;

    vector<T> vec= graph.dfs();
    /*vector<T> vec;
    for(Vertex<T>* vertex: graph.getVertexSet()){
        vec.push_back(vertex->getInfo());
    }*/
    showConnection<T>(vec);
    if(vec.size()==graph.getVertexSet().size()){
        cout<<"Grafo fortemente conexo!"<<endl;
    }
    else{
        for(Vertex<T>* vertex:graph.getVertexSet()){
            //TODO
        }
    }
}

void Visualizar_Mapa() {        // Apresenta o grafo completo, mostrando todos os clientes, restaurantes, e estafetas que estão presentes na empresa
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

template<class T>
void recolher_info_clientes() {       // Lê as informações relativas aos clientes do ficheiro

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
        v.push_back(cliente);
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

template <class T>
void recolher_info_restaurantes() {       // Lê as informações relativas aos restaurantes do ficheiro
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
        v.push_back(restaurante);
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

void recolher_info_transportes() {       // Lê as informações relativas aos transportes do ficheiro
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

template <class T>
void recolher_info_estafetas() {       // Lê as informações relativas aos estafetas do ficheiro
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
        v.push_back(estafeta);
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

void Recolher_Info() {       // Lê as informações dos clientes, restaurantes e estafetas presentes na empresa
    recolher_info_casaEstafetas<int>();
    recolher_info_clientes<int>();
    recolher_info_restaurantes<int>();
    recolher_info_transportes();
    recolher_info_estafetas<int>();
}

/*template <class T>
bool isIn(const vector<Vertex<T>*> &v, Vertex<T>* vertex) {
    for (Vertex<T>* vert : v) {
        if (vert->getInfo() == vertex->getInfo())
            return true;
    }
    return false;
}*/

template <class T>
int isInPedidos(Vertex<T>* vertex) {        // Verifica se um dado vertex é um dos vertices envolvidos nos pedidos
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

/*int getIndex(vector<Vertex<int>*>v, Vertex<int>* a){
    int i=0;
    for (Vertex<int>* vert : v) {
        if (vert==a) return i;
        i++;
    }
    return -1;
}*/

template <class T>
void atribuirEstafeta(Pedido<T> *pedido) {      // Atribui o estafeta que estiver mais perto do restaurante indicado no pedido a esse pedido
    double minDist = 10000;
    for(Estafeta<T>* estafeta : eatExpress.getEstafetas()) {
        double d=graph.getDist(pedido->getRestaurante()->getMorada(),estafeta->getPos());
        if(d < minDist) {
            minDist = d;
            pedido->setEstafeta(estafeta);
        }
    }
}

template <class T>
void showConnection(vector<T> vec) {        // Apresenta no ecrã a conetividade do grafo
    gv = new GraphViewer(1000, 900, false);
    gv->createWindow(1200, 900);
    gv->defineEdgeColor("black");
    vector<Vertex<T>*> vector_vertexs;
    for(T t : vec){
        Vertex<T>* vert=graph.findVertex(t);
        for (Vertex<int>* vertex : graph.getVertexSet()) {
            if (vert == vertex) {
                gv->setVertexColor(vertex->getInfo(), "black");
                gv->addNode(vertex->getInfo(), vertex->getLatitude(), vertex->getLongitude());
                vector_vertexs.push_back(vert);
            }
        }
    }
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            gv->addEdge(edge.getID(),vertex->getInfo(), edge.getDest()->getInfo(), EdgeType::DIRECTED);
        }
    }
    for (unsigned int i = 0 ; i < vector_vertexs.size() ; i++) {
        Sleep(250);
        gv->setVertexColor(vector_vertexs[i]->getInfo(),"green");
        for (Edge<int> edge : vector_vertexs[i]->getAdj()) {
            if (edge.getDest() == vector_vertexs[i+1]) {
                gv->setEdgeColor(edge.getID(), "green");
                break;
            }
        }
        gv->rearrange();
    }
}

template <class T>
void showPathGV(vector<Vertex<T>*> v) {     // Apresenta o grafo e o percurso indicado no parâmetro
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
            cout << "Estafeta " + to_string(n_pedido) << " - " << pedido->getEstafeta()->getNome() << " (" << pedido->getEstafeta()->getNif() << ")\n";
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
        Sleep(1000);
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

template <class T>
void showMultiplePathsGV(vector<vector<Vertex<T>*>> percursos) {        // Apresenta o grafo e os vários percursos dos vários estafetas
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
            cout << "Estafeta " + to_string(n_pedido) << " - " << pedido->getEstafeta()->getNome() << " (" << pedido->getEstafeta()->getNif() << ")\n";
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

    string color;
    int num_percurso=1;
    // Desenha os percursos dos vários estafetas
    for(vector<Vertex<T>*> v: percursos) {
        for (unsigned int i = 0 ; i < v.size() - 1 ; i++) {
            if(num_percurso % 4 == 1) {color ="red";}
            if(num_percurso % 4 == 2) {color = "blue";}
            if(num_percurso % 4 == 3) {color = "green";}
            if(num_percurso % 4 == 0) {color = "orange";}
            Sleep(1000);
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

template <class T>
T getRestauranteProximo(vector<T> vetor) {      // Devolve o id do vertex onde se encontra o restaurante mais próximo do estafeta
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

template <class T>
void apagar(T inf, vector<T> &vetor) {          // Apaga o id de um dado vertex de um vetor de ids de vertices
    for (typename vector<T>::iterator it = vetor.begin() ; it != vetor.end() ; it++) {
        if ((*it) == inf) {
            vetor.erase(it);
            break;
        }
    }
}

#endif //CAL_FP05_UTILS_H
