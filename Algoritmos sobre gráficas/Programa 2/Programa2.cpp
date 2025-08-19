#include <iostream>
using namespace std;

void IngresaMatriz(int dim, int M[20][20]);
void ImprimeMatriz(int dim, int M[20][20], char letra);

char letra;
int i, j, dim;
int M[20][20];

int main()
{
    cout<<"Inserte el carácter inicial: ";
    cin>>letra;

    cout<<endl<<"Ingrese la dimensión de la matriz: ";
    cin>>dim;

    IngresaMatriz(dim, M);

    cout<<endl;

    ImprimeMatriz(dim, M, letra);

    return 0;
}

void IngresaMatriz(int dim, int M[20][20])
{
    cout<<endl<<"Ingresa los valores de la matriz"<<endl;

    for(i = 1; i <= dim; i++)
    {
        for(j = 1; j <= dim; j++)
        {
            cout<<"Ingrese la entrada "<<i<<", "<<j<<": ";
            cin>>M[i][j];
        }
    }
}

void ImprimeMatriz(int dim, int M[20][20], char letra)
{
    char letra1;
    letra1 = letra;

    for(i = 1; i <= dim; i++)
    {
        cout<<"\t"<<letra;
        letra++;
    }

    for(i = 1; i <= dim; i++)
    {
        cout<<endl<<letra1<<"\t";
        letra1++;

        for(j = 1; j <= dim; j++)
        {
            cout<<M[i][j]<<"\t";
        }
    }
}
