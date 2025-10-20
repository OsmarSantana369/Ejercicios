#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa verifica si una digr�fica dada es transitiva.

Para esto, se usa la funci�n EsTransitiva(), la cual recibe como par�metros la matriz de adyacencia y el vector de colas de adyacencias. Dentro de esta funci�n, se recorre cada v�rtice y sus adyacencias, y para cada adyacencia, se revisan sus propias adyacencias. Si alguna de estas �ltimas no est� ya en la lista de adyacencias del v�rtice original y no es el mismo v�rtice, se concluye que la digr�fica no es transitiva. Si se recorren todas las adyacencias sin encontrar tal caso, entonces es transitiva.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias);
void ImprimeMatriz(vector<vector<int>>& M);
bool Encontrar(queue<int> fila, int elemento);
bool EsTransitiva(vector<vector<int>>& Matriz, vector<queue<int>>& adyacencias);

int orden, tamano;
bool Reiniciar;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la digr�fica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inv�lido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tama�o de la digr�fica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)){
            cout << "Tama�o inv�lido para una digr�fica simple." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    vector<vector<int>> M(orden + 1, vector<int>(orden + 1, 0));
    vector<queue<int>> adyacencias(orden + 1);

    IngresaAristas(M, adyacencias);
    ImprimeMatriz(M);
    
    if(EsTransitiva(M, adyacencias))
        cout << "La digr�fica es transitiva" << endl << endl;
    else 
        cout << "La digr�fica no es transitiva" << endl << endl;

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

// Funci�n para verificar si un entero est� almacenado en una cola
bool Encontrar(queue<int> fila, int elemento){
    queue<int> copia = fila;

    while(!copia.empty()){
        if(copia.front() == elemento)
            return true;

        copia.pop();
    }
    return false;
}

// Funci�n para verificar si una digr�fica es transitiva
bool EsTransitiva(vector<vector<int>>& Matriz, vector<queue<int>>& adyacencias){
	for(int i = 1; i <= orden; i++){
		queue<int> fila = adyacencias[i];
            
        while(!fila.empty()){
            queue<int> adyacentesVerticeActual = adyacencias[fila.front()];

            while(!adyacentesVerticeActual.empty()){
                int verticeFinal = adyacentesVerticeActual.front();
                adyacentesVerticeActual.pop();

                if(!Encontrar(adyacencias[i], verticeFinal) && verticeFinal != i)
                    return false;
            }
            fila.pop();
        }
    }
    return true;
}