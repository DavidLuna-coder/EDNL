#include "../../Floyd.hpp"
#include "../../MaterialesGrafos/alg_grafo_E-S.h"
#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../MaterialesGrafos/listaenla.h"
#include <iostream>
#include <algorithm>
#include <time.h>

using tCoste = size_t;
using vertice = typename GrafoP<tCoste>::vertice;

struct vertOrigen
{
    vertOrigen(vertice v = 0,vertice o = 0):v(v),origen(o){}
    vertice v;
    vertice origen;
};


bool esAciclicoRec(Lista<vertOrigen>& Lv,vertOrigen arista,const GrafoP<tCoste>& G,std::vector<bool> recorrido)
{
    std::vector<tCoste> costes = G[arista.v];

    

        Lv.eliminar(Lv.primera());
        recorrido[arista.v] = true; // Marcamos como visitado
        for (size_t i = 0; i < G.numVert(); i++)
        {
            if (arista.origen!=i && costes[i] != GrafoP<tCoste>::INFINITO)
            {
                if (recorrido[i] == false )
                {
                    Lv.insertar(vertOrigen(i,arista.v),Lv.primera());
                }
                else
                    return false;

            }
            
        }
        if (Lv.primera()!=Lv.fin())
        {
            return esAciclicoRec(Lv,Lv.elemento(Lv.primera()),G,recorrido);
        }
        else
            return true;
        
    
    //if(!recorrido[v]){
    /*for (vertice i = 0; i < G.numVert(); i++)
    {
            if (i!=v && i!= origen && vertices[i] != GrafoP<tCoste>::INFINITO)
            {
                if (Lv.buscar(i)!=Lv.fin())
                {
                    return false;
                }
                else
                {
                    Lv.insertar(i,Lv.primera());
                    recorrido[v] = true;
                }
            }
    }
    }
    if(Lv.primera() == Lv.fin())
    {
        return true;
    }
    else*/
}


bool esAciclico(const GrafoP<tCoste>& G)
{
    Lista<vertOrigen> Lv;
    std::vector<bool> recorrido(G.numVert(),false);
    vertice v = 0;
    std::vector<tCoste> adyacentes = G[v];
    recorrido[v] = true;
    for (size_t i = 0; i < G.numVert(); i++)
    {
        if (adyacentes[i] != GrafoP<tCoste>::INFINITO)
        {
            Lv.insertar(vertOrigen(i,v),Lv.primera());
        }
        
    }
    if (Lv.primera()==Lv.fin())
    {
        return true;
    }
    
    return esAciclicoRec(Lv,Lv.elemento(Lv.primera()),G,recorrido);
    
    
}
int main()
{
    srand(time(NULL));
    size_t n = 4;
    GrafoP<size_t> G(n);
    size_t INFINITO = 4294967295;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout<<"Introduce la arista: " << i << " " << j << std::endl;
            std::cin >> G[i][j];
            if(G[i][j] == 0)
            {
                G[i][j] = GrafoP<tCoste>::INFINITO; 
            }
            G[j][i] = G[i][j];
        }
    }

    std::cout<< G << std::endl;
    std::cout<<esAciclico(G);

}