#include "../MaterialesGrafos/alg_grafoPMC.h"
#include <cmath>
struct ciudad
{
    double x;
    double y;
    ciudad(double x, double y) : x(x), y(y) {}
};
bool operator==(ciudad c1, ciudad c2)
{
    return c1.x == c2.x && c1.y == c2.y;
}

struct Puente
{
    ciudad c1;
    ciudad c2;
    double coste;
    Puente(ciudad c1, ciudad c2, double coste) : c1(c1), c2(c2), coste(coste) {}
};
struct Carretera
{
    ciudad c1;
    ciudad c2;
    double coste;
    Carretera(ciudad c1, ciudad c2, double coste) : c1(c1), c2(c2), coste(coste) {}
};
bool operator==(Carretera ct1, Carretera ct2) { return ct1.c1 == ct2.c1 && ct2.c2 == ct1.c2; }

bool operator==(Puente p1, Puente p2){return p1.c1 == p2.c1 && p1.c2 == p2.c2;};

using namespace std;

double distancia(ciudad c1, ciudad c2) {return (sqrt(pow(c1.x - c2.x, 2) + pow((c2.y - c1.y), 2))); }
vector<Puente> COMUNICA(vector<ciudad> cFobos, vector<ciudad> cDeimos, vector<ciudad> cEuropa, double costeC, double costeP, double costeAdicionalC, double costeAdicionalP, vector<Carretera> &carreteras)
{
    typedef typename GrafoP<double>::vertice vertice;
    const double INFINITO = GrafoP<double>::INFINITO;
    size_t nFobos = cFobos.size();
    size_t nDeimos = cDeimos.size();
    size_t nEuropa = cEuropa.size();

    // Creamos un Grecoland
    GrafoP<double> Grecoland(nFobos + nDeimos + nEuropa);

    // Rellenar carreteras de FOBOS;
    for (vertice i = 0; i < nFobos; i++)
    {
        for (vertice j = i; j < nFobos; j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = costeC + costeAdicionalC * distancia(cFobos[i], cFobos[j]);
        }
    }

    for (vertice i = nFobos; i < nFobos + nDeimos; i++)
    {
        for (vertice j = i; j < nDeimos; j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = costeC + costeAdicionalC * distancia(cDeimos[i - nFobos], cDeimos[j - nFobos]);
        }
    }

    for (vertice i = nDeimos; i < nDeimos + nEuropa; i++)
    {
        for (vertice j = i; j < nEuropa; j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = costeC + costeAdicionalC * distancia(cDeimos[i - (nFobos+nDeimos)], cDeimos[j - (nFobos+nDeimos)]);
        }
    }

    // Carreteras Construidas, ahora toca puentes;
    // Fobos-Deimos
    for (vertice i = 0; i < nFobos; i++)
    {
        for (vertice j = nFobos; j < nFobos + nDeimos; j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = costeP + costeAdicionalP * distancia(cFobos[i], cDeimos[j - nFobos]);
        }
    }

    // Fobos Europa
    for (vertice i = 0; i < nFobos; i++)
    {
        for (vertice j = nFobos + nDeimos; j < nFobos + nDeimos + nEuropa; j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = costeP + costeAdicionalP * distancia(cFobos[i], cEuropa[j - nFobos - nDeimos]);
        }
    }

    // Deimos - Europa

    for (vertice i = nFobos; i < nDeimos; i++)
    {
        for (vertice j = i + nDeimos; j < nFobos + nDeimos + nEuropa; j++)
        {
            Grecoland[i][j] = Grecoland[j][i] = costeP + costeAdicionalP * distancia(cDeimos[i - nFobos], cEuropa[j - nFobos - nDeimos]);
        }
    }

    GrafoP<double> GrecolandComunicado = Kruskall(Grecoland);
    // Buscar Carreteras
    for (vertice i = 0; i < nFobos; i++)
    {
        for (vertice j = i; j < nFobos; j++)
        {
            if (GrecolandComunicado[i][j] != INFINITO)
            {
                carreteras.push_back(Carretera(cFobos[i], cFobos[j], GrecolandComunicado[i][j]));
            }
        }
    }

    for (vertice i = nFobos; i < nFobos + nDeimos; i++)
    {
        for (vertice j = i; j < nFobos + nDeimos; j++)
        {
            if (GrecolandComunicado[i][j] != INFINITO)
            {
                carreteras.push_back(Carretera(cDeimos[i], cDeimos[j], GrecolandComunicado[i][j]));
            }
        }
    }

    for (vertice i = nFobos + nDeimos; i < nFobos + nDeimos + nEuropa; i++)
    {
        for (vertice j = i; j < nFobos + nDeimos + nEuropa; j++)
        {
            if (GrecolandComunicado[i][j] != INFINITO)
            {
                carreteras.push_back(Carretera(cEuropa[i], cEuropa[j], GrecolandComunicado[i][j]));
            }
        }
    }
}
