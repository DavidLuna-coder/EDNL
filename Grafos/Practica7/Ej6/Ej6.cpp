#include "../../MaterialesGrafos/grafoPMC.h"
#include "../../MaterialesGrafos/matriz.h"
#include "../../Floyd.hpp"
#include <iostream>
#include <algorithm>
matriz<double> TarifaMinima(const GrafoP<double> &Bus, const GrafoP<double> &Tren, size_t ciudad)
{
    GrafoP<double> G(Bus.numVert() + Tren.numVert());

    for (auto i = 0; i < Bus.numVert(); i++)
    {
        for (auto j = 0; j < Bus.numVert(); j++)
        {
            G[i][j] = Bus[i][j];
        }
    }

    for (auto i = Bus.numVert(); i < Bus.numVert() + Tren.numVert(); i++)
    {
        for (auto j = Bus.numVert(); j < Bus.numVert() + Tren.numVert(); j++)
        {
            G[i][j] = Tren[i % Tren.numVert()][j % Tren.numVert()];
        }
    }

    for (auto i = 0; i < Bus.numVert(); i++)
    {
        for (auto j = Bus.numVert(); j < Bus.numVert() + Tren.numVert(); j++)
        {
            if (i == j % Tren.numVert() && i == ciudad)
            {
                G[i][j] = 0;
                G[j][i] = 0;
            }

            else
            {
                G[i][j] = GrafoP<double>::INFINITO;
                G[j][i] = GrafoP<double>::INFINITO;
            }
        }
    }

    std::cout << G << "\n";
    matriz<size_t> P;
    matriz<double> tarifa = Floyd(G, P);
    matriz<double> mat(Bus.numVert());
    for (size_t i = 0; i < mat.dimension(); i++)
    {
        for (size_t j = 0; j < mat.dimension(); j++)
        {
            mat[i][j] = std::min(tarifa[i][j], tarifa[i+Bus.numVert()][j+Bus.numVert()]);
        }
        
    }
    
    return mat;
}

int main()
{
    srand(time(NULL));
    GrafoP<double> G1(3), G2(3);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == j)
                G1[i][j] = 0;
            else
                G1[i][j] = rand() % 100 + 1;
        }
    }

    std::cout << "---------------------------\n";

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == j)
                G2[i][j] = 0;
            else
                G2[i][j] = rand() % 100 + 1;
        }
    }
    std::cout << "\n";
    std::cout << "\n";

    auto mat = TarifaMinima(G1, G2, 5);
    std::cout<< "MATRIZ:\n";
    for (size_t i = 0; i < mat.dimension(); i++)
    {
        for (size_t j = 0; j < mat.dimension(); j++)
        {
            std::cout << mat[i][j] << "\t";
        }

        std::cout << "\n";
    }

    return 0;
}