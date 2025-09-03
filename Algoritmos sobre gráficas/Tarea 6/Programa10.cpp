#include <iostream>
#include <locale>
#include <vector>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un árbol (o bosque) generador de una gráfica dada (Algoritmo de búsqueda en profundidad).

Se empieza por buscar el primer vértice (alfabéticamente) que no ha sido visitado y se usa la función Visitar() para añadirlo a *visitado*, mostrarlo en pantalla y buscar adyacencias que no esten en *visitado*.
    En caso de tener tales adyacencias, se añade la arista correspondiente a *Indaristas* y se usa Visitar() con el vértice encontrado.
    Este proceso se repite hasta que no haya más adyacencias por visitar, momento en el cual se regresa a Buscar() para repetir el proceso.
El programa termina cuando todos los vértices estén en *visitado*.

Si la gráfica no es conexa, la función Buscar() se encargará de encontrar todas las componentes conexas y generar un bosque generador en lugar de un árbol generador.

Por último, se imprimen las aristas que inducen el árbol (bosque) generador.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
void Buscar(vector<vector<int>>& M);
void Visitar(int k, vector<vector<int>>& M);

char letra;
int i, j, orden, tamano;
queue<int> visitado;
queue<int> cola;
queue<char> Indaristas;

int main()
{
    setlocale(LC_ALL, "");

    cout<<"Ingrese el orden de la gráfica: ";
    cin>>orden;

    if (orden <= 0) {
        cout<<"Orden inválido. Debe ser mayor que 0.\n";
        return 1;
    }

    cout<<"\nIngrese el tamaño de la gráfica: ";
    cin>>tamano;

    if (tamano < 0 || tamano > orden*(orden - 1)/2) {
        cout<<"Tamaño inválido para una gráfica simple.\n";
        return 1;
    }

    vector<vector<int>> M(orden+1, vector<int>(orden+1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    Buscar(M);

    cout<<endl<<endl;

    cout<<"El árbol (bosque) generador es la subgráfica inducida por las aristas: "<<endl;

    while (!Indaristas.empty()) {
		cout << Indaristas.front();
		Indaristas.pop();
		cout << Indaristas.front() << endl;
		Indaristas.pop();
	}

    cout<<endl;

    return 0;
}

//funciï¿½n para ingresar las adyacencias de la gráfica
void IngresaAristas(int tamano, vector<vector<int>>& M){
    char v1, v2;
    for (int i = 1; i <= tamano; i++){
        cout<<"\nInserte los vértices de la "<<i<<"° arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()){
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"vértices fuera de rango. Inténtelo nuevamente.\n";
            i--;
        }
    }
}

// funciï¿½n para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<int>>& M){
    cout<<"\n ";
    for (int i = 1; i <= orden; i++){
        cout<<"   "<<char(96 + i);
    }

    for (int i = 1; i <= orden; i++){
        cout<<"\n"<<char(96 + i)<<"   ";
        for (int j = 1; j <= orden; j++){
            cout<<M[i][j]<<"   ";
        }
    }
    cout<<endl;
}

bool Encontrar(queue<int> cola, int elemento){
    queue<int> copia = cola;
    while(!copia.empty()){
        if(copia.front() == elemento)
            return true;

        copia.pop();
    }

    return false;
}

void Buscar(vector<vector<int>>& M){
    for (i = 1; i <= orden; i++){
        if (!Encontrar(visitado, i))
            Visitar(i, M);
    }
}

void Visitar(int k, vector<vector<int>>& M){
    visitado.push(k);
    cola.push(k);
    cout << endl << char(visitado.front()+96);

	while(!cola.empty()){
        int nodo = cola.front();
        cola.pop();

        for(int x = 1; x <= orden; x++){
            if(M[nodo][x] != 0 && !Encontrar(visitado, x)){
                cola.push(x);
                Indaristas.push(nodo+96);
                Indaristas.push(x+96);
            }
        }
    }
}
