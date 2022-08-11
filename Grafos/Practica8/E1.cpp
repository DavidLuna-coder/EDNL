#include "../MaterialesGrafos/grafoMA.h"
#include "../MaterialesGrafos/grafoPMC.h"
#include "../Kruskal.hpp"
#include "../Floyd.hpp"
#include <cmath>
using namespace std;
using tCoste = double;

struct ciudad
{
    double x;
    double y;
    explicit ciudad(double x_, double y_) : x(x_), y(y_){};
};

pair<Particion, matriz<tCoste>> ArchipielagoTombuctu(vector<ciudad> ciudades, Grafo GA)
{
    // 1º Pasar la matriz de Adyacencia a una de costes.
    using vertice = typename GrafoP<tCoste>::vertice;
    size_t n = GA.numVert();
    GrafoP<tCoste> G(n);
    Particion P(n);
    matriz<tCoste> CostesTotales(n);
    matriz<vertice> t;
    // Construimos la matriz de costes
    for (vertice i = 0; i < n; i++)
    {
        for (vertice j = i; j < n; j++)
        {
            if (GA[i][j])
            {
                G[i][j] = sqrt(pow(ciudades[i].x - ciudades[j].x, 2) + pow(ciudades[i].y - ciudades[j].y, 2));
            }

            if (GA[j][i])
            {
                G[j][i] = sqrt(pow(ciudades[i].x - ciudades[j].x, 2) + pow(ciudades[i].y - ciudades[j].y, 2));
            }
        }
    }

    CostesTotales = Floyd(G, t);

    for (vertice i = 0; i < n; i++)
    {
        for (vertice j = i; j < n; j++)
        {
            if(G[i][j]!=GrafoP<tCoste>::INFINITO && P.encontrar(i) != P.encontrar(j))
            {
                P.unir(i,j);
            }
        }
    }
    return make_pair(P, CostesTotales);
}
