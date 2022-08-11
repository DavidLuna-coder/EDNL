#include "../MaterialesGrafos/alg_grafoPMC.h"
#include <cmath>
#include <iostream>
typedef typename GrafoP<size_t>::vertice nodo;
using namespace std;
struct casilla
{
    int x;
    int y;
};

nodo casillaToNodo(casilla c1, size_t tam)
{
    return (c1.x * tam + c1.y);
}

casilla nodoToCasilla(nodo v, size_t tam)
{
    casilla c;
    c.x = v / tam;
    c.y = v % tam;
    return c;
}

size_t movimientosCaballo(casilla origen, casilla destino)
{
    GrafoP<int> nodos(8 * 8);

    for (size_t i = 0; i < 64; i++)
    {
        casilla c1 = nodoToCasilla(i, 8);
        for (size_t j = i; j < 64; j++)
        {
            casilla c2 = nodoToCasilla(j, 8);
            if (c1.x != c2.x && c1.y != c2.y)
            {
                if (abs(c1.x - c2.x) + abs(c1.y - c2.y) == 3)
                {
                    nodos[j][i] = nodos[i][j] = 1;
                }
            }
        }
    }

    vector<nodo> P;
    vector<int> Movimientos = Dijkstra(nodos,casillaToNodo(origen,8),P);
    return Movimientos[casillaToNodo(destino,8)];
}


int main()
{
    casilla origen;
    origen.x = 1;
    origen.y = 1;

    casilla destino;
    destino.x = 1;
    destino.y = 7;

    std::cout << movimientosCaballo(origen,destino);
}