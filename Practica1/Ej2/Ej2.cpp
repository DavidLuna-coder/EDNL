#include "Abin_Enlazada.h"
#include "abin_E-S.h"
#include "Ej2.hpp"
using namespace std;
int main()
{
    Abin<char> A;
    rellenarAbin(A,'p');
    cout << "La altura del Arbol es " << Altura(A) << endl;

    return 0;
}