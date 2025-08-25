#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa verifica si una gr�fica tiene paseo euleriano cerrado, abierto o no lo tiene.

Para esto se calcula el grado de cada v�rtice a partir de su matriz de adyacencia y se cuenta cu�ntos v�rtices tienen grado impar.
Si todos los v�rtices tienen grado par, la gr�fica tiene un paseo euleriano cerrado.
Si exactamente dos v�rtices tienen grado impar, la gr�fica tiene un paseo euleriano abierto.
Si m�s de dos v�rtices tienen grado impar, la gr�fica no tiene un paseo euleriano.

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

    cout<<"Ingrese el orden de la gr�fica: ";
    cin>>orden;

    if (orden <= 0) {
        cout<<"Orden inv�lido. Debe ser mayor que 0.\n";
        return 1;
    }

    cout<<"\nIngrese el tama�o de la gr�fica: ";
    cin>>tamano;

    if (tamano < 0 || tamano > orden*(orden - 1)/2) {
        cout<<"tama�o inv�lido para una gr�fica simple.\n";
        return 1;
    }

    vector<vector<int>> M(orden+1, vector<int>(orden+1, 0));
    vector<int> Grados(orden+1);

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    cout<<endl<<"Los grados de cada v�rtice son: "<<endl;

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
        cout<<endl<<"La gr�fica tiene un paseo euleriano cerrado."<<endl;
    else if(j == 2)
        cout<<endl<<"La gr�fica no tiene un paseo euleriano cerrado pero s� uno abierto."<<endl;
    else
        cout<<endl<<"La gr�fica no tiene alg�n paseo euleriano."<<endl;

    return 0;
}

// Funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(int tamano, vector<vector<int>>& M)
{
    char v1, v2;
    for (int i = 1; i <= tamano; i++) {
        cout<<"\nInserte los v�rtices de la "<<i<<"� arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()) {
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"V�rtices fuera de rango. Int�ntelo nuevamente.\n";
            i--;
        }
    }
}

// Funci�n para imprimir la matriz de adyacencia
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
