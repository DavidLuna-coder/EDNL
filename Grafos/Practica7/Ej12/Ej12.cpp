#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../MaterialesGrafos/matriz.h"
#include "../../Floyd.hpp"
using vertice = typename GrafoP<double>::vertice;
using namespace std;

struct Puente
{
    vertice c1;
    vertice c2;

    Puente(vertice v1,vertice v2):c1(v1),c2(v2){}
};

double costeGlobal(matriz<double> M)
{
    double costeGlobal = 0;
    for (size_t i = 0; i < M.dimension(); i++)
    {
        for (size_t j = 0; j < M.dimension(); j++)
        {
            if (M[i][j] != GrafoP<double>::INFINITO)
            {   
                costeGlobal += M[i][j];
            }
            
        }
        
        return costeGlobal;
    }
    
}
Puente MontarPuenteOptimo(const GrafoP<double>& G1, const GrafoP<double>& G2, vector<vertice> Costeras1,vector<vertice> Costeras2)
{
    size_t n1 = G1.numVert();
    size_t n2 = G2.numVert();
    GrafoP<double> G(n1 + n2);
    vector<bool> esCostera(n1 + n2,false);
    matriz<double> mat;
    matriz<vertice> r;
    for (size_t i = 0; i < Costeras1.size(); i++)
    {
        esCostera[Costeras1[i]] = true;
    }

    for (size_t i = 0; i < Costeras2.size(); i++)
    {
        esCostera[Costeras2[i] + n1] = true;
    }

    //Construimos el nuevo grafo

    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < n1; j++)
        {
            G[i][j] = G1[i][j];
        }
    }
    
    for (size_t i = n1; i < n1+n2; i++)
    {
        for (size_t j = n1; j < n1+n2; j++)
        {
            G[i][j] = G[i%n2][j%n2];
            G[j][i] = G[i%n2][j%n2];
        }
        
    }
    
    //Probamos puentes
    double minimo = GrafoP<double>::INFINITO;
    double coste = 0;
    Puente P(0,0); //Puente por defecto
    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = n1; j < n1+n2; j++)
        {
            G[i][j] = 0;
            mat = Floyd(G,r);
            coste = costeGlobal(mat);
            if (coste < minimo)
            {
                minimo = coste;
                P.c1 = i;
                P.c2 = j%n2;
            }
            G[i][j] = GrafoP<double>::INFINITO;
        }
    }

    return P;
    
}

