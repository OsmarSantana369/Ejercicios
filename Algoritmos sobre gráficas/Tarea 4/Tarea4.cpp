#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa verifica si una gr·fica dada es completa a partir de su matriz de adyacencia.

Para esto se verifica si el *tamano* de la gr·fica ingresada es igual a la mitad del producto del *orden* por este mismo disminuido en 1.
Si lo es, se muestra un mensaje de que la gr·fica es completa, en caso contrario el mensaje dir· que no lo es y se imprimir·n las aristas que faltan para que lo sea.

Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
void EsCompleta(int orden, int tamano, vector<vector<int>>& M);

int main()
{
    setlocale(LC_ALL, "");
    int orden, tamano;

    cout<<"Ingrese el orden de la gr·fica: ";
    cin>>orden;

    if (orden <= 0) {
        cout<<"Orden inv·lido. Debe ser mayor que 0.\n";
        return 1;
    }

    cout<<"\nIngrese el tamaÒo de la gr·fica: ";
    cin>>tamano;

    if (tamano < 0 || tamano > orden*(orden - 1)/2) {
        cout<<"TamaÒo inv·lido para una gr·fica simple.\n";
        return 1;
    }

    vector<vector<int>> M(orden+1, vector<int>(orden+1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    EsCompleta(orden, tamano, M);

    return 0;
}

// Funci√≥n para ingresar las adyacencias de la gr·fica
void IngresaAristas(int tamano, vector<vector<int>>& M)
{
    char v1, v2;
    for (int i = 1; i <= tamano; i++) {
        cout<<"\nInserte los vÈrtices de la "<<i<<"∞ arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()) {
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"VÈrtices fuera de rango. IntÈntelo nuevamente.\n";
            i--;
        }
    }
}

// Funci√≥n para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<int>>& M)
{
    cout<<"\n ";
    for (int i = 1; i <= orden; i++) {
        cout<<"   "<<char(96 + i);
    }

    for (int i = 1; i <= orden; i++) {
        cout<<"\n"<<char(96 + i)<<"   ";
        for (int j = 1; j <= orden; j++) {
            cout<<M[i][j]<<"   ";
        }
    }
    cout<<endl;
}

// Funci√≥n para ver si la gr·fica es completa
void EsCompleta(int orden, int tamano, vector<vector<int>>& M)
{
    if(tamano == orden*(orden-1)/2)
        cout<<endl<<"La gr·fica es completa"<<endl;
    else{
        cout<<endl<<"La gr·fica no es completa"<<endl<<endl;
        cout<<"Las aristas que faltan son:"<<endl;

        for (int i = 1; i <= orden; i++) {
            for (int j = i+1; j <= orden; j++) {
                if(M[i][j] == 0)
                    cout<<char(i+96)<<char(j+96)<<endl;
            }
        }
    }
}


