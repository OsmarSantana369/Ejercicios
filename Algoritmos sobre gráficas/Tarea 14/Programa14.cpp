#include <iostream>
#include <locale>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra las distancia de peso m�nimo o m�ximo que hay de un v�rtice a otros (Algoritmo de Dijkstra).



Orden del algoritmo: O(potencia*orden^3 + tamano*NumCompCon)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M);
void ImprimeMatriz(int orden, vector<vector<float>>& M);

int orden, tamano, minax;
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
	vector<vector<float>> MDist(orden + 1, vector<float>(orden + 1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    do{
        cout << endl << "Inserte 0 si quiere obtener distancias m�nimas o 1 para distancias m�ximas: ";
        cin >> minax;

        if(minax != 0 && minax != 1){
            cout << "Valor inv�lido." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

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

// Funci�n para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<float>>& M){
    cout << endl << endl;

    for(int i = 1; i <= orden; i++){
        cout << "   " << char(96 + i);
    }

    for(int i = 1; i <= orden; i++){
        cout << endl << char(96 + i) << "  ";
        for(int j = 1; j <= orden; j++){
            cout << M[i][j] << "   ";
        }
    }

    cout << endl;
}
