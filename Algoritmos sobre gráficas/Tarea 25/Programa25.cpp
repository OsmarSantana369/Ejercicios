#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa verifica si una didigráfica dada es débil, unilateral o fuertemente conexa.



Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
vector<vector<int>> ObtenerDistancias(vector<vector<int>>& M);

int orden, tamano, infinito = INT_MAX;
int grafdigraf;
bool Reiniciar;

int main()
{
    do{
        cout << endl << "Ingrese el orden de la didigráfica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inválido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tamaño de la digráfica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tamaño inválido para una digráfica simple." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    vector<vector<int>> M(orden + 1, vector<int>(orden + 1, 0));
    vector<vector<int>> MDist = ObtenerDistancias(M);

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    cout << "Matriz de distancias mínimas entre vértices:" << endl;
    ImprimeMatriz(orden, MDist);
    
    return 0;
}

// Función para ingresar las adyacencias de la digráfica
void IngresaAristas(int tamano, vector<vector<int>>& M){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° flecha: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
        } else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<int>>& M){
    cout << endl << endl << " ";

    for(int i = 1; i <= orden; i++){
        cout << setw(3) << char(96 + i);
    }
    cout << endl;

    for(int i = 1; i <= orden; i++){
        cout << char(96 + i);

        for(int j = 1; j <= orden; j++)
            cout << setw(3) << M[i][j];

        cout << endl;
    }
    cout << endl;
}

// Función para obtener las distancias mínimas entre los vértices
vector<vector<int>> ObtenerDistancias(vector<vector<int>>& M){
    queue<int> aux;
    vector<vector<int>> MDist(orden + 1, vector<int>(orden + 1, infinito));

    for(int i = 1; i <= orden; i++){
        MDist[i][i] = 0;
        aux.push(i);

        while(!aux.empty()){
            int actual = aux.front();
            aux.pop();

            for(int j = 1; j <= orden; j++){
                if(M[actual][j] != 0 && MDist[i][actual] + M[actual][j] < MDist[i][j]){
                    MDist[i][j] = MDist[i][actual] + M[actual][j];
                    aux.push(j);
                }
            }
        }
    }
}
