/*
 * Change.cpp
 */

#include "Change.h"
#include <iostream>
#include <sstream>

using namespace std;

 /*             Formalização do problema (alínea a)
    Dados: M (troco), V = {v1,v2,...,vn} (valores unitários das moedas)
    Variáveis de Decisão: X = {x1,x2,...,xn} - queremos decidir: x1 moedas de v1, x2 de v2, etc...
    Função Objetivo: min Somatório de xi - número mínimo de moedas entregues
    Restrições: Somatório de xi*vi (de 0 a n) tem de ser igual a M - Troco correto
 */

 /*             Fórmulas recursivas (alínea b)  (e = erro)
                    { 0, se k = 0
    minCoins(i,k) = { e, se k > 0 && i == 0
                    { minCoins(i,k-vi) + 1, se vi <= k && minCoins(i,k-vi) != e && (minCoins(i-1,k) = e || minCoins(i,k-vi) + 1 < minCoins(i-1,k))
                    { minCoins(i-1,k), noutros casos

                    { nenhum, se k = 0
    lastCoin(i,k) = { nenhum, se k > 0 && i == 0
                    { vi, se vi <= k && minCoins(i,k-vi) != e && (minCoins(i-1,k) = e || minCoins(i,k-vi) + 1 < minCoins(i-1,k))
                    { lastCoin(i-1,k), noutros casos
 */

 void PrintTable(int m, int numCoins, int* coinValues, int** table) {
    cout << "i/j";
    for (int j = 0 ; j < m+1 ; j++) {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 0 ; i < numCoins + 1 ; i++) {
        cout << i << "\t";
        for (int j = 0 ; j < m+1 ; j++) {
            cout << table[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
 }

string calcChange(int m, int numCoins, int *coinValues)
{
    // Alocar espaço para resultados dos sub-problemas
    int **minCoins = new int*[numCoins + 1];
    int **lastCoin = new int*[numCoins + 1];
    for (int i = 0 ; i < numCoins + 1; i++) {
        minCoins[i] = new int[m+1];
        lastCoin[i] = new int[m+1];
    }
    // Iniciar a primeira coluna a 0, uma vez que são necessárias 0 moedas para troco de 0
    for (int j = 0 ; j < numCoins+1 ; j++) {
        minCoins[j][0] = 0;
        lastCoin[j][0] = 0;
    }
    // Iniciar a primeira linha com um valor muito alto, uma vez que não é possível obter qualquer quantia a partir de 0 moedas
    for (int k = 1 ; k < m+1 ; k++) {
        minCoins[0][k] = 1000000;
        lastCoin[0][k] = 0;
    }
    // Solução recursiva usando Programação Dinâmica
    for (int i = 1 ; i < numCoins + 1 ; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (coinValues[i - 1] > j) {  // Não é possível escolher a maior moeda
                minCoins[i][j] = minCoins[i - 1][j];
                lastCoin[i][j] = lastCoin[i - 1][j];
            }
            else {
                if (minCoins[i][j - coinValues[i - 1]] + 1 <= minCoins[i - 1][j]) {
                    minCoins[i][j] = minCoins[i][j - coinValues[i - 1]] + 1;
                    lastCoin[i][j] = coinValues[i - 1];
                }
                else {
                    minCoins[i][j] = minCoins[i - 1][j];
                    lastCoin[i][j] = lastCoin[i - 1][j];
                }
            }
        }
    }
    // alínea c - No ficheiro tests.cpp chamar calcChange(9,3, valoresTabela), em que int valoresTabela[3] = {1,2,5};
    //PrintTable(m, numCoins, coinValues, minCoins);       // alínea c - minCoins (descomentar)
    //PrintTable(m, numCoins, coinValues, lastCoin);       // alínea c - lastCoin (descomentar)
    if (minCoins[numCoins][m] == 1000000)
        return "-"; // Sem solução
    ostringstream result;
    for (int r = m ; r > 0 ; r -= lastCoin[numCoins][r])
        result << lastCoin[numCoins][r] << ";";
    return result.str();
}


