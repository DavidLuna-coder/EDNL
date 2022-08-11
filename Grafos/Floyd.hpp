#pragma once
#include "MaterialesGrafos/grafoPMC.h"
#include "MaterialesGrafos/matriz.h"
using std::vector;


template<typename tCoste>
tCoste suma(tCoste v, tCoste w){
    if (v == GrafoP<tCoste>::INFINITO || w == GrafoP<tCoste>::INFINITO)
    {
        return GrafoP<tCoste>::INFINITO;
    }
    return v + w;
};

template <typename tCoste>
matriz<tCoste> Floyd (const GrafoP<tCoste>& G, matriz<typename GrafoP<tCoste>::vertice>& P)
{
    using vertice = typename GrafoP<tCoste>::vertice;
    size_t n = G.numVert();
    matriz<tCoste> A(n);
    P = matriz<vertice>(n);

    for (vertice i = 0; i < n; i++)
    {
        A[i] = G[i]; //Matriz de costes directos
        A[i][i] = 0; //Coste de i a i 0
        P[i] = vector<vertice>(n,i); // Vertice intermedio de origen i a destino es i en camino directo
    }

    //Minimizar costes
    for (vertice k = 0; k < n; k++)
    {
        for (vertice j = 0; j < n; j++)
        {
            for (vertice i = 0; i < n; i++)
            {
                tCoste ikj = suma(A[i][k],A[k][j]);
                if (ikj < A[i][j])
                {
                    A[i][j] = ikj;
                    P[i][j] = k;
                }
                
            }
            
        }
        
    }    
    return A;
    
}
