/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
    if (n <= 1)
        return 1;
    else
	    return n*factorialRecurs(n-1);
}

int factorialDinam(int n)
{
    int soma = 1;
    for (int i = n ; i >= 1 ; i--) {
        soma *= i;
    }
    return soma;
}

// Complexidade Temporal:   Recursiva - O(n)    Iterativa - O(n)
// Complexidade Espacial:   Recursiva - O(n)    Iterativa - O(1)
