#ifndef CAL_FP05_CONETIVIDADE_H
#define CAL_FP05_CONETIVIDADE_H

#include "Graph.h"
extern Graph<int> graph;

// Algoritmo de visita em profundidade
template <class T>
void dfsVisit(Vertex<T> *v, std::vector<Vertex<T> *> & res) {
    v->visited=true;
    res.push_back(v);
    for(unsigned int i = 0; i < v->getAdj().size(); i++) {
        if (!v->getAdj().at(i).getDest()->visited) {
            dfsVisit(v->getAdj().at(i).getDest(), res);
        }
    }
}

// Função que chama o algoritmo de visita em profundidade, tratando das suas preparações
template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graphh, Vertex<T> * initial) {
    vector<Vertex<T> *> res;
    for(auto vertex: graphh->getVertexSet()){
        vertex->visited=false;
    }
    dfsVisit(initial, res);

    return res;
}

// Função que verifica se um vetor de vértices contém um dado vértice
template <class T>
bool containsVertex(std::vector<Vertex<T> *> vectorVert, Vertex<T> * vert){
    for(auto v : vectorVert)
        if( (vert->getInfo()) == (v->getInfo()))
            return true;
    return false;
}

// Função que mostra no GraphViewer a conetividade de um grafo
template <class T>
void showConnection(vector<T> vec) {        // Apresenta no ecrã a conetividade do grafo
    gv = new GraphViewer(1000, 900, false);
    gv->createWindow(1200, 900);
    gv->defineEdgeColor("black");
    vector<Vertex<T>*> vector_vertexs;
    for (Vertex<T>* vertex : graph.getVertexSet()) {
        gv->setVertexColor(vertex->getInfo(), "black");
        gv->addNode(vertex->getInfo(), vertex->getLatitude(), vertex->getLongitude());
    }
    for (Vertex<T>* vertex : graph.getVertexSet()) {
        for (Edge<T> edge : vertex->getAdj()) {
            gv->addEdge(edge.getID(),vertex->getInfo(), edge.getDest()->getInfo(), EdgeType::DIRECTED);
        }
    }
    for (unsigned int i = 0 ; i < vec.size() ; i++) {
        Vertex<T>* vertex = graph.findVertex(vec[i]);
        gv->setVertexColor(vertex->getInfo(),"green");
        for (Edge<T> edge : vertex->getAdj()) {
            gv->setEdgeColor(edge.getID(), "green");
        }
    }
    gv->rearrange();
}

// Função que avalia a conetividade de um grafo
template <class T>
vector<Vertex<T>*> Avaliar_Conetividade(Vertex<T> *v) {               // Avalia a Conetividade do Grafo a partir de V

    vector<Vertex<T>*> res_normal= dfs(&graph,v); // Pesquisa em profundidade no grafo normal
    Graph<T> *invertedGraph = graph.invert();   //Inverter Grafo
    Vertex<T>  *invInitial = invertedGraph->findVertex( (v->getInfo()));
    vector<Vertex<T> *> res_invert = dfs(invertedGraph, invInitial); // Pesquisa em profundidade no grafo invertido

    vector<Vertex<T> *> res;
    for(auto v: res_normal){
        if(containsVertex(res_invert, v))
            res.push_back(v);
    }

    return res;
}

#endif //CAL_FP05_CONETIVIDADE_H
