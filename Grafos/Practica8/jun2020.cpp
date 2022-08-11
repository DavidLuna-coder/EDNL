#include "../MaterialesGrafos/alg_grafoPMC.h"

typedef typename GrafoP<double>::vertice cliente;
using namespace std;
size_t Pedido(cliente c);
cliente Minimo(vector<double>, vector<size_t>, cliente);
bool seguirRepartiendo(vector<size_t> Pedidos);

double CosteReparto(GrafoP<double> G, size_t capacidad, cliente origen)
{
    size_t n = G.numVert();
    vector<size_t> PedidosRestantes(n);
    size_t carga = capacidad;
    for (cliente i = 0; i < n; i++)
    {
        PedidosRestantes[i] = Pedido(i);
    }

    matriz<cliente> MC(n);
    matriz<double> CostesMinimos = Floyd(G, MC);

    double costeTotal = 0;
    PedidosRestantes[origen] = 0;
    cliente v = origen;
    bool continua = true;

    while (continua == true)
    {
        cliente w = Minimo(CostesMinimos[v], PedidosRestantes, v); // NUNCA SERA V;
        costeTotal += CostesMinimos[v][w];

        if (carga <= PedidosRestantes[w])
        {
            PedidosRestantes[w] -= carga;
            carga = 0;
            carga = capacidad;
            costeTotal += CostesMinimos[w][origen];
            v = origen;
        }

        else
        {
            carga -= PedidosRestantes[w];
            PedidosRestantes[w] = 0;
            v = w;
        }

        if (PedidosRestantes[w] == 0)
        {
            continua = seguirRepartiendo(PedidosRestantes); // Devuelve verdadero si faltan pedidos por repartir


        }
    }
    costeTotal += CostesMinimos[v][origen];

    return costeTotal;

}