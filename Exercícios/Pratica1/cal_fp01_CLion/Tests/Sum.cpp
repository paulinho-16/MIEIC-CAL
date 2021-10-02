/*
 * Sum.cpp
 */

#include "Sum.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>

void Performance_calcSum() {
    srand(time(NULL));
    int seq[500];
    ofstream escrever;
    escrever.open("Grafico3b.csv");
    escrever << "size;time" << endl;
    for (int n = 10 ; n <= 500 ; n += 10) {
        auto start = std::chrono::high_resolution_clock::now();
        for (unsigned int i = 0 ; i < 1000 ; i++) {
            for (int j = 0 ; j < n ; j++) {
                seq[j] = rand() % (10*n) + 1;
            }
            string result = calcSum(seq,n);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
        escrever << n << ";" << mili << endl;
    }
    escrever.close();
}

string calcSum(int* sequence, int size)
{
    int maior_soma[size];
    int index_seq[size];
    for (int i = 0 ; i < size ; i++) {
        int soma = 0;
        for (int j = i ; j < size ; j++) {
            soma += sequence[j];
            if (i == 0 || soma < maior_soma[j-i]) {
                maior_soma[j-i] = soma;
                index_seq[j-i] = i;
            }
        }
    }
    ostringstream result;
    for (unsigned int j = 0 ; j < size ; j++) {
        result << maior_soma[j] << "," << index_seq[j] << ";";
    }
	return result.str();
}

