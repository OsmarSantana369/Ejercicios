#include <iostream>
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

char letra;
bool euleriana = true;

int main()
{
    setlocale(LC_ALL, "");
    int orden, tamano, i, j;

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
    vector<int> Grados(orden+1);

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    cout<<endl<<"Los grados de cada vértice son: "<<endl;

    for(i = 1; i <= orden; i++)
    {
        Grados[i] = 0;

        for(j = 1; j <= orden; j++)
        {
            Grados[i] = Grados[i] + M[i][j];
        }
    }

    letra = 'a';

    for(i = 1; i <= orden; i++)
    {
        cout<<"gr("<<letra<<") = "<<Grados[i]<<endl;
        letra++;
    }

    for(i = 1; i <= orden; i++)
    {
        if(Grados[i]%2 == 1)
        {
            euleriana = false;
            break;
        }
    }

    if(euleriana)
        cout<<"La gráfica es euleriana."<<endl;
    else
        cout<<"La gráfica no es euleriana."<<endl;

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
