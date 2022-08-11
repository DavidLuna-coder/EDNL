#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../MaterialesGrafos/matriz.h"
#include "../../Dijkstra.hpp"
#include <iostream>
#include <algorithm>

//? OPCIONES
//* Bus - Cambio1 - Tren
//* Bus - Cambio2 - Tren
using vertice = typename GrafoP<double>::vertice;
using namespace std;

Lista<vertice> RutaMasCorta(const GrafoP<double> &BUS, const GrafoP<double> &TREN, vertice origen, vertice destino, vertice cambio1, vertice cambio2, double &coste_total)
{
    vector<vertice> P1;
    vector<double> CostesTren = Dijkstra(TREN, origen, P1);
    double Tren_Cambio1 = CostesTren[cambio1];
    double Tren_Cambio2 = CostesTren[cambio2];

    vector<vertice> P2;
    vector<double> CostesBus = DijkstraInverso(BUS, destino, P2);

    double Bus_Cambio1 = CostesBus[cambio1];
    double Bus_Cambio2 = CostesBus[cambio2];
    vertice cambio = cambio1;
    coste_total = Tren_Cambio1 + Bus_Cambio1;
    if (Tren_Cambio2 + Bus_Cambio2 < Tren_Cambio1 + Bus_Cambio1)
    {
        cambio = cambio2;
        coste_total = Tren_Cambio2 + Bus_Cambio2;
    }

    // Montamos la ruta
    Lista<vertice> Ruta;
    vertice i = cambio;
    Ruta.insertar(cambio, Ruta.primera());
    while (i != origen)
    {
        Ruta.insertar(P1[i], Ruta.primera());
        i = P1[i];
    }

    i = cambio;
    while (i != destino)
    {
        Ruta.insertar(P2[i], Ruta.fin());
        i = P2[i];
    }

    return Ruta;
}
