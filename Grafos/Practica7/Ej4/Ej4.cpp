#include "../../MaterialesGrafos/alg_grafoPMC.h"
#include "../../DijkstraInverso.hpp"
struct parte
{
    std::vector<size_t> cargas;
};

double DistanciaTotal(const GrafoP<double> G, parte P, typename GrafoP<double>::vertice capital)
{
    std::vector<typename GrafoP<double>::vertice> v;
    std::vector<double> DistanciaDesdeOrigen = Dijkstra(G,capital,v); //Costes Minimos desde Origen
    std::vector<double> DistanciaHastaOrigen = DijkstraInverso(G,capital,v); //Costes Minimos Hasta Origen

    double total = 0;
    for (size_t i = 0; i < G.numVert(); i++)
    {
        total += P.cargas[i] * (DistanciaDesdeOrigen[i] + DistanciaHastaOrigen[i]);
    }
    
    return total;
}