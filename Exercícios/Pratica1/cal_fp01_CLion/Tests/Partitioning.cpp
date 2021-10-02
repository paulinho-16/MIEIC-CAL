/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
   if (k == 1 || k == n)
       return 1;
   return s_recursive(n-1,k-1) + k*s_recursive(n-1,k);
}

int s_dynamic(int n,int k)
{
    int comprimento = n-k+1;
    int valores[comprimento];
    for (int i = 0 ; i < comprimento ; i++)
        valores[i] = 1;
    for (int j = 2 ; j <= k ; j++) {
        for (int l = 1; l < comprimento ; l++) {
            valores[l] += j*valores[l-1];
        }
    }
	return valores[comprimento-1];
}


int b_recursive(int n)
{
    int soma = 0;
	for (int k = 1 ; k <= n ; k++) {
	    soma += s_recursive(n,k);
	}
	return soma;
}

int b_dynamic(int n)
{
	int valores[n + 1];
	for (int i = 1 ; i <= n ; i++) {
	    valores[i] = 1;
	    for (int j = i-1 ; j > 1 ; j--)
	        valores[j] = valores[j-1] + j*valores[j];
	}
	int soma = 0;
	for (int k = 1 ; k <= n ; k++)
	    soma += valores[k];
	return soma;
}


