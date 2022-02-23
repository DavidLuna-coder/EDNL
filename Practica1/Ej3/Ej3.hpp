/*3. Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine
la profundidad de este nodo en dicho árbol.*/
#ifndef EJ3
#define EJ3

#include <iostream>
#include "Abin_Enlazada.h"

template <typename T>
int Profundidad(Abin<T> A, typename Abin<T>::nodo n)
{
    int cont = 0;
    while (A.padre(n) != Abin<T>:: NODO_NULO)
    {
        n = A.padre(n);
        cont ++;
    }

    return cont;
}

#endif