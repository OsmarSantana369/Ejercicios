##include <iostream>
#include <locale>
#include <vector>
#include <cctype>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa obtiene la matriz de adyacencia de una gráfica y la imprime.

Para esto se ingresa el orden y tamaño de la gráfica, en caso de no ser los adecuados, se imprime un mensaje con esta aclaración.
Cuando sí lo son se crea una matriz cuadrada de dimensión *orden* y se ejecuta la función IngresaAristas() que solicita las adyacencias de la gráfica,
a partir de las etiquetas de los vértices (las letras del abecedario iniciando en la "a").
Luego, se obtiene su índice dentro de la matriz de adyacencia y se coloca 1 en las entradas correspondientes.
Si algún vértice no corresponde a la gráfica se imprime un mensaje para volver a hacer la incersión.
Después, se ejecuta la función ImprimeMatriz() que imprime la matriz junto con encabezados de los vértices que corresponden.

Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
void Buscar(int vector<int>& visitado);
void Visitar(int k, int id);

std::vector<char> Indaristas;
char letra;
int i, j, orden, tamano, M[30][30], visitado[30];


int main()
{
    setlocale(LC_ALL, "");
    cout
    <<"Ingrese el orden de la gráfica: ";
    cin>>orden;

    cout<<endl<<"Ingrese el tamaño de la gráfica: ";
    cin>>tamano;

    IngresaAristas(tamano, M);

    cout<<endl;

    cout<<"La matriz de adyacencia es la siguiente:"<<endl;
    ImprimeMatriz(orden, M);

    Buscar(visitado);

    cout<<endl<<endl;

    cout<<"El árbol generador es la subgráfica inducida por las aristas: "<<endl;

    for(i = 0; i < (Indaristas.size()+1)/2; i++)
    {
        cout<<Indaristas[2*i]<<Indaristas[2*i + 1]<<endl;
    }

    return 0;
}

//Función para ingresar las adyacencias de la gráfica
void IngresaAristas(int tamano, vector<vector<int>>& M)
{
    char v1, v2;
    for (int i = 1; i <= tamano; i++) {
        cout<<"\nInserte los vértices de la "<<i<<"° arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()) {
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"Vértices fuera de rango. Intentelo nuevamente.\n";
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<int>>& M)
{
    cout<<"\n ";
    for (int i = 1; i <= orden; i++) {
        cout<<"   "<<char(96 + i);
    }

    for (int i = 1; i <= orden; i++) {
        cout<<"\n"<<char(96 + i)<<"   ";
        for (int j = 1; j <= orden; j++) {
            cout<<M[i][j]<<"   ";
        }
    }
    cout<<endl;
}

void Buscar(int visitado[30])
{
    int id, k;
    for(k = 1; k <= orden; k++)
        visitado[k] = 0;

    id = 0;

    for(k = 1; k <= orden; k++)
    {
        if(visitado[k] == 0)
            Visitar(k, id);
    }
}

void Visitar(int k, int id)
{
    int x;
    id++;
    visitado[k] = id;

    char vertice = k + 96;
    cout<<endl<<vertice;

    for(x = 1; x <= orden; x++)
    {
        if(M[k][x] != 0 && visitado[x] == 0)
        {
            Indaristas.push_back(k+96);
            Indaristas.push_back(x+96);
            Visitar(x, id);
        }
    }
}

