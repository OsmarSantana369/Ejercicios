#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Programa que verifica si dos vértices pertenecen a la misma componente conexa de una gráfica.

Para esto, se solicita al usuario ingresar las letras que correponden a los vértices a verificar. Después, se usa la función MismaComponente(), la cual crea dos colas llamadas *visitados* y *auxiliar*, y se añade a cada una el primer vértice insertado. Luego, se toma un vértice de *auxiliar* y se verifica si alguna de sus adyacencias corresponde al segundo vertice insertado, de ser así, ambos vértices están en la misma componente. De lo contrario, todas las adyacencias se incorporan a *visitados* y *auxiliar*.
Esto se repite hasta hallar al segundo vértice o que el vector auxiliar esté vacio, lo cual quiere decir que todos los vértices de la componente en la que está el primer vértice están en *visitado* y el vértice 2 está en alguna otra componente.

Finalmente, se imprime el resultado obtenido.

Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(vector<vector<float>>& M, vector<queue<int>>& Adyacencias);
void ImprimeMatriz(vector<vector<float>>& M);
bool Encontrar(queue<int> fila, int elemento);
bool MismaComponente(int vertice1, int vertice2, vector<queue<int>>& Adyacencias);

int orden, tamano;
bool Reiniciar;

int main(){
    setlocale(LC_ALL, "");

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
	vector<queue<int>> Adyacencias(orden + 1);

    IngresaAristas(M, Adyacencias);
    ImprimeMatriz(M);

    do{
        char ver1, ver2;
        cout << "Ingrese el primer vértice: ";
        cin >> ver1;
        cout << "Ingrese el segundo vértice: ";
        cin >> ver2;
        int vertice1 = tolower(ver1) - 96;
        int vertice2 = tolower(ver2) - 96;

        if(vertice1 > 0 && vertice1 <= orden && vertice2 > 0 && vertice2 <= orden){
            if(MismaComponente(vertice1, vertice2, Adyacencias))
                cout << endl << "Los vértices " << ver1 << " y " << ver2 << " están en la misma componente conexa." << endl;
            else
                cout << endl << "Los vértices " << ver1 << " y " << ver2 << " están en distintas componentes conexas." << endl;
            Reiniciar = false;
        } else{
            cout << "Los vértices ingresados no corresponden a la gráfica ingresada. Intente nuevamente.";
            Reiniciar = true;
        }
    } while(Reiniciar);

    return 0;
}

// Función para ingresar las adyacencias de la gráfica
void IngresaAristas(vector<vector<float>>& M, vector<queue<int>>& Adyacencias){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            Adyacencias[ver1].push(ver2);
            M[ver2][ver1] = 1;
			Adyacencias[ver2].push(ver1);
        } else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
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

// Función que comprueba si dos vértices están en una misma componente conexa
bool MismaComponente(int vertice1, int vertice2, vector<queue<int>>& Adyacencias){
    queue<int> visitados;
    queue<int> auxiliar;
    visitados.push(vertice1);
    auxiliar.push(vertice1);

    while(!auxiliar.empty()){
        int verticeActual = auxiliar.front();
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
