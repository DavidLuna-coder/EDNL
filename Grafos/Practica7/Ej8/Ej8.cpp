#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../MaterialesGrafos/matriz.h"
#include "../../Dijkstra.hpp"
#include <iostream>
#include <algorithm>

typedef typename GrafoP<double>::vertice vertice;
using namespace std;
double TarifaMinima(const GrafoP<double> &Bus, const GrafoP<double> &Tren, vertice origen, vertice destino)
{
    vector<vertice> P;
    vector<double> OBus = Dijkstra(Bus,origen,P); //bus - bus


    vector<double> OTren = Dijkstra(Tren,origen,P); // tren - tren
    vector<double> DBus = DijkstraInverso(Bus,destino,P);
    vector<double> DTren = DijkstraInverso(Bus,destino,P);

    double coste = min(OBus[destino],OTren[destino]);
    for (size_t i = 0; i < Bus.numVert(); i++)
    {   

        auto min1 = min(OBus[i] + DTren[i], OTren[i] + DBus[i]);
        if( i != origen && i!=destino && min(OBus[i] + DTren[i], OTren[i] + DBus[i]) < coste)
        coste = min(OBus[i] + DTren[i], OTren[i] + DBus[i]);
    }

    return coste;
}

int main()
{
    srand(time(NULL));
    size_t n = 5;
    GrafoP<double> G1(n), G2(n);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
                G1[i][j] = 0;
            else
                G1[i][j] = rand() % 100 + 1;
        }
    }
    G1[2][4]=1;
    cout<< G1 <<"\n";
    std::cout << "---------------------------\n";

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
                G2[i][j] = 0;
            else
                G2[i][j] = rand() % 100 + 1;
        }
    }
    G2[4][1]=1;
    std::cout << "\n";
    std::cout << "\n";

    cout << G2 << "\n";
    std::cout << "---------------------------\n";

    cout << TarifaMinima(G1,G2,2,1) << "\n";

    return 0;
}