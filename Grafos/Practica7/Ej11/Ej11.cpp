#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../Floyd.hpp"
#include "../../MaterialesGrafos/matriz.h"
using namespace std;
using vertice = typename GrafoP<double>::vertice;

struct Puente
{
    vertice c1;
    vertice c2;
};

matriz<double> CostesMinimos(const GrafoP<double> &G1, const GrafoP<double> &G2, const GrafoP<double> &G3, vector<Puente> P)
{
    size_t n1 = G1.numVert();
    size_t n2 = G2.numVert();
    size_t n3 = G3.numVert();
    // Construimos un grafo de tamaño suficiente

    GrafoP<double> G(n1 + n2 + n3);

    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < n1; j++)
        {
            G[i][j] = G1[i][j];
        }
    }

    for (size_t i = n1; i < n1 + n2; i++)
    {
        for (size_t j = 0; j < n1 + n2; j++)
        {
            G[i][j] = G2[i%n2][j%n2];
        }
    }

    for (size_t i = n1 + n2; i < n1 + n2 + n3; i++)
    {
        for (size_t j = 0; j < n1 + n2 + n3; j++)
        {
            G[i][j] = G2[i%n3][j%n3];
        }
    }

    // Establecemos los puentes
    for (size_t i = 0; i < P.size(); i++)
    {
        G[P[i].c1][P[i].c2] = 0;
        G[P[i].c2][P[i].c1] = 0;
    }

    matriz<vertice> mvertices;
    
    return Floyd(G,mvertices);
}
