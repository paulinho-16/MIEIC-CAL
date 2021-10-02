/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
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
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
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
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set
	vector<vector<double>> distMin;
	vector<vector<Vertex<T>*>> predecessores;

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
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
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
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
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
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
