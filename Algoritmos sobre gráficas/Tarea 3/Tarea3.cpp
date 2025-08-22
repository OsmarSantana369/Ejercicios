#include <iostream>
#include <locale.h>
#include <vector>
using namespace std;

// Osmar Dominique Santana Reyes

// Algoritmo de búsqueda en profundidad
// Este programa obtiene el árbol generador de una gráfica dada (o bosque generador si la gráfica es disconexa).
// Para esto, se obtendrá una lista de aristas que inducirán el árbol o bosque generador de la gráfica original.
// La función Buscar() asigna al vector *visitado* tantos ceros según el orden de la gráfica, inicializa un índice *id* en 0 y verifica qué vértices de la gráfica ya han sido visitados, es decir,
// cuáles ya han sido cubiertos por las aristas. Esto último es importante en el caso de las gráficas disconexas, pues en lo que sigue del algoritmo se obtendrán las aristas deseadas de solo una de las componentes conexas.
// Si hay un vértice que no haya sido visitado entonces se usa la función Visitar(), con entrada el vértice no visitado. En caso contrario, no se hace nada.
//     Luego, en esta función se aumenta en 1 la variable *id* y el valor de esta se le asigna al vector *visitado* en la entrada que corresponde al vértice no visitado y se imprime la etiqueta del vértice.
//     Posteriormente, si el vértice no visitado es adyacente a otro vértice que tampoco ha sido visitado entonces ambos son registrados en el vector *Indaristas*,
//     el cual contiene los pares de vértices de cada arista que será parte del árbol generador, además de que se volverá a ejecutar la función Visitar() pero cuya entrada es el otro vector no visitado.
//     La función Visitar() se ejecutará hasta que haya un vértice que no sea adyacente a otro no visitado. Cuando esto pase, el programa,
//     continuará con los vértices que se hayan quedado pendientes y terminará de ejecutarse cuando todos los vértices hayan sido visitados, es decir, cuando el vector *visitado* ya no tenga ceros.
// Finalmente, se imprimen los vértices terminales de las aristas que inducen el árbol o bosque generador de la gráfica dada.
// En caso, de haber vértices no cubiertos por estas aristas, entonces estos vértices son aislados.

// Orden: O((Indaristas.size()+1)/2 + tamano + orden^2)

void IngresaAristas(int tamano, int M[30][30]);
void ImprimeMatriz(int orden, int M[30][30]);
void Buscar(int visitado[30]);
void Visitar(int k, int id);

std::vector<char> Indaristas;
char letra;
int i, j, orden, tamano, M[30][30], visitado[30];


int main()
{
    setlocale(LC_ALL, "");
    cout<<"Ingrese el orden de la gráfica: ";
    cin>>orden;

    cout<<endl<<"Ingrese el tamaño de la gráfica: ";
    cin>>tamano;

    IngresaAristas(tamano, M);

    cout<<endl;

    cout<<"La matriz de adyacencia es la siguiente:"<<endl;
    ImprimeMatriz(orden, M);

    Buscar(visitado);

    cout<<endl<<endl;

    cout<<"El árbol (o bosque) generador es la subgráfica inducida por las aristas: "<<endl;

    for(i = 0; i < (Indaristas.size()+1)/2; i++)
    {
        cout<<Indaristas[2*i]<<Indaristas[2*i + 1]<<endl;
    }

    return 0;
}


void IngresaAristas(int tamano, int M[30][30])
{
    char v1, v2;
    for(i = 1; i <= tamano; i++)
    {
        cout<<endl<<"Inserte los vértices de la "<<i<<"° arista: ";
        cin>>v1>>v2;

        int ver1 = v1;
        int ver2 = v2;
        ver1 = ver1 - 96;
        ver2 = ver2 - 96;

        M[ver1][ver2] = 1;
        M[ver2][ver1] = 1;
    }
}

void ImprimeMatriz(int orden, int M[30][30])
{
    char letra1;
    letra = 'a';
    letra1 = letra;

    cout<<" ";
    for(i = 1; i <= orden; i++)
    {
        cout<<"   "<<letra;
        letra++;
    }

    for(i = 1; i <= orden; i++)
    {
        cout<<endl<<letra1<<"   ";
        letra1++;

        for(j = 1; j <= orden; j++)
        {
            cout<<M[i][j]<<"   ";
        }
    }

    cout<<endl<<endl;
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

