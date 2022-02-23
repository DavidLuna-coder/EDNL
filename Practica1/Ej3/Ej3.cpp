#include "Abin_Enlazada.h"
#include "abin_E-S.h"
#include "Ej3.hpp"

const char fin = '-';
int main()
{
    int profundidad;
    Abin<char> a;
    rellenarAbin(a,fin);
    imprimirAbin(a);
    std::cout <<"Profundidad: " << Profundidad(a,a.hijoIzqdo(a.raiz()))<<std::endl;
    return 0;
}