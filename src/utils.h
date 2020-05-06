#ifndef CAL_FP05_UTILS_H
#define CAL_FP05_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void readMap(string directory);

void readNodes(string file_directory);
void readEdges(string file_directory);
void readTags(string file_directory);

#endif //CAL_FP05_UTILS_H
