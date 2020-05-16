#ifndef CAL_FP05_UTILS_H
#define CAL_FP05_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

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
GraphViewer *gv;

using namespace std;

template <class T>
void showConnection(vector<T> vector);

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

template <class T>
Vertex<T>* readNode(string tuple) {
    tuple = tuple.substr(1, tuple.size() - 2);
    stringstream ss(tuple);
    string id, latitude, longitude;
    getline(ss, id, ',');
    getline(ss, latitude, ',');
    getline(ss, longitude, ',');
    auto* vertex = new Vertex<T>(stoi(id), stof(latitude), stof(longitude));
    return vertex;
}

template <class T>
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

template <class T>
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
    //system("pause");
}

template <class T>
void readMap(string directory) {
    string nodes_path = directory + "/nodes.txt";
    string edges_path = directory + "/edges.txt";
    readNodes<int>(nodes_path);
    readEdges<int>(edges_path);

    cout<<"Testing Connectivity..."<<endl;

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
    system("pause");
}

template <class T>
void readTags(string file_directory) {

}

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
                gv->setVertexColor(vertex->getInfo(), "purple"); break;
            case 4:     // Casa dos Estafetas
                gv->setVertexColor(vertex->getInfo(), "yellow"); break;
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

template<class T>
void recolher_info_casaEstafetas() {
    eatExpress.setCasaEstafetas(0);
    Vertex<T>* vertex = graph.findVertex(eatExpress.getCasaEstafetas());
    vertex->setType(4);
}

template<class T>
void recolher_info_clientes(){
    vector<Cliente<T>*> v;
    Cliente<T>* cliente1 = new Cliente<T>("Antonio", "123456789", 2);
    Cliente<T>* cliente2 = new Cliente<T>("Joaquim", "987654321", 6);
    Cliente<T>* cliente3 = new Cliente<T>("Manuel",  "999999999", 12);
    v.push_back(cliente1);
    v.push_back(cliente2);
    v.push_back(cliente3);
    eatExpress.setClientes(v);
    for (Cliente<T>* cliente : eatExpress.getClientes()) {
        Vertex<T>* vertex = graph.findVertex(cliente->getMorada());
        if (vertex->getType() == 0) {
            vertex->setType(1);
        }
    }
}

template <class T>
void recolher_info_restaurantes(){
    vector<Restaurante<T>*> v;
    Restaurante<T>* restaurante1 = new Restaurante<T>("Casa dos Frangos", "Frangos everywhere", 24);
    Restaurante<T>* restaurante2 = new Restaurante<T>("McDonalds", "Muitos Hamburgueres", 15);
    Restaurante<T>* restaurante3 = new Restaurante<T>("Pizza Hut",  "Pizzas italianas", 9);
    v.push_back(restaurante1);
    v.push_back(restaurante2);
    v.push_back(restaurante3);
    eatExpress.setRestaurantes(v);
    for (Restaurante<T>* restaurante : eatExpress.getRestaurantes()) {
        Vertex<T>* vertex = graph.findVertex(restaurante->getMorada());
        if (vertex->getType() == 0) {
            vertex->setType(2);
        }
    }
}

template <class T>
void recolher_info_estafetas(){
    vector<Estafeta<T>*> v;
    Estafeta<T>* estafeta1 = new Estafeta<T>("Toni", "Primeiro Estafeta", 0);
    v.push_back(estafeta1);
    eatExpress.setEstafetas(v);
    for (Estafeta<T>* estafeta : eatExpress.getEstafetas()) {
        Vertex<T>* vertex = graph.findVertex(estafeta->getPos());
        if (vertex->getType() == 0) {
            vertex->setType(3);
        }
    }
}

void Recolher_Info() {
    recolher_info_casaEstafetas<int>();
    recolher_info_clientes<int>();
    recolher_info_restaurantes<int>();
    recolher_info_estafetas<int>();
}

template <class T>
bool isIn(const vector<Vertex<T>*> &v, Vertex<T>* vertex) {
    for (Vertex<T>* vert : v) {
        if (vert->getInfo() == vertex->getInfo())
            return true;
    }
    return false;
}

int getIndex(vector<Vertex<int>*>v, Vertex<int>* a){
    int i=0;
    for (Vertex<int>* vert : v) {
        if (vert==a) return i;
        i++;
    }
    return -1;
}

template <class T>
void showConnection(vector<T> vec){
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
void showPathGV(vector<Vertex<T>*> v, int restauranteIndex) {
    gv = new GraphViewer(1000, 900, false);
    gv->createWindow(1200, 900);
    gv->defineEdgeColor("black");
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        if (vertex == v[0]) {
            gv->setVertexColor(vertex->getInfo(), "orange");
            gv->setVertexLabel(vertex->getInfo(), "Estafeta");
        }
        else if (vertex == v[v.size()-1]) {
            gv->setVertexColor(vertex->getInfo(), "orange");
            gv->setVertexLabel(vertex->getInfo(), "Cliente");
        }
        else if (isIn(v, vertex)) {
            if (vertex->getType() == 2) {
                gv->setVertexColor(vertex->getInfo(), "green");
                gv->setVertexLabel(vertex->getInfo(), "Restaurante");
            }
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

    Sleep(2000);

    for (unsigned int i = 0 ; i < v.size() - 1 ; i++) {
        Sleep(1000);
        if (i != restauranteIndex - 1 && i != v.size() - 2)     // Para evitar pintar o restaurante e a morada do Cliente.
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
void showPathGV2(vector<Vertex<T>*> v) {
    gv = new GraphViewer(1000, 900, false);
    gv->createWindow(1200, 900);
    gv->defineEdgeColor("black");
    int i=0;
    for(Pedido<int>*pedido : eatExpress.getPedidos()) {
        i++;
        for (Vertex<int>* vertex : graph.getVertexSet()) {
            if (vertex == v[0]) {
                gv->setVertexColor(vertex->getInfo(), "orange");
                gv->setVertexLabel(vertex->getInfo(), "Estafeta");
            }
            else if (vertex->getInfo() == pedido->getRestaurante()->getMorada()) {
                gv->setVertexColor(vertex->getInfo(), "orange");
                stringstream os;
                os << "Restaurante" << i;
                gv->setVertexLabel(vertex->getInfo(), os.str());
            }
            else if (vertex->getInfo() == pedido->getCliente()->getMorada()) {
                gv->setVertexColor(vertex->getInfo(), "orange");
                stringstream os;
                os << "Cliente" << i;
                gv->setVertexLabel(vertex->getInfo(), os.str());
            }
            else if (isIn(v, vertex)) {
                gv->setVertexColor(vertex->getInfo(), "red");
            }
            else {
                gv->setVertexColor(vertex->getInfo(), "blue");
            }
            gv->addNode(vertex->getInfo(), vertex->getLatitude(), vertex->getLongitude());
        }
    }

    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            gv->addEdge(edge.getID(),vertex->getInfo(), edge.getDest()->getInfo(), EdgeType::DIRECTED);
        }
    }
    for (unsigned int i = 0 ; i < v.size() - 1 ; i++) {
        Sleep(1000);
        /*if (i != restauranteIndex - 1 && i != v.size() - 2)     // Para evitar pintar o restaurante e a morada do Cliente.
            gv->setVertexColor(v[i+1]->getInfo(), "red");*/
        for (Edge<int> edge : v[i]->getAdj()) {
            if (edge.getDest() == v[i+1]) {
                gv->setEdgeColor(edge.getID(), "red");
                break;
            }
        }
        gv->rearrange();
    }
}


#endif //CAL_FP05_UTILS_H
