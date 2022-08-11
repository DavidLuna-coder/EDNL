
#include "../../MaterialesGrafos/alg_grafoPMC.h"
#include "../../MaterialesGrafos/alg_grafo_E-S.h"

using tCoste = double;
struct Ciudad
{

    typename GrafoP<tCoste>::vertice v;
    size_t  almacen;
};

tCoste CosteMinimoTotal(Ciudad& origen, size_t cantidad, const GrafoP<tCoste>& G, std::vector<size_t> almacenes, const std::vector<double> subvencion, std::vector<size_t>& cantidades)
{
    std::vector<typename GrafoP<tCoste>::vertice> P;
    std::vector<tCoste> CostesMinimos = Dijkstra(G,origen.v,P); // Vector de costes minimos
    // Aplicamos las subvenciones
    tCoste minimo = GrafoP<tCoste>::INFINITO;
    for(size_t i = 0; i < CostesMinimos.size(); i++)
    {
        CostesMinimos[i] = subvencion[i]/100 * CostesMinimos[i];
    }
    //Conseguimos el vector de Costes Minimos subvencionado
    typename GrafoP<tCoste>::vertice ciudad = origen.v; 

    while (cantidad > 0)
    {
        minimo = GrafoP<tCoste>::INFINITO;
        for (size_t i = 0; i < P.size(); i++)
        {
            if (P[i] != origen.v && CostesMinimos[i] < minimo && almacenes[i] > 0)
            {
                minimo = CostesMinimos[i];
                ciudad = i;
            }
        }

        //Si cabe todo el producto;
        if (almacenes[ciudad] > cantidad)
        {
            cantidades[ciudad] = cantidad;
            cantidad = 0;
            almacenes[ciudad] -= cantidad;
        }
        else
        {
            cantidad -= almacenes[ciudad];
            cantidades[ciudad] = almacenes[ciudad];
            almacenes[ciudad] = 0;
        }
        
        tCoste Coste = CostesMinimos[ciudad];
    }

    
    
}
