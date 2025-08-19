#include <iostream>
#include <locale>
#include <vector>
using namespace std;

// Osmar Dominique Santana Reyes

// Algoritmo de b�squeda en profundidad
// Este programa obtiene el �rbol generador de una gr�fica dada (o bosque generador si la gr�fica es disconexa).
// Para esto, se obtendr� una lista de aristas que inducir�n el �rbol o bosque generador de la gr�fica original.
// La funci�n Buscar() asigna al vector *visitado* tantos ceros seg�n el orden de la gr�fica, inicializa un �ndice *id* en 0 y verifica qu� v�rtices de la gr�fica ya han sido visitados, es decir,
// cu�les ya han sido cubiertos por las aristas. Esto �ltimo es importante en el caso de las gr�ficas disconexas, pues en lo que sigue del algoritmo se obtendr�n las aristas deseadas de solo una de las componentes conexas.
// Si hay un v�rtice que no haya sido visitado entonces se usa la funci�n Visitar(), con entrada el v�rtice no visitado. En caso contrario, no se hace nada.
//     Luego, en esta funci�n se aumenta en 1 la variable *id* y el valor de esta se le asigna al vector *visitado* en la entrada que corresponde al v�rtice no visitado y se imprime la etiqueta del v�rtice.
//     Posteriormente, si el v�rtice no visitado es adyacente a otro v�rtice que tampoco ha sido visitado entonces ambos son registrados en el vector *Indaristas*,
//     el cual contiene los pares de v�rtices de cada arista que ser� parte del �rbol generador, adem�s de que se volver� a ejecutar la funci�n Visitar() pero cuya entrada es el otro vector no visitado.
//     La funci�n Visitar() se ejecutar� hasta que haya un v�rtice que no sea adyacente a otro no visitado. Cuando esto pase, el programa,
//     continuar� con los v�rtices que se hayan quedado pendientes y terminar� de ejecutarse cuando todos los v�rtices hayan sido visitados, es decir, cuando el vector *visitado* ya no tenga ceros.
// Finalmente, se imprimen los v�rtices terminales de las aristas que inducen el �rbol o bosque generador de la gr�fica dada.
// En caso, de haber v�rtices no cubiertos por estas aristas, entonces estos v�rtices son aislados.

// Orden

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
    cout
    <<"Ingrese el orden de la gr�fica: ";
    cin>>orden;

    cout<<endl<<"Ingrese el tama�o de la gr�fica: ";
    cin>>tamano;

    IngresaAristas(tamano, M);

    cout<<endl;

    cout<<"La matriz de adyacencia es la siguiente:"<<endl;
    ImprimeMatriz(orden, M);

    Buscar(visitado);

    cout<<endl<<endl;

    cout<<"El �rbol generador es la subgr�fica inducida por las aristas: "<<endl;

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
        cout<<endl<<"Inserte los v�rtices de la "<<i<<"� arista: ";
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

