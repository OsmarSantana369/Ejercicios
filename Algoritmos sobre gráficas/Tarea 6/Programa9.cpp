#include <iostream>
#include <locale>
#include <vector>
#include <stack>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un �rbol (o bosque) generador de una gr�fica dada (Algoritmo de b�squeda en profundidad).

Se empieza por buscar el primer v�rtice (alf�beticamente) que no ha sido visitado y se usa la funci�n Visitar() para a�adirlo a *visitado*, mostrarlo en pantalla y buscar adyacencias que no esten en *visitado*.
    En caso de tener tales adyacencias, se a�ade la arista correspondiente a *Indaristas* y se usa Visitar() con el v�rtice encontrado.
    Este proceso se repite hasta que no haya m�s adyacencias por visitar, momento en el cual se regresa a Buscar() para repetir el proceso.
El programa termina cuando todos los v�rtices est�n en *visitado*.

Si la gr�fica no es conexa, la funci�n Buscar() se encargar� de encontrar todas las componentes conexas y generar un bosque generador en lugar de un �rbol generador.

Por �ltimo, se imprimen las aristas que inducen el �rbol (bosque) generador.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
void Buscar(vector<vector<int>>& M);
void Visitar(int k, vector<vector<int>>& M);

char letra;
int i, j, orden, tamano;
stack<int> visitado;
stack<char> Indaristas;

int main()
{
    setlocale(LC_ALL, "");

    cout<<"Ingrese el orden de la gr�fica: ";
    cin>>orden;

    if (orden <= 0) {
        cout<<"Orden inv�lido. Debe ser mayor que 0.\n";
        return 1;
    }

    cout<<"\nIngrese el tama�o de la gr�fica: ";
    cin>>tamano;

    if (tamano < 0 || tamano > orden*(orden - 1)/2) {
        cout<<"Tama�o inv�lido para una gr�fica simple.\n";
        return 1;
    }

    vector<vector<int>> M(orden+1, vector<int>(orden+1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    Buscar(M);

    cout<<endl<<endl;

    cout<<"El �rbol (bosque) generador es la subgr�fica inducida por las aristas: "<<endl;

    while (!Indaristas.empty()) {
		cout << Indaristas.top();
		Indaristas.pop();
		cout << Indaristas.top() << endl;
		Indaristas.pop();
	}

    cout<<endl;

    return 0;
}

//funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(int tamano, vector<vector<int>>& M){
    char v1, v2;
    for (int i = 1; i <= tamano; i++){
        cout<<"\nInserte los v�rtices de la "<<i<<"� arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()){
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"v�rtices fuera de rango. Int�ntelo nuevamente.\n";
            i--;
        }
    }
}

// funci�n para imprimir la matriz de adyacencia
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

bool Encontrar(stack<int> fila, int elemento){
    stack<int> copia = fila;
    while(!copia.empty()){
        if(copia.top() == elemento)
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
    cout << endl << char(visitado.top()+96);

    for(int x = 1; x <= orden; x++){
        if(M[k][x] != 0 && !Encontrar(visitado, x)){
            Indaristas.push(k+96);
            Indaristas.push(x+96);
            Visitar(x, M);
        }
    }
}
