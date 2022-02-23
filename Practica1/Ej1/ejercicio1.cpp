#include <iostream>
#include "Abin_Enlazada.h"
#include "abin_E-S.h"
#include "ejercicio1.hpp"
using namespace std;
typedef char tElto;
const tElto fin = 'p'; // Fin de lectura.
int main ()
{
Abin<tElto> A, B;
cout << "*** Lectura del árbol binario A ***\n";
rellenarAbin(A, fin); // Desde std::cin
imprimirAbin(A); // En std::cout
int cont;
cout<< "El numero de nodos es: "<< contarNodos(A) << endl;
}