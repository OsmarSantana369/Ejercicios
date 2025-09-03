#include <iostream>
#include <locale>
#include <vector>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un ·rbol (o bosque) generador de una gr·fica dada (Algoritmo de b√∫squeda en profundidad).

Se empieza por buscar el primer vÈrtice (alfab√©ticamente) que no ha sido visitado y se usa la FunciÛn Visitar() para a√±adirlo a *visitado*, mostrarlo en pantalla y buscar adyacencias que no esten en *visitado*.
    En caso de tener tales adyacencias, se a√±ade la arista correspondiente a *Indaristas* y se usa Visitar() con el vÈrtice encontrado.
    Este proceso se repite hasta que no haya m√°s adyacencias por visitar, momento en el cual se regresa a Buscar() para repetir el proceso.
El programa termina cuando todos los vÈrtices est√©n en *visitado*.

Si la gr·fica no es conexa, la FunciÛn Buscar() se encargar√° de encontrar todas las componentes conexas y generar un bosque generador en lugar de un ·rbol generador.

Por √∫ltimo, se imprimen las aristas que inducen el ·rbol (bosque) generador.

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

    cout<<"Ingrese el orden de la gr·fica: ";
    cin>>orden;

    if (orden <= 0) {
        cout<<"Orden inv·lido. Debe ser mayor que 0.\n";
        return 1;
    }

    cout<<"\nIngrese el tamaÒo de la gr·fica: ";
    cin>>tamano;

    if (tamano < 0 || tamano > orden*(orden - 1)/2) {
        cout<<"TamaÒo inv·lido para una gr·fica simple.\n";
        return 1;
    }

    vector<vector<int>> M(orden+1, vector<int>(orden+1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    Buscar(M);

    cout<<endl<<endl;

    cout<<"El ·rbol (bosque) generador es la subgr·fica inducida por las aristas: "<<endl;

    while (!Indaristas.empty()) {
		cout << Indaristas.front();
		Indaristas.pop();
		cout << Indaristas.front() << endl;
		Indaristas.pop();
	}

    cout<<endl;

    return 0;
}

//FunciÛn para ingresar las adyacencias de la gr·fica
void IngresaAristas(int tamano, vector<vector<int>>& M){
    char v1, v2;
    for (int i = 1; i <= tamano; i++){
        cout<<"\nInserte los vÈrtices de la "<<i<<"∞ arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()){
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"vÈrtices fuera de rango. IntÈntelo nuevamente.\n";
            i--;
        }
    }
}

// FunciÛn para imprimir la matriz de adyacencia
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
    cout << endl << char(k+96);

	while(!cola.empty()){
        int vertice = cola.front();
        cola.pop();

        for(int x = 1; x <= orden; x++){
            if(M[vertice][x] != 0 && !Encontrar(visitado, x)){
                cola.push(x);
                visitado.push(x);
                cout << endl << char(x+96);
                Indaristas.push(vertice+96);
                Indaristas.push(x+96);
            }
        }
    }
}
