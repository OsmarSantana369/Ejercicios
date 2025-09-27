#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra las distancias de peso mínimo que hay de un vértice a otros (Algoritmo de Dijkstra).



Orden del algoritmo: O(potencia*orden^3 + tamano*NumCompCon)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
void ObtenerDistancias(vector<vector<float>>& M, vector<vector<float>>& MDistPesos);

int orden, tamano, infinito = INT_MAX;
int grafdigraf;
bool Reiniciar;

int main()
{
    setlocale(LC_ALL, "");

    do{
        cout << "Ingrese 1 si desea trabajar en una gráfica o 2 para una digráfica: ";
        cin >> grafdigraf;

        if(grafdigraf != 1 && grafdigraf != 2){
            cout << "Valores inválidos." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el orden de la gráfica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inválido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tamaño de la gráfica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tamaño inválido para una gráfica simple." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    vector<vector<float>> M(orden + 1, vector<float>(orden + 1, 0));
    vector<vector<float>> MDistPesos(orden + 1, vector<float>(orden + 1, infinito));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);
    ObtenerDistancias(M, MDistPesos);

    cout << endl << "Las distancias de peso mínimo entre los vértices son las siguientes:";
    ImprimeMatriz(orden, MDistPesos);
    cout << endl;
    return 0;
}

// Función para ingresar las adyacencias de la gráfica
void IngresaAristas(int tamano, vector<vector<float>>& M){
    char v1, v2;
    float peso;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            cout << "Ingrese el peso de la arista: ";
            cin >> peso;

            if(grafdigraf == 1){
                M[ver1][ver2] = peso;
                M[ver2][ver1] = peso;
            } else
                M[ver1][ver2] = peso;

        } else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<float>>& M){
    cout << endl << endl << " ";

    for(int i = 1; i <= orden; i++){
        cout << setw(7) << char(96 + i);
    }
    cout << endl;

    for(int i = 1; i <= orden; i++){
        cout << char(96 + i);
        for(int j = 1; j <= orden; j++){
            if(M[i][j] == infinito)
                cout << setw(7) << "infty";
            else
                cout << setw(7) << M[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Función para obtener las distancias de peso mínimo entre los vértices
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
