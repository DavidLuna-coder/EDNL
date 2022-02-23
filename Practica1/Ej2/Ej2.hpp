#include "Abin_Enlazada.h"

template <typename T>
int Altura_Rec(Abin<T> A,typename Abin<T>::nodo n)
{
    int max,alt1,alt2;
    alt2 = 0;
    alt1 = 0;
    if(n != Abin<T>::NODO_NULO)
    {
        alt1 = 1 + Altura_Rec(A,A.hijoIzqdo(n));
        alt2 = 1 + Altura_Rec(A,A.hijoDrcho(n));

        if (alt1>=alt2)
        {
            max = alt1;
        }
        else
        {
            max = alt2;
        }
    }
    else max = 0;
    
    return max;
}

template <typename T>
int Altura(Abin<T> A)
{
    typename Abin<T>::nodo n = A.raiz();
    return Altura_Rec(A,n) - 1;
}