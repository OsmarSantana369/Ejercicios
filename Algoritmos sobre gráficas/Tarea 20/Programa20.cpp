#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa obtiene la cerradura transitiva de una digr�fica dada.



Orden del algoritmo: O(tamano + potencia*orden^3)
*/

void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias);
void ImprimeMatriz(vector<vector<int>>& M);
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int n);

int orden, tamano;
bool Reiniciar;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la gr�fica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inv�lido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tama�o de la gr�fica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tama�o inv�lido para una gr�fica simple." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    vector<vector<int>> M(orden + 1, vector<int>(orden + 1, 0));
    vector<queue<int>> adyacencias(orden + 1);

    IngresaAristas(M, adyacencias);
    ImprimeMatriz(M);
    
	vector<vector<int>> MatrizCerradura = M;
    vector<queue<int>> adyacenciasCerradura = adyacencias;

    CerraduraTransitiva(MatrizCerradura, adyacenciasCerradura);

    return 0;
}

// Funci�n para ingresar las adyacencias de la digr�fica
void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los v�rtices de la " << i << "� arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            adyacencias[ver1].push(ver2);
        }
        else{
            cout << "V�rtices fuera de rango. Int�ntelo nuevamente." << endl;
            i--;
        }
    }
}

// Funci�n para imprimir la matriz de adyacencia
void ImprimeMatriz(vector<vector<int>>& M){
    cout << endl << endl << " ";

    for(int i = 1; i <= orden; i++)
        cout << setw(3) << char(96 + i);

    cout << endl;

    for(int i = 1; i <= orden; i++){
        cout << char(96 + i);

        for(int j = 1; j <= orden; j++)
            cout << setw(3) << M[i][j];

        cout << endl;
    }
    cout << endl;
}

// Funci�n para elevar una matriz a una n-�sima potencia
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int potencia){
    vector<vector<int>> resultado(orden + 1, vector<int>(orden + 1, 0));

    for (int i = 1; i <= orden; i++)
        resultado[i][i] = 1;

    for (int k = 1; k <= potencia; k++){
        vector<vector<int>> temp(orden + 1, vector<int>(orden + 1, 0));

        for (int i = 1; i <= orden; i++){
            for (int j = 1; j <= orden; j++){
                for (int l = 1; l <= orden; l++)
                    temp[i][j] += resultado[i][l] * M[l][j];
            }
        }
        resultado = temp;
    }
    return resultado;
}

void CerraduraTransitiva(vector<vector<int>>& Matriz, vector<queue<int>>& adyacencias){
	int contador = 0;

	do{
		vector<vector<int>> MDist2 = PotenciaMatriz(Matriz, 2);
		contador = 0;

		for(int i = 1; i <= orden; i++){
			for(int j = 1; j <= orden; j++){
				if(MDist2[i][j] > 0 && Matriz[i][j] == 0 && i != j){
					Matriz[i][j] = 1;
					adyacencias[i].push(j);
					contador++;
				}
			}
		}
	} while(contador != 0);
}
