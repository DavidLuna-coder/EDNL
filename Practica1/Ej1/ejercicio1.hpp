#ifndef _EJERCICIO1_
#define _EJERCICIO1_
#include "Abin_Enlazada.h"

template<typename T>
int contarNodos(Abin<T> A)
{
    int contador;
    if (!A.arbolVacio())
    {
        typename Abin<T>::nodo n = A.raiz();
        contador = contar(n, A);
    }
    
    return contador;
}

template <typename T>
int contar(typename Abin<T>::nodo n, Abin<T> A)
{
    int contador = 0;
    if (n != Abin<T>::NODO_NULO)
    {
        contador = 1 + contar(A.hijoIzqdo(n),A) + contar(A.hijoDrcho(n),A);
    }
    
    return contador;
}



#endif