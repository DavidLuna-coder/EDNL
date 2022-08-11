#include "../MaterialesGrafos/grafoPMC.h"
#include "../Floyd.hpp"
#include <cmath>
#include "../Kruskal.hpp"
#include "../MaterialesGrafos/apo.h"
using namespace std;

struct ciudad
{
    double x;
    double y;
    ciudad(double x = -1, double y = -1) : x(x), y(y){}; // Ciudad invalida
};
bool operator == (ciudad c1, ciudad c2){return (c1.x == c2.x && c1.y == c2.y);}
struct LineaAerea
{
    ciudad c1;
    ciudad c2;
    double coste;
    LineaAerea(ciudad c1 = ciudad(), ciudad c2 = ciudad()) : c1(c1), c2(c2), coste(sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2))){};
};

bool operator < (const LineaAerea& a1, const LineaAerea& a2){return a1.coste < a2.coste; }


using vertice = typename GrafoP<double> ::vertice;
vertice BuscarCiudad(ciudad c, vector<ciudad> ciudades)
{
    bool encontrado = false;
    size_t i;
    for ( i = 0; i < ciudades.size() && !encontrado; i++)
    {
        if (c == ciudades[i])
        {
            encontrado = true;
        }
        
    }
    return i-1;
}
vector<LineaAerea> Tombuctú2(Grafo GA, vector<ciudad> ciudades)
{
    auto INFINITO = GrafoP<double>::INFINITO;
    using vertice = typename GrafoP<double> ::vertice;
    size_t n_ciudades = GA.numVert();
    GrafoP<double> G(n_ciudades); // Grafo de n ciudades;
    for(vertice i = 0; i < n_ciudades; i++)
    {
        for (size_t j = i; j < n_ciudades; j++)
        {
            if(GA[i][j])
            {
                G[i][j] = sqrt(pow(ciudades[i].x - ciudades[j].x, 2) + pow(ciudades[i].y - ciudades[j].y, 2));
            }

            if (G[j][i])
            {
                G[j][i] = sqrt(pow(ciudades[i].x - ciudades[j].x, 2) + pow(ciudades[i].y - ciudades[j].y, 2));
            }
            
        }
    }

    matriz<vertice> t;
    matriz<double> mCostes = Floyd(G,t);//conectar todas las ciudades posibles;

    size_t n_islas = n_ciudades;
    Particion Islas(n_ciudades);//Máximos de islas tantas como ciudades

    for (size_t i = 0; i < n_ciudades; i++)
    {
        for(size_t j = 0; j < n_ciudades; j++)
        {
            if ((mCostes[i][j] != INFINITO || mCostes[j][i] != INFINITO) && Islas.encontrar(i) != Islas.encontrar(j))
            {
                Islas.unir(i,j);
                n_islas--;
            }    
        }
    }
    // Ya tenemos el numero de islas
    Apo<LineaAerea> apoLineas (n_ciudades * (n_ciudades- 1)/2);

    for (size_t i = 0; i < n_ciudades; i++)
    {
        for(size_t j = i; j < n_ciudades; j++)
        {
            if (Islas.encontrar(i) != Islas.encontrar(j))
            {
                apoLineas.insertar(LineaAerea(ciudades[i],ciudades[j]));
            }
        }
    }

    Grafo IslaConectada(n_islas);
    vector <LineaAerea> Lineas (n_islas * (n_islas -1) / 2);
    size_t i = 0;
    while (i < n_islas * (n_islas -1) / 2)
    {
        LineaAerea a = apoLineas.cima();
        apoLineas.suprimir();
        vertice v = BuscarCiudad(a.c1,ciudades) % n_islas;
        vertice w = BuscarCiudad(a.c2,ciudades) % n_islas;
        if (!IslaConectada[v][w])
        {
            IslaConectada[w][v] = true;
            Lineas[i] = a;
            i++;
        }
    }
    
    return Lineas;
}
