#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un árbol (o bosque) generador de una gráfica dada (Algoritmo de búsqueda en profundidad).

Para esto se usa la función Buscar() que rellena al vector *Insertado* con ceros y luego verifica qué vértices ya fueron visitados. Si hay alguno que no fue visitado, se utiliza la función Visitar(), para recorrer la gráfica y marcar los vértices visitados. 
Es decir, se fija en los vértices adyacentes al que está visitando y si encuentra alguno que no fue visitado, se vuelve a ejecutar la función Visitar(), hasta que no encuentre más vértices adyacentes no visitados.

Si la gráfica no es conexa, la función Buscar() se encargará de encontrar todas las componentes conexas y generar un bosque generador en lugar de un árbol generador.

Por último, se imprimen las aristas que inducen el árbol (bosque) generador.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
void Buscar(vector<int>& visitado, vector<vector<int>>& M);
void Visitar(int k, int id, vector<int>& visitado, vector<vector<int>>& M);

std::vector<char> Indaristas;
char letra;
int i, j, orden, tamano;

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
    vector<int> visitado(orden+1);

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    Buscar(visitado, M);

    cout<<endl<<endl;

    cout<<"El árbol (bosque) generador es la subgráfica inducida por las aristas: "<<endl;

    for(i = 0; i < Indaristas.size(); i += 2){
        cout<<Indaristas[i]<<Indaristas[i+1]<<endl;
    }

    return 0;
}

//función para ingresar las adyacencias de la gráfica
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
            cout<<"vértices fuera de rango. Inténtelo nuevamente.\n";
            i--;
        }
    }
}

// función para imprimir la matriz de adyacencia
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

void Buscar(vector<int>& visitado, vector<vector<int>>& M)
{
    int id, k;
    for(k = 1; k <= orden; k++)
        visitado[k] = 0;

    id = 0;

    for(k = 1; k <= orden; k++)
    {
        if(visitado[k] == 0)
            Visitar(k, id, visitado, M);
    }
}

void Visitar(int k, int id, vector<int>& visitado, vector<vector<int>>& M)
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
            Visitar(x, id, visitado, M);
        }
    }
}
