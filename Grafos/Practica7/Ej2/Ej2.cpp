/*2. Se dispone de un laberinto de NxN casillas del que se conocen las casillas de entrada
y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las
casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
(en caso contrario no sería un verdadero laberinto).
Implementa un subprograma que dados
 N (dimensión del laberinto),
 la lista de paredes del laberinto,
 la casilla de entrada, y
 la casilla de salida,
calcule el camino más corto para ir de la entrada a la salida y su longitud.*/

//* CasillaToNodo: nodo = i * n + j
//* NodoToCasilla: i = nodo/n  j = nodo%n


#include "../../MaterialesGrafos/alg_grafoPMC.h"
#include "../../MaterialesGrafos/listaenla.h"
#include <cmath>
#include <iostream>
//#include "../../Dijkstra.hpp"
using Coste = size_t;
using vertice = typename GrafoP<Coste>::vertice;
struct Casilla
{
    size_t coord_x;
    size_t coord_y;
    explicit Casilla(size_t x = 0, size_t y = 0):coord_x(x),coord_y(y){};
};

struct Pared
{
    Casilla c1;
    Casilla c2;
    Pared(Casilla c1 = Casilla(), Casilla c2 = Casilla()):c1(c1),c2(c2){};
};

bool operator==(Casilla C1,Casilla C2)
{
    if (C1.coord_x == C2.coord_x && C1.coord_y == C2.coord_y)
    {
        return true;
    }
    else
    return false;
}

bool operator==(Pared P1,Pared P2)
{
    if (P1.c1 == P2.c1 && P1.c2 == P2.c2)
    {
        return true;
    }
    else 
    return false;
}
vertice CasillaToVertice(const Casilla& C,size_t n)
{
    vertice v = C.coord_x*n + C.coord_y;
    return v;
}

Casilla VerticeToCasilla(vertice v, size_t n)
{
    return Casilla(v/n,v%n);
}
Coste longitudCaminoCorto(size_t n, const Lista<Pared>& LP, Casilla entrada, Casilla salida, Lista<Casilla>& camino)
{
    GrafoP<Coste> G(n*n);
    size_t tam = G.numVert();
    
    Casilla c1,c2;

    for (size_t i = 0; i < tam; i++)
    {
        c1 = VerticeToCasilla(i,n);
        for (size_t j = i; j < tam; j++)
        {
            c2 = VerticeToCasilla(j,n);
            if (abs((c1.coord_x - c2.coord_x)) == 1 && c1.coord_y - c2.coord_y == 0||(c1.coord_x - c2.coord_x == 0 && abs(c1.coord_y - c2.coord_y) == 1))
            {
                if (LP.buscar(Pared(c1,c2)) == LP.fin())
                {
                    G[i][j] = 1;
                    G[j][i] = 1;
                }
            }
      
        }
    }
    std::vector<vertice> P;
    vertice vert_entrada = CasillaToVertice(entrada,n);
    vertice vert_salida = CasillaToVertice(salida,n);

    Coste CosteCaminoCorto = Dijkstra(G, vert_entrada, P)[vert_salida];

    vertice i = vert_salida;
    Casilla ci;
 
    do
    {
        ci = VerticeToCasilla(i,n);
        camino.insertar(ci,camino.primera());
        i = P[i];
    } while (i != vert_entrada);
    
    camino.insertar(entrada,camino.primera());
 
 //! DEBUGGING
    std::cout << G << std::endl;
    return CosteCaminoCorto;
}

std::ostream& operator << (std::ostream& os,Casilla c)
{
    os << CasillaToVertice(c,4);
    return os;
}

std::ostream& operator << (std::ostream& os, Lista<Casilla> L)
{
    for (auto i = L.primera(); i != L.fin(); i = L.siguiente(i))
    {
        os << "[ " << L.elemento(i) << " ] ";
    }
    os << std::endl;
    return os;
}
int main()
{
    size_t n = 4;
    Lista<Pared> LP;
    LP.insertar(Pared(Casilla(0,0),Casilla(1,0)),LP.primera());
    LP.insertar(Pared(Casilla(0,1),Casilla(1,1)),LP.primera());
    LP.insertar(Pared(Casilla(1,2),Casilla(2,2)),LP.primera());
    LP.insertar(Pared(Casilla(1,1),Casilla(2,1)),LP.primera());



    Casilla entrada(0,0);
    Casilla salida(2,2);
    Lista<Casilla> camino;
    Coste costeCamino = longitudCaminoCorto(n,LP,entrada,salida,camino);

    std::cout << "Coste: " << costeCamino << std::endl;
    std::cout << "Camino: " << camino << std::endl ;
}