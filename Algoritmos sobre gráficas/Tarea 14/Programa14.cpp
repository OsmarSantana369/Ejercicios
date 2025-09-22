#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra las distancia de peso m�nimo que hay de un v�rtice a otros (Algoritmo de Dijkstra).



Orden del algoritmo: O(potencia*orden^3 + tamano*NumCompCon)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
void ObtenerDistancias(vector<vector<float>>& M, vector<vector<float>>& MDistPesos);

int orden, tamano, infinito = INT_MAX;
bool Reiniciar;

int main()
{
    setlocale(LC_ALL, "");

    do{
        cout << "Ingrese el orden de la gr�fica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inv�lido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tama�o de la gr�fica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tama�o inv�lido para una gr�fica simple." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    vector<vector<float>> M(orden + 1, vector<float>(orden + 1, 0));
    vector<vector<float>> MDistPesos(orden + 1, vector<float>(orden + 1, infinito));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);
    ObtenerDistancias(M, MDistPesos);

    cout << endl << "Las distancias de peso m�nimo entre los v�rtices son las siguientes:";
    ImprimeMatriz(orden, MDistPesos);
    cout << endl;
    return 0;
}

// Funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(int tamano, vector<vector<float>>& M){
    char v1, v2;
    float peso;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los v�rtices de la " << i << "� arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            cout << "Ingrese el peso de la arista: ";
            cin >> peso;
            M[ver1][ver2] = peso;
            M[ver2][ver1] = peso;
        } else{
            cout << "V�rtices fuera de rango. Int�ntelo nuevamente." << endl;
            i--;
        }
    }
}

/*
La funci�n ImprimeMatriz ya imprime la matriz de adyacencia organizada por columnas y filas correspondientes a los v�rtices.
Sin embargo, para mejorar la alineaci�n y claridad, se puede ajustar el formato de impresi�n usando setw.
*/

// Funci�n para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<float>>& M){
    cout << endl << endl << " ";

    for(int i = 1; i <= orden; i++){
        cout << setw(6) << char(96 + i);
    }
    cout << endl;

    for(int i = 1; i <= orden; i++){
        cout << char(96 + i);
        for(int j = 1; j <= orden; j++){
            cout << setw(6) << M[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Funci�n para obtener las distancias de peso m�nimo entre los v�rtices
void ObtenerDistancias(vector<vector<float>>& M, vector<vector<float>>& MDistPesos){
    queue<int> aux;

    for(int i = 1; i <= orden; i++){
        MDistPesos[i][i] = 0;
        aux.push(i);

        while(!aux.empty()){
            int actual = aux.front();
            aux.pop();

            for(int j = 1; j <= orden; j++){
                if(M[actual][j] != 0 && MDistPesos[i][actual] + M[actual][j] < MDistPesos[i][j]){
                    MDistPesos[i][j] = MDistPesos[i][actual] + M[actual][j];
                    aux.push(j);
                }
            }
        }
    }
}