#ifndef CAL_FP05_UTILS_H
#define CAL_FP05_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "Graph.h"

extern Graph<int> graph;

using namespace std;

void readMap(string directory);

template <class T>
void readNodes(string file_directory);
template <class T>
void readEdges(string file_directory);
template <class T>
void readTags(string file_directory);

#endif //CAL_FP05_UTILS_H
