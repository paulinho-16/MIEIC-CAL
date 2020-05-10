#ifndef CAL_FP05_UTILS_H
#define CAL_FP05_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "Graph.h"
#include "../GraphViewerLib/graphviewer.h"

#include "Cliente.h"
#include "Estafeta.h"
#include "Restaurante.h"

extern Graph<int> graph;

using namespace std;

void readMap(string directory);

template <class T>
void readNodes(string file_directory);
template <class T>
Vertex<T>* readNode(string tuple);
template <class T>
void readEdges(string file_directory);
template <class T>
void readTags(string file_directory);

void Visualizar_Mapa();

//template <class T>
//vector<Cliente<T>*>  recolher_info_clientes();
template <class T>
vector<Restaurante<T>*>  recolher_info_restaurantes();
template <class T>
vector<Restaurante<T>*>  recolher_info_estafetas();

void buildApp();
#endif //CAL_FP05_UTILS_H
