#include <iostream>
#include<locale>
using namespace std;

//Osmar
//Descrpcion
//Orden

void IngresaAristas(int tamano, int M[30][30]);
void ImprimeMatriz(int orden, int M[30][30]);

char letra;
int i, j, orden, tamano, M[30][30], Grados[30], ady;
bool euleriana = true;

int main()
{
    setlocale(LC_ALL, "");
    cout<<endl<<"Ingrese el orden de la gr�fica: ";
    cin>>orden;

    cout<<endl<<"Ingrese el tama�o de la gr�fica: ";
    cin>>tamano;

    IngresaAristas(tamano, M);

    cout<<endl;

    cout<<"La matriz de adyacencia es la siguiente:"<<endl;
    ImprimeMatriz(orden, M);

    cout<<endl<<"Los grados de cada v�rtice son: "<<endl;

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
        cout<<"La gr�fica es euleriana."<<endl;
    else
        cout<<"La gr�fica no es euleriana."<<endl;

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

    cout<<endl;
}
