#include "../MaterialesGrafos/grafoPMC.h"
#include <cmath>
#include "../Kruskal.hpp"
#include "../Dijkstra.hpp"
using vertice = typename GrafoP<double>::vertice;
using namespace std;
struct ciudad
{
    double x;
    double y;
    explicit ciudad(double x = double(), double y = double()) : x(x), y(y){};
};
bool operator==(ciudad c1, ciudad c2) { return c1.x == c2.x && c2.y == c1.y; }
struct Puente
{
    vertice c1;
    vertice c2;
    explicit Puente(vertice c1 = 0, vertice c2 = 0) : c1(c1), c2(c2){};
};
double distanciaEuclidea(ciudad c1, ciudad c2)
{
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

vertice ciudadToVertice(ciudad c1, vector<ciudad> Fobos, vector<ciudad> Deimos)
{

    for (size_t i = 0; i < Fobos.size(); i++)
    {
        if (Fobos[i] == c1)
        {
            return i;
        }
    }

    for (size_t i = 0; i < Deimos.size(); i++)
    {
        if (Deimos[i] == c1)
        {
            return i + Fobos.size();
        }
    }
}
double CosteGrecoland(vector<ciudad> CiudadesFobos, vector<ciudad> CiudadesDeimos, vector<ciudad> CosterasFobos, vector<ciudad> CosterasDeimos, ciudad origen, ciudad destino)
{
    GrafoP<double> Fobos(CiudadesFobos.size());
    GrafoP<double> Deimos(CiudadesDeimos.size());
    // Completamos Fobos
    for (size_t i = 0; i < Fobos.numVert(); i++)
    {
        for (size_t j = i; j < Fobos.numVert(); j++)
        {
            Fobos[i][j] = Fobos[j][i] = distanciaEuclidea(CiudadesFobos[i], CiudadesFobos[j]);
        }
    }

    // Rellenamos Deimos
    for (size_t i = 0; i < Deimos.numVert(); i++)
    {
        for (size_t j = i; j < Deimos.numVert(); j++)
        {
            Deimos[i][j] = Deimos[j][i] = distanciaEuclidea(CiudadesDeimos[i], CiudadesDeimos[j]);
        }
    }
    // Construimos las carrecteras de coste minimo para unir todo Fobos y Deimos
    Fobos = Kruskal(Fobos);
    Deimos = Kruskal(Deimos);

    Puente P;
    // Decidimos que puente construir
    double min = GrafoP<double>::INFINITO;
    for (size_t i = 0; i < CosterasFobos.size(); i++)
    {
        for (size_t j = 0; j < CosterasDeimos.size(); j++)
        {
            double distancia = distanciaEuclidea(CosterasFobos[i], CosterasDeimos[j]);
            if (distancia < min)
            {
                P = Puente(i, j);
                min = distancia;
            }
        }
    } // Puente mas corto

    // Creamos el Grafo Grande

    GrafoP<double> Grecoland(Fobos.numVert() + Deimos.numVert());

    // Copiamos Fobos
    for (vertice i = 0; i < Fobos.numVert(); i++)
    {
        for (vertice j = i; j < Fobos.numVert(); j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = Fobos[i][j];
        }
    }

    // Copiamos Deimos
    for (vertice i = Fobos.numVert(); i < Deimos.numVert(); i++)
    {
        for (vertice j = i; j < Deimos.numVert(); j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = Deimos[i % Deimos.numVert()][j % Deimos.numVert()];
        }
    }

    // Establecemos el puente
    Grecoland[P.c1][P.c2 + Fobos.numVert()] = Grecoland[P.c2 + Fobos.numVert()][P.c1] = min;

    vector<vertice> t;
    vertice org = ciudadToVertice(origen,CiudadesFobos,CiudadesDeimos);
    vector<double> costesMinimos = Dijkstra(Grecoland,org,t);
    vertice dest = ciudadToVertice(destino,CiudadesFobos,CiudadesDeimos);

    return costesMinimos[dest];
}