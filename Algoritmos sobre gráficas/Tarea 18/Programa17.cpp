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

void IngresaAristas(vector<vector<float>>& M, vector<queue<int>>& Adyacencias);
void ImprimeMatriz(vector<vector<float>>& M);
bool MismaComponente(int vertice1, int vertice2, vector<queue<int>>& Adyacencias);


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

    IngresaAristas(M, Adyacencias);
    ImprimeMatriz(M);

    char ver1, ver2;
	cout << "Ingrese el primer v�rtice: ";
	cin >> ver1;
	cout << "Ingrese el segundo v�rtice: ";
	cin >> ver2;
	int vertice1 = tolower(ver1) - 96;
	int vertice2 = tolower(ver2) - 96;

	if(MismaComponente(vertice1, vertice2, Adyacencias))
        cout << endl << "Los v�rtices " << ver1 << " y " << ver2 << " est�n en la misma componente conexa." << endl;
    else
        cout << endl << "Los v�rtices " << ver1 << " y " << ver2 << " est�n en distintas componentes conexas." << endl;

    return 0;
}

// Funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(vector<vector<float>>& M, vector<queue<int>>& Adyacencias){
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
void ImprimeMatriz(vector<vector<float>>& M){
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

bool MismaComponente(int vertice1, int vertice2, vector<queue<int>>& Adyacencias){
    queue<int> visitados;
    queue<int> auxiliar;
    visitados.push(vertice1);
    auxiliar.push(vertice1);

    while(!auxiliar.empty()){
        int verticeActual = visitados.front();
        queue<int> adyacentesActual = Adyacencias[verticeActual];
        auxiliar.pop();

        if(Encontrar(adyacentesActual, vertice2))
            return true;
        else{
            while(!adyacentesActual.empty()){
                if(!Encontrar(visitados, adyacentesActual.front())){
                    visitados.push(adyacentesActual.front());
                    auxiliar.push(adyacentesActual.front());
                }
                adyacentesActual.pop();
            }
        }
    }

    return false;
}
