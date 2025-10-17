#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa obtiene la cerradura transitiva de una digráfica dada.

Para esto, se usa la función CerraduraTransitiva(), la cual recibe como parámetros la matriz de adyacencia y el vector de colas de adyacencias. Dentro de esta función, se utiliza un ciclo do-while que se repite hasta que no se realicen más cambios en la matriz de adyacencia. En cada iteración, se recorre cada vértice y sus adyacencias, y para cada adyacencia, se revisan sus propias adyacencias. Si alguna de estas últimas no está ya en la lista de adyacencias del vértice original y no es el mismo vértice, se añade a la matriz y a la lista de adyacencias.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias);
void ImprimeMatriz(vector<vector<int>>& M);
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int n);
void CerraduraTransitiva(vector<vector<int>>& Matriz, vector<queue<int>>& adyacencias);

int orden, tamano;
bool Reiniciar;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la digráfica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inválido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tamaño de la digráfica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)){
            cout << "Tamaño inválido para una digráfica simple." << endl;
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

    cout << endl << "Matriz de adyacencia de la cerradura transitiva:";
    ImprimeMatriz(MatrizCerradura);

    cout << "Adyacencias de la cerradura transitiva:" << endl;

    for(int i = 1; i <= orden; i++){
        cout << char(96 + i) << ": ";

        queue<int> temp = adyacenciasCerradura[i];
        while(!temp.empty()){
            cout << char(96 + temp.front()) << " ";
            temp.pop();
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}

// Función para ingresar las adyacencias de la digráfica
void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            adyacencias[ver1].push(ver2);
        }
        else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
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

// Función para verificar si un entero está almacenado en una cola
bool Encontrar(queue<int> fila, int elemento){
    queue<int> copia = fila;

    while(!copia.empty()){
        if(copia.front() == elemento)
            return true;

        copia.pop();
    }
    return false;
}

// Función para obtener la cerradura transitiva de una digráfica
void CerraduraTransitiva(vector<vector<int>>& Matriz, vector<queue<int>>& adyacencias){
	int contador = 0;

	do{
		contador = 0;

		for(int i = 1; i <= orden; i++){
			queue<int> fila = adyacencias[i];
            
            while(!fila.empty()){
                queue<int> adyacentesVerticeActual = adyacencias[fila.front()];

                while(!adyacentesVerticeActual.empty()){
                    int verticeFinal = adyacentesVerticeActual.front();
                    adyacentesVerticeActual.pop();

                    if(!Encontrar(adyacencias[i], verticeFinal) && verticeFinal != i){
                        Matriz[i][verticeFinal] = 1;
                        adyacencias[i].push(verticeFinal);
                        contador++;
                    }
                }
                fila.pop();
            }
        }
	} while(contador != 0);
}
