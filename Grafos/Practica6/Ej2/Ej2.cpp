/* 2. Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que
minimiza la suma de las distancias mínimas a sus dos nodos más alejados. Definiremos
el diámetro del grafo como la suma de las distancias mínimas a los dos nodos más
alejados del pseudocentro del grafo.
Dado un grafo conexo representado mediante matriz de costes, implementa un
subprograma que devuelva la longitud de su diámetro.*/

#include "../../Floyd.hpp"
#include "../../MaterialesGrafos/alg_grafo_E-S.h"
#include "../../MaterialesGrafos/grafoPMC.h"
#include <iostream>
#include <algorithm>
#include <time.h>
template<typename tCoste>
tCoste diametro (const GrafoP<tCoste>& G)
{
    using vertice = typename GrafoP<tCoste>::vertice;
    matriz<vertice> P(G.numVert(),vertice()); 
    matriz<tCoste> A = Floyd(G,P); //Matriz de Costes minimos
    tCoste o,d; //Costes de origen y destino.
    tCoste diametro = GrafoP<tCoste>::INFINITO;

    vertice pseudo;
    for (size_t i = 0; i < G.numVert(); i++)
    {
        o = 0;
        d = 0;
        for (size_t j = 0; j < G.numVert(); j++)
        {
            if(i != j)
            {
                if (A[i][j] > o)
                {
                    d = o;
                    o = A[i][j];
                }
                else if (A[i][j]>d)
                {
                    d = A[i][j];    
                }
                
            }

        }


        if (diametro > d + o)
        {
            diametro = o + d;
            pseudo = i;             //Pseudocentro
        }
        
    }
    std::cout<<"PseudoCentro: " << pseudo << std::endl;
    return diametro;
    
}

int main()
{
    srand(time(NULL));
    size_t n = 5;
    GrafoP<size_t> G(n);
    size_t INFINITO = 4294967295;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            std::cout<<"Introduce la arista: " << i << " " << j << std::endl;
            G[i][j] = rand()%999;
            G[j][i] = G[i][j];
        }
        
    }

    matriz<typename GrafoP<size_t>::vertice> P(G.numVert());
    std::cout<< G << std::endl;
    std::cout<< Floyd(G,P) <<std::endl;
    std::cout<<diametro(G)<<std::endl;

}