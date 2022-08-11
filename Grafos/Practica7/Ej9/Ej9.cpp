#include <iostream>
#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../Dijkstra.hpp"
#include <algorithm>
typedef typename GrafoP<double>::vertice vertice;
using namespace std;
double costeMinimo(const GrafoP<double> &Tren, const GrafoP<double> &Bus, vertice origen, vertice destino, double cTaxi)
{
    size_t n = Tren.numVert();
    // Creamos un grafo de tamaño 2n
    GrafoP<double> G(2 * n);

    // Costes de tren
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            G[i][j] = Tren[i][j];
        }
    }

    // Costes de Bus
    for (size_t i = n; i < 2 * n; i++)
    {
        for (size_t j = n; j < 2 * n; j++)
        {
            G[i][j] = Bus[i][j];
        }
    }

    //Coste de transbordo
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = n; j < 2 * n; j++)
        {
            if(i == j)
            {
                G[i][j] = cTaxi;
            }
        }
    }

    // Opciones: Bus - Bus, Tren - Tren, Bus - Tren, Tren - Bus
    vector<vertice> caminoOrigenBus;
    vector<double> costesOrigenBus = Dijkstra(G,origen,caminoOrigenBus);

    vector<vertice> caminoOrigenTren;
    vector<double> costesOrigenTren = Dijkstra(G,origen + n,caminoOrigenTren);

    double minimo = min(costesOrigenBus[destino],costesOrigenBus[destino + n], costesOrigenTren[destino]);
    minimo = min(minimo,costesOrigenTren[destino+n]);

    return minimo;

}