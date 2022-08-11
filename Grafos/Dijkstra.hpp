#pragma once
#include "MaterialesGrafos/grafoPMC.h"
using std::vector;

template<typename tCoste>
tCoste sumarCostes(tCoste v, tCoste w){
    if (v == GrafoP<tCoste>::INFINITO || w == GrafoP<tCoste>::INFINITO)
    {
        return GrafoP<tCoste>::INFINITO;
    }
    return v + w;
};

template<typename tCoste>
vector<tCoste> Dijkstra (const GrafoP<tCoste>& G,typename GrafoP<tCoste>::vertice origen, vector<typename GrafoP<tCoste>::vertice>& P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vertice v,w;
    size_t n = G.numVert();
    vector<bool> S(n,false); //Vector de booleanos a falso;

    vector<tCoste> D;
    D = G[origen]; // Rellenamos el vector con los costes originales
    D[origen] = 0; // Coste de origen a origen
    P = vector<vertice>(n,origen); //Nodo anterior es origen
    S[origen] = true; // Evitar origen;

    for (size_t i = 1; i < n-1; i++)
    {
        //Primero calculamos el mas cercano al origen no incluido en S
        tCoste MIN = GrafoP<tCoste>::INFINITO;        
        for ( v = 0; v < n; v++)
        {
            if(!S[v] && D[v] <= MIN)
            {
                w = v;
                MIN = D[v];
            }
        }
        S[w] = true;

        for ( v = 0; v < n; v++)
        {
            tCoste owv = sumarCostes(D[w], G[w][v]);
            if (!S[v] && owv < D[v])
            {
                D[v] = owv;
                P[v] = w;
            }
        }
        
    }
    return D;
}

template<typename tCoste>
vector<tCoste> DijkstraInverso(const GrafoP<tCoste>& G, typename GrafoP<tCoste>::vertice destino, vector<typename GrafoP<tCoste>::vertice>& P)
{
    using vertice = typename GrafoP<tCoste>::vertice;
    const tCoste& INFINITO = GrafoP<tCoste>::INFINITO;
    vertice v,w;
    size_t n = G.numVert();
    vector<bool> S(n,false);
    vector<tCoste> D(n,INFINITO);
    for (size_t i = 0; i < n-1; i++)
    {
        D[i] = G[i][destino];
    }
    D[destino] = 0;
    S[destino] = true;
    P = vector<vertice>(n,destino);

    for ( size_t i = 1; i < n-1; i++)
    {
        tCoste MIN = INFINITO;
        for ( v = 0; v < n ; v++)
        {
            if (!S[v] && D[v] < MIN)
            {
                w = v;
                MIN = D[v];
            }
        }

        S[w] = true;

        for ( v = 0; v < n; v++)
        {
            tCoste vwd = sumarCostes(D[w],G[v][w]);
            if (!S[v] && vwd < D[v])
            {
                P[v] = w;
                D[v] = vwd;
            }
        }
        
    }

    return D;
}