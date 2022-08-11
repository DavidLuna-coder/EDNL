#include "MaterialesGrafos/grafoPMC.h"
#include "MaterialesGrafos/particion.h"
#include "MaterialesGrafos/apo.h"


template<typename tCoste>
GrafoP<tCoste> Kruskal (const GrafoP<tCoste> Gr)
{
    using arista = typename GrafoP<tCoste>::arista;
    using vertice = typename GrafoP<tCoste>::vertice;
    const tCoste& INFINITO = GrafoP<tCoste>::INFINITO;
    //Creamos un Grafo nuevo
    const size_t n = Gr.numVert();
    GrafoP<tCoste> G(n);
    Apo<arista> A ((n*n-1)/2);
    Particion P(n);
//Rellenar el Apo con las aristas
    for (vertice v = 0; v < n - 1; v++)
    {
        for (vertice w = 0; w < n; w++)
        {
            if (Gr[v][w] != INFINITO)
            {
                A.insertar(arista(v,w,G[v][w]));
            }   
        }
    }

    size_t i = 0;

    while (i < n-1)
    {
        arista a = A.cima();
        A.suprimir();
        if (P.encontrar(a.orig) != P.encontrar(a.dest))
        {
            P.unir(a.orig,a.dest);
            G[a.orig][a.dest] = G[a.dest][a.orig];
            i++;
        }
        
    }
    
    return G;
}