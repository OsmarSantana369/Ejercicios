#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Programa que encuentra las componentes conexas de una gr�fica y los v�rtices que pertenecen a cada una.

Este programa est� basado en el de b�squeda en profundidad, el cual visita cada v�rtice mediante sus adyacencias para obtener un �rbol o bosque generador. Si la gr�fica es conexa, la funci�n Buscar() solo usar� la funci�n Visitar() una vez, ya que todos los v�rtices estar�n conectados. Si no es conexa, la funci�n Buscar() llamar� a la funci�n Visitar() tantas veces como componentes conexas haya y cada vez que se llame se incrementar� el contador numeroComponentes.

En este programa, la funci�n Visitar() toma un v�rtice k, lo agrega a *visitado* y a la cola de v�rtices de la componente conexa en cuesti�n y revisa sus adyacencias. Si una de estas adyacencias no est� en *visitado*, entonces se llama recursivamente a la funci�n Visitar() con este v�rtice. Esto se repite hasta que se hayan visitado todos los v�rtices conectados al v�rtice inicial k.

Finalmente, se imprime el n�mero de componentes conexas y los v�rtices que pertenecen a cada una, o bien, se indica que la gr�fica es conexa.

Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M, vector<queue<int>>& Adyacencias);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
vector<queue<int>> Buscar(vector<vector<float>>& M, vector<queue<int>>& Adyacencias);
void Visitar(int k, vector<vector<float>>& M, vector<queue<int>>& ComponentesCopia, vector<queue<int>>& Adyacencias);

int orden, tamano, numeroComponentes = 0;
bool Reiniciar;
queue<int> visitado;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la gr�fica: ";
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
	vector<queue<int>> Adyacencias(orden + 1);

    IngresaAristas(tamano, M, Adyacencias);
    ImprimeMatriz(orden, M);

	vector<queue<int>> Componentes = Buscar(M, Adyacencias);

	if(numeroComponentes == 1)
		cout << "La gr�fica es conexa." << endl;
	else{
		for(int i = 1; i <= numeroComponentes; i++){
			cout << "La " << i << "� componente conexa tiene a los v�rtices: ";

			while(!Componentes[i].empty()){
				cout << char(96 + Componentes[i].front()) << " ";
				Componentes[i].pop();
			}
			cout << endl;
		}
	}
    cout << endl;

    return 0;
}

// Funci�n para ingresar las adyacencias de la gr�fica o digr�fica
void IngresaAristas(int tamano, vector<vector<float>>& M, vector<queue<int>>& Adyacencias){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los v�rtices de la " << i << "� arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            Adyacencias[ver1].push(ver2);
            M[ver2][ver1] = 1;
			Adyacencias[ver2].push(ver1);
        } else{
            cout << "V�rtices fuera de rango. Int�ntelo nuevamente." << endl;
            i--;
        }
    }
}

// Funci�n para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<float>>& M){
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

bool Encontrar(queue<int> fila, int elemento){
    queue<int> copia = fila;

    while(!copia.empty()){
        if(copia.front() == elemento)
            return true;

        copia.pop();
    }
    return false;
}

vector<queue<int>> Buscar(vector<vector<float>>& M, vector<queue<int>>& Adyacencias){
    vector<queue<int>> ComponentesCopia(orden + 1);

    for(int i = 1; i <= orden; i++){
        if(!Encontrar(visitado, i)){
            numeroComponentes++;
            Visitar(i, M, ComponentesCopia, Adyacencias);
        }
    }
    vector<queue<int>> Componentes(numeroComponentes + 1);

    for(int i = 1; i <= numeroComponentes; i++)
        Componentes[i] = ComponentesCopia[i];

    return Componentes;
}

void Visitar(int k, vector<vector<float>>& M, vector<queue<int>>& ComponentesCopia, vector<queue<int>>& Adyacencias){
    ComponentesCopia[numeroComponentes].push(k);
	visitado.push(k);

    for(int j = 1; j <= Adyacencias[k].size(); j++){
        int x = Adyacencias[k].front();
        Adyacencias[k].pop();

        if(!Encontrar(ComponentesCopia[numeroComponentes], x))
            Visitar(x, M, ComponentesCopia, Adyacencias);

        Adyacencias[k].push(x);
    }
}
