#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa verifica si una gráfica tiene paseo euleriano cerrado, abierto o no lo tiene.

Para esto se calcula el grado de cada vértice a partir de su matriz de adyacencia y se cuenta cuántos vértices tienen grado impar.
Si todos los vértices tienen grado par, la gráfica tiene un paseo euleriano cerrado.
Si exactamente dos vértices tienen grado impar, la gráfica tiene un paseo euleriano abierto.
Si más de dos vértices tienen grado impar, la gráfica no tiene un paseo euleriano.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);

char letra;
bool euleriana = true, eulerianaAbierta = true;

int main()
{
    setlocale(LC_ALL, "");
    int orden, tamano, i, j;

    cout<<"Ingrese el orden de la gráfica: ";
    cin>>orden;

    if (orden <= 0) {
        cout<<"Orden inválido. Debe ser mayor que 0.\n";
        return 1;
    }

    cout<<"\nIngrese el tamaño de la gráfica: ";
    cin>>tamano;

    if (tamano < 0 || tamano > orden*(orden - 1)/2) {
        cout<<"tamaño inválido para una gráfica simple.\n";
        return 1;
    }

    vector<vector<int>> M(orden+1, vector<int>(orden+1, 0));
    vector<int> Grados(orden+1);

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    cout<<endl<<"Los grados de cada vértice son: "<<endl;

    for(i = 1; i <= orden; i++){
        Grados[i] = 0;

        for(j = 1; j <= orden; j++)
            Grados[i] = Grados[i] + M[i][j];
    }

    letra = 'a';

    for(i = 1; i <= orden; i++){
        cout<<"gr("<<char(i+96)<<") = "<<Grados[i]<<endl;
        letra++;
    }

    j = 0;

    for(i = 1; i <= orden; i++){
        if(Grados[i]%2 == 1){
            j++;
            euleriana = false;
        }
    }

    if(euleriana)
        cout<<endl<<"La gráfica tiene un paseo euleriano cerrado."<<endl;
    else if(j == 2)
        cout<<endl<<"La gráfica no tiene un paseo euleriano cerrado pero sí uno abierto."<<endl;
    else
        cout<<endl<<"La gráfica no tiene algún paseo euleriano."<<endl;

    return 0;
}

// Función para ingresar las adyacencias de la gráfica
void IngresaAristas(int tamano, vector<vector<int>>& M)
{
    char v1, v2;
    for (int i = 1; i <= tamano; i++) {
        cout<<"\nInserte los vértices de la "<<i<<"° arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()) {
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"Vértices fuera de rango. Inténtelo nuevamente.\n";
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
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
