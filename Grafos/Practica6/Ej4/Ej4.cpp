/*4. Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre
dos ciudades cualesquiera de un país llamado Zuelandia. El problema es sencillo pero
hay que tener en cuenta unos pequeños detalles:
a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas
y por tanto solo permiten un sentido de la circulación.
b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de
ciudades del país que han sido tomadas por los rebeldes, por lo que no pueden
ser usadas para viajar.
c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que
también han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser
usadas).
d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido
que absolutamente todos los viajes que se hagan por el país pasen por la capital
del mismo, donde se harán los controles de seguridad pertinentes.
Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
• el grafo (matriz de costes) de Zuelandia en situación normal,
• la relación de las ciudades tomadas por los rebeldes,
• la relación de las carreteras cortadas por los rebeldes
• y la capital de Zuelandia,
calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades
zuelandesas en esta situación*/

#include "../../MaterialesGrafos/grafoPMC.h"
#include <iostream>
#include "../../MaterialesGrafos/alg_grafo_E-S.h"
#include "../../MaterialesGrafos/matriz.h"
#include "../../Dijkstra.hpp"

using tCoste = size_t;
using std::vector;

matriz<tCoste> Zuelandia(GrafoP<tCoste>& G,const vector<GrafoP<tCoste>::vertice>& ciudadesRebeldes, const vector<GrafoP<tCoste>::arista>& carreterasRebeldes, GrafoP<tCoste>::vertice capital)
{
    using vertice = typename GrafoP<tCoste>::vertice;
    using arista = GrafoP<tCoste>::arista;
    GrafoP<tCoste> GrafoRebelde(G.numVert());
    GrafoRebelde = G;
    const tCoste& INFINITO = GrafoP<tCoste>::INFINITO;
    //* Modificamos el grafo rebelde con las condiciones
    for (size_t i = 0; i < ciudadesRebeldes.size(); i++)
    {
        for (size_t j = 0; j < G.numVert(); j++)
        {
            GrafoRebelde[ciudadesRebeldes[i]][j] = GrafoP<tCoste>::INFINITO; //* Las carreteras que pasen por ciudades rebeldes se establece como coste INFINITO
            GrafoRebelde[j][ciudadesRebeldes[i]] = GrafoP<tCoste>::INFINITO;
        }
    }

    //* Modificamos el Grafo Rebelde teniendo en cuenta las listas de carreteras tomadas por los rebeldes.
    for (size_t i = 0; i < carreterasRebeldes.size(); i++)
    {
        GrafoRebelde[carreterasRebeldes[i].orig][carreterasRebeldes[i].dest] = INFINITO; //* Establecemos estas aristas a Infinito
    }


    
    //* Tendríamos el Grafo Rebelde construido. Como tiene que pasar por la capital lo que debemos mirar es cuanto cuesta llegar desde todas las ciudades hasta la capital, aplicamos dijkstra inverso.

    vector<vertice> P;
    vector<tCoste> costeACapital = DijkstraInverso(GrafoRebelde,capital, P);


    //*[[23][32][32][1][3]] Vector de distancias hasta la capital. Ver cuanto cuesta ir desde la capital hasta cualquier otro sitio

    //* Dijkstra normal tomando como origen la capital.
    vector<tCoste> costeDesdeCapital = Dijkstra(GrafoRebelde,capital,P);
    //* Vector de costes desde la capital hasta cualquier ciudad.

    //* Modificamos el grafo Rebelde con los costes de ir a capital y a destino.

    for (size_t i = 0; i < GrafoRebelde.numVert(); i++)
    {
        for (size_t j = 0; j < GrafoRebelde.numVert(); j++)
        {
            if(costeACapital[i]==INFINITO || costeDesdeCapital[j] == INFINITO || i == j)
            GrafoRebelde[i][j] = INFINITO;
            else
            GrafoRebelde[i][j] = costeACapital[i] + costeDesdeCapital[j];
        }
    }

    //!
    std::cout<<GrafoRebelde<<std::endl; 
    //* Con esto tenemos ya el Grafo con costes Minimos Haria falta transformarlo en matriz.
    matriz<tCoste> CostesMinimos(GrafoRebelde.numVert());
    for (size_t i = 0; i < GrafoRebelde.numVert(); i++)
    {
        for (size_t j = 0; j < GrafoRebelde.numVert(); j++)
        {
            CostesMinimos[i][j] = GrafoRebelde[i][j];
        }
        
    }
    
    return CostesMinimos;
}


int main()
{
    srand(time(NULL));
    using vertice = typename GrafoP<tCoste>::vertice;
    using arista = GrafoP<tCoste>::arista;
    const tCoste& INFINITO = GrafoP<tCoste>::INFINITO;
    size_t n = 7;
    GrafoP<tCoste> G(n);
    for(vertice v = 0; v < G.numVert(); v++)
    {
        for (vertice w = 0; w < G.numVert(); w++)
        {
            if(v == w)
            {
                G[v][w] = INFINITO;
            }
            else
            {
                tCoste x = rand()%100;
                if (!x%5)
                {
                    G[v][w] = INFINITO;
                }
                else
                G[v][w] = x;
            }
        }
        
    }
    std::cout << G << std::endl;

    //* Lista de ciudades rebeldes
    vector<vertice> cr;
    cr = {3};

    std::cout<< cr << std::endl;
    arista a(0,2);
    arista b(2,1);
    arista c(4,6);

    vector<arista> ar = {a,b,c};

    vertice capital = 6;

    matriz <tCoste> Prueba = Zuelandia(G,cr,ar,6);
    //std::cout << Prueba << std::endl;
}
