#include "utils.h"

void readMap(string directory) {
    string nodes_path = directory + "/nodes.txt";
    string edges_path = directory + "/edges.txt";
    readNodes(nodes_path);
    readEdges(edges_path);
}

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
        while (getline(ss, number, ','))
        {
            cout << number << " - ";
        }
        cout << endl;
    }
    ler.close();
}

void readEdges(string file_directory) {

}

void readTags(string file_directory) {

}