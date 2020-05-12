/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	double latitude;
	double longitude;
	vector<Edge<T> > adj;		// outgoing edges
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue
	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	int type = 0;   // 0 se não for ponto de interesse, 1 se for uma morada, 2 se for um restaurante, 3 se estiver ocupado por um estafeta e 4 unicamente para a Casa dos Estafetas

	void addEdge(int id, Vertex<T> *dest, double w);

public:
	Vertex(T in, double lat, double longt);
	T getInfo() const;
    double getLatitude() const;
    double getLongitude() const;
    int getNumEdges() const;
	double getDist() const;
	Vertex *getPath() const;
	vector<Edge<T>> getAdj() const;
	int getType() const;
	void setType(int type);
	void setDist(double d);
	void setPath(Vertex<T>* p);

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in, double lat, double longt): info(in), latitude(lat), longitude(longt) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(int id, Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(id, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getLatitude() const {
    return this->latitude;
}

template <class T>
double Vertex<T>::getLongitude() const {
    return this->longitude;
}

template <class T>
int Vertex<T>::getNumEdges() const {
    return adj.size();
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template <class T>
vector<Edge<T>> Vertex<T>::getAdj() const {
    return adj;
}

template <class T>
int Vertex<T>::getType() const {
    return type;
}

template <class T>
void Vertex<T>::setType(int type) {
    this->type = type;
}
template <class T>
void Vertex<T>::setDist(double d){
    this->dist=d;
}

template <class T>
void Vertex<T>::setPath(Vertex<T>* p){
    this->path=p;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    int edgeID;
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(int id, Vertex<T> *d, double w);
	Vertex<T>* getDest() const;
	double getWeight();
    int getID();
    void setID(int id);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(int id, Vertex<T> *d, double w): dest(d), weight(w), edgeID(id) {}

template <class T>
Vertex<T>* Edge<T>::getDest() const {
    return dest;
}

template <class T>
double Edge<T>::getWeight() {
    return this->weight;
}

template <class T>
int Edge<T>::getID() {
    return this->edgeID;
}

template <class T>
void Edge<T>::setID(int id) {
    this->edgeID = id;
}

/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	vector<vector<double>> distMin;
	vector<vector<Vertex<T>*>> predecessores;

public:
    Vertex<T> * findVertex(T in) const;
	//bool addVertex(const T &in);
	bool addVertex(Vertex<T>* vertex);
    bool addEdge(int id, T source, T dest);
	int getNumVertex() const;
	int getNumEdges() const;
	void printVertexs();
	void printEdges();
	vector<Vertex<T> *> getVertexSet() const;
    vector<Vertex<T> *> getPath(const T &origin, const T &dest) const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
    bool dijkstraRelax(Vertex<T> *v, Vertex<T> *w, double weight);
    std::vector<Vertex<T> *> dijkstraShortestPath2(Graph<T> * graph, const T &origin, const T &dest);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPathTo(const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
int Graph<T>::getNumEdges() const {
    int sum = 0;
    for (Vertex<T>* v : vertexSet) {
        sum += v->getNumEdges();
    }
    return sum;
}

template <class T>
void Graph<T>::printVertexs() {
    for (Vertex<T>* v : vertexSet) {
        cout << "Id: " << v->getInfo() << "   Latitude: " << v->getLatitude() << "   Longitude: " << v->getLongitude() << endl;
    }
}

template <class T>
void Graph<T>::printEdges() {
    for (Vertex<T>* v : vertexSet) {
        for (Edge<T> e : v->getAdj())
            cout << "ID: " << e.getID() << "   Source: " << v->getInfo() << "   Dest: " << e.dest->getInfo() << "   Weight: " << e.weight << endl;
    }
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(T in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(Vertex<T>* vertex) {
	if (findVertex(vertex->getInfo()) != NULL)
		return false;
	vertexSet.push_back(vertex);
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(int id, T source, T dest) {
	auto v1 = findVertex(source);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	//cout << "Lat1: " << v1->getLatitude() << "   Lat2: " << v2->getLatitude() << "   Long1 = " << v1->getLongitude() << "   Long2 = " << v2->getLongitude() << endl;
	double weight = sqrt((v1->getLatitude() - v2->getLatitude())*(v1->getLatitude() - v2->getLatitude()) + (v1->getLongitude() - v2->getLongitude())*(v1->getLongitude() - v2->getLongitude()));
	v1->addEdge(id, v2, weight);
	return true;
}
template<class T>
vector<Vertex<T> *> Graph<T>::getPath(const T &origin, const T &dest) const{
    vector<Vertex<T> *> res;
    auto o = findVertex(origin);
    auto v = findVertex(dest);
    if (v == nullptr || v->dist == INF) // missing or disconnected
        return res;
    for ( ; v != o && v != nullptr; v = v->path)
        res.push_back(v);
    res.push_back(o);
    reverse(res.begin(), res.end());

    return res;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (auto vertex : vertexSet) {
        vertex->dist = INF;
        vertex->path = NULL;
    }
    auto origem = findVertex(orig);
    origem->dist = 0;
    queue <Vertex<T>*> fifo;
    fifo.push(origem);
    while (!fifo.empty()) {
        Vertex<T>* vertice = fifo.front();
        fifo.pop();
        for (auto edge : vertice->adj) {
            if (edge.dest->dist == INF) {
                fifo.push(edge.dest);
                edge.dest->dist = vertice->dist + 1;
                edge.dest->path = vertice;
            }
        }
    }
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	for (auto vertex : vertexSet) {
	    vertex->dist = INF;
	    vertex->path = NULL;
	}
	Vertex<T>* origem = findVertex(origin);
	origem->dist = 0;
	MutablePriorityQueue<Vertex<T>> fila;
	fila.insert(origem);
	while (!fila.empty()) {
	    Vertex<T>* vertice = fila.extractMin();
	    for (auto &edge : vertice->adj) {
	        if (edge.dest->dist > vertice->dist + edge.weight) {
	            edge.dest->dist = vertice->dist + edge.weight;
	            edge.dest->path = vertice;
                if (!fila.inQueue(edge.dest))
                    fila.insert(edge.dest);
                else
                    fila.decreaseKey(edge.dest);
	        }
	    }
	}
}

template <class T>
bool Graph<T>::dijkstraRelax(Vertex<T> *v, Vertex<T> *w, double weight) {
    if (v->getDist() + weight < w->getDist()) {
        w->setDist(v->getDist() + weight);
        w->setPath(v);
        return true;
    }
    else
        return false;
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::dijkstraShortestPath2(Graph<T> * graph, const T &origin, const T &dest)
{
    std::vector<Vertex<T> *> result;
    auto s = graph->findVertex(origin);
    Vertex<T>* d = graph->findVertex(dest);
    MutablePriorityQueue<Vertex<T>> q;
    q.insert(s);

    while( ! q.empty() ) {
        auto v = q.extractMin();

        if(v == d)
            return graph->getPath(origin, dest);

        for(unsigned int i = 0; i < v->getAdj().size(); i++) {
            auto e = v->getAdj().at(i);
            auto oldDist = e.getDest()->getDist();
            if (this->dijkstraRelax(v, e.getDest(),  e.getWeight())) {
                if (oldDist == INF)
                    q.insert(e.getDest());
                else
                    q.decreaseKey(e.getDest());
            }
        }
    }

    return result;
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	for (auto vertex : vertexSet) {
	    vertex->dist = INF;
	    vertex->path = NULL;
	}
	Vertex<T>* origem = findVertex(orig);
	origem->dist = 0;
	for (unsigned int i = 1 ; i < vertexSet.size() - 1 ; i++) {
	    for (auto vertex : vertexSet) {
	        for (auto edge : vertex->adj) {
                if ((edge.dest)->dist > vertex->dist + edge.weight) {
                    (edge.dest)->dist = vertex->dist + edge.weight;
                    (edge.dest)->path = vertex;
                }
            }
	    }
	}
    for (auto vertex : vertexSet) {
        for (auto edge : vertex->adj) {
            if (vertex->dist + edge.weight < (edge.dest)->dist) {
                cout << "Erro: O grafo tem arestas de peso negativo!\n";
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T>* destino = findVertex(dest);
	stack<T> pilha;
	pilha.push(dest);
	while (destino->getPath() != NULL) {
	    pilha.push(destino->getPath()->getInfo());
	    destino = destino->getPath();
	}
	while (!pilha.empty()) {
	    res.push_back(pilha.top());
	    pilha.pop();
	}
	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    distMin.clear();
    predecessores.clear();                  // Aloca memória para as Matrizes
    distMin = vector<vector<double>>(getNumVertex(), vector<double>(getNumVertex(), INF));
    predecessores = vector<vector<Vertex<T>*>>(getNumVertex(), vector<Vertex<T>*>(getNumVertex(), NULL));

    for (int i = 0 ; i < getNumVertex() ; i++) {
        for (int j = 0 ; j < getNumVertex() ; j++) {
            if (i == j) // Elementos da diagonal da Matriz a 0
                distMin[i][j] = 0;
            else {
                for (auto edge : vertexSet[i]->adj) {
                    if (edge.dest->getInfo() == vertexSet[j]->info) {
                        distMin[i][j] = edge.weight;
                        predecessores[i][j] = vertexSet[i];
                    }
                }
            }
        }
    }

    for (int k = 0 ; k < getNumVertex() ; k++) {
        for (int l = 0 ; l < getNumVertex() ; l++) {
            for (int m = 0 ; m < getNumVertex() ; m++) {
                if (distMin[l][m] > distMin[l][k] + distMin[k][m]) {
                    distMin[l][m] = distMin[l][k] + distMin[k][m];
                    predecessores[l][m] = predecessores[k][m];
                }
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
    int indexOrigem, indexDestino;
    for (int i = 0 ; i < getNumVertex() ; i++) {
        if (vertexSet[i]->info == orig)
            indexOrigem = i;
        else if (vertexSet[i]-> info == dest)
            indexDestino = i;
    }

    while (predecessores[indexOrigem][indexDestino] != vertexSet[indexOrigem]) {
        res.emplace(res.begin(), predecessores[indexOrigem][indexDestino]->info);
        for (int j = 0 ; j < getNumVertex() ; j++) {
            if (vertexSet[j]->info == predecessores[indexOrigem][indexDestino]->info) {
                indexDestino = j;
                break;
            }
        }
    }

    res.push_back(dest);
    res.insert(res.begin(), orig);
    return res;
}


#endif /* GRAPH_H_ */
