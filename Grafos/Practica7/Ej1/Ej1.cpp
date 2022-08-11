/*1. Tu agencia de viajes “OTRAVEZUNGRAFO S. A.” se enfrenta a un curioso cliente.
Es un personaje sorprendente, no le importa el dinero y quiere h acer el viaje más caro
posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de
dinero posible (ojalá todos los clientes fueran así), no le importa el origen ni el destino
del viaje.
Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente
el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino
de tan curioso viaje. Se parte de la matriz de costes directos entre las ciudades del grafo.*/

#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../MaterialesGrafos/alg_grafo_E-S.h"
#include "../../MaterialesGrafos/matriz.h"
#include "../../Floyd.hpp"
#include <iostream>
#include <limits>
using tCoste = size_t;

//* Es necesario hacer una modificación de Floyd para este ejercicio y obtener el camino de costes máximos entre cada par de ciudades.


matriz<tCoste> FloydMaximo (const GrafoP<tCoste>& G)
{
    using vertice = typename GrafoP<tCoste>::vertice;
    const tCoste& INFINITO = GrafoP<tCoste>::INFINITO;
    size_t n = G.numVert();
    matriz<tCoste> A(n);
    matriz <vertice> P(n);
    for (vertice i = 0; i < n; i++)
    {
        A[i] = G[i];
        A[i][i] = 0;
        P[i] = vector<vertice>(n,i);
    }
    

    for (vertice k = 0; k < n; k++)
    {
        for (vertice i = 0; i < n; i++)
        {
            for(vertice j = i; j < n; j++)
            {
                tCoste ikj = suma(A[i][k],A[k][j]);
                if ((A[i][j] == GrafoP<tCoste>::INFINITO && ikj != GrafoP<tCoste>::INFINITO) || (ikj > A[i][j] && ikj!=GrafoP<tCoste>::INFINITO))
                {
                    A[i][j] = ikj;
                    A[j][i] = ikj;
                    P[i][j]= k;
                }
            }
        }
        
    }
    std::cout<< A << std::endl;
    std:: cout << P << std::endl;
    return A;
    
}
GrafoP<tCoste>::arista viajeMasCaro(const GrafoP<tCoste>& G)
{
    matriz<tCoste> A = FloydMaximo(G);
    size_t n = G.numVert();
    tCoste max = G[0][0];
    GrafoP<tCoste>::arista a;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (A[i][j] != GrafoP<tCoste>::INFINITO && A[i][j] > max || max == GrafoP<tCoste>::INFINITO )
            {
                max = A[i][j];
                a.orig = i;
                a.dest = j;
                a.coste = max;
            }
            
        }
        
    }
    return a;
}

int main()
{
    srand(time(NULL));
    using vertice = typename GrafoP<tCoste>::vertice;
    using arista = GrafoP<tCoste>::arista;
    const tCoste& INFINITO = GrafoP<tCoste>::INFINITO;
    size_t n = 3;
    GrafoP<tCoste> G(n);
    for(vertice v = 0; v < G.numVert(); v++)
    {
        for (vertice w = 0; w < G.numVert(); w++)
        {
            if(v == w)
            {
                G[v][w] = INFINITO;
            }
            else
            {
                tCoste x = rand()%10;
                /*if (!x%5)
                {
                    G[v][w] = INFINITO;
                }
                else*/
                G[v][w] = x;
            }
        }
        
    }

    std::cout << G << std::endl;
    matriz<vertice> P(n);
    arista a = viajeMasCaro(G);

    std::cout << "Origen: " <<a.orig << " Destino: " << a.dest << " Coste: " << a.coste << std::endl;
    std::cout << Floyd(G,P)<<std::endl;
    return 0;
}