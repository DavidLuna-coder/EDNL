#include "../../MaterialesGrafos/alg_grafoPMC.h"
#include "../../MaterialesGrafos/alg_grafo_E-S.h"
#include "../../MaterialesGrafos/matriz.h"
#include <iostream>
using namespace std;
std::vector<bool> CiudadesPosibles(const GrafoP<double> &G1, const GrafoP<double> &G2, typename GrafoP<double>::vertice origen, double dinero)
{
    size_t n = G1.numVert(); // Numero de ciudades

    GrafoP<double> G3(2 * n);
    // Rellenamos el grafo

    // Rellenamos la esquina superior izq del grafo
    for (auto i = 0; i < n; i++)
    {
        for (auto j = 0; j < n; j++)
        {
            G3[i][j] = G1[i][j];
        }
    }
    // Rellenamos esquina inferior derecha
    for (auto i = n; i < 2 * n; i++)
    {
        for (auto j = n; j < 2 * n; j++)
        {
            G3[i][j] = G2[i % n][j % n];
        }
    }

    // Rellenamos esquina superior dcha
    for (auto i = 0; i < n; i++)
    {
        for (auto j = n; j < 2 * n; j++)
        {
            if (i == j % n)
                G3[i][j] = 0;
            else
                G3[i][j] = GrafoP<double>::INFINITO;
        }
    }

    // Rellenamos esquina inferior izq
    for (auto i = n; i < 2 * n; i++)
    {
        for (auto j = 0; j < n; j++)
        {
            if (i % n == j)
                G3[i][j] = 0;
            else
                G3[i][j] = GrafoP<double>::INFINITO;
        }
    }

    cout << G3 << "\n";
    vector<typename GrafoP<double>::vertice> P;
    vector<double> CostesMinimos = Dijkstra(G3, origen, P);
    cout << CostesMinimos<<"\n";
    // Vector de costes Minimos
    std::vector<bool> llega(n, false);

    for (size_t i = 0; i < 2 * n; i++)
    {
        if (llega[i % n] == false && CostesMinimos[i] != GrafoP<double>::INFINITO && dinero >= CostesMinimos[i])
        {
            llega[i % n] = true;
        }
    }

    return llega;
}

int main()
{
    srand(time(NULL));
    GrafoP<double> G1(8), G2(8);
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (i==j)
            G1[i][j]=0;
            else
            G1[i][j] = rand() % 100 + 1;
        }
    }

    std::cout << "---------------------------\n";

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (i==j)
            G2[i][j]=0;
            else
            G2[i][j] = rand() % 100 + 1;
        }
    }

    std::cout << "---------------------------\n";

    vector<bool> llega = CiudadesPosibles(G1, G2, 3, 14);
    std::cout << llega;
}