#include <iostream>
#include <locale>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un �rbol (o bosque) generador de una gr�fica dada (Algoritmo de b�squeda en profundidad).

Se empieza por buscar el primer v�rtice (alfab�ticamente) que no ha sido visitado y se usa la funci�n Visitar() para a�adirlo a *visitado*,
mostrarlo en pantalla y buscar adyacencias que no esten en *visitado*.
    En caso de tener tales adyacencias, se a�ade la arista correspondiente a *Indaristas* y se usa Visitar() con el v�rtice encontrado.
    Este proceso se repite hasta que no haya m�s adyacencias por visitar, momento en el cual se regresa a Buscar() para repetir el proceso.
El programa termina cuando todos los v�rtices est�n en *visitado*.

Si la gr�fica no es conexa, la funci�n Buscar() se encargar� de encontrar todas las componentes conexas y generar un bosque generador en lugar de un �rbol generador.

Por �ltimo, se imprimen las aristas que inducen el �rbol (bosque) generador.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
void Buscar(vector<vector<float>>& M);
void Visitar(int k, vector<vector<float>>& M, int i, int orden, vector<queue<char>>& Indaristas, vector<queue<int>>& PesosAristas);

int i, j, orden, tamano, minax;
float PesoTotal = 0;
stack<int> visitado;
queue<char> Indaristas;
queue<float> PesosAristas;

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

    vector<vector<float>> M(orden+1, vector<float>(orden+1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    cout << endl << "Inserte 0 si quiere obtener un �rbol m�nimo o 1 para un �rbol m�ximo: ";
    cin >> minax;

    Buscar(M);

    if(minax == 0)
        cout<<"El �rbol (bosque) generador m�nimo es la subgr�fica inducida por las aristas: "<<endl;
    else
        cout<<"El �rbol (bosque) generador m�ximo es la subgr�fica inducida por las aristas: "<<endl;

    while(!Indaristas.empty()){
        cout << Indaristas.front();
        Indaristas.pop();
        cout << Indaristas.front();
        Indaristas.pop();

        PesoTotal += PesosAristas.front();
        cout << " con peso " << PesosAristas.front() << endl;
        PesosAristas.pop();
    }

    cout << "El peso del �rbol es: " << PesoTotal << endl;

    return 0;
}

//Funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(int tamano, vector<vector<float>>& M){
    char v1, v2;
    float peso;

    for (int i = 1; i <= tamano; i++){
        cout<<"\nInserte los v�rtices de la "<<i<<"� arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"v�rtices fuera de rango. Int�ntelo nuevamente.\n";
            i--;
        }
    }

    for (int i = 1; i <= orden; i++){
        for(int j = i+1; j <= orden; j++){
            if(M[i][j] != 0){
                cout << endl << "Ingrese el peso de la arista " << char(i+96) << char(j+96) << ": ";
                cin >> peso;
                M[i][j] = peso;
                M[j][i] = peso;
            }
        }
    }
}

// Funci�n para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<float>>& M){
    cout<<endl<<endl;
    for (int i = 1; i <= orden; i++){
        cout<<"   "<<char(96 + i);
    }

    for (int i = 1; i <= orden; i++){
        cout<<"\n"<<char(96 + i)<<"  ";
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

void Buscar(vector<vector<float>>& M){
    for (j = 1; j <= orden; j++){
        if (!Encontrar(visitado, j))
            Visitar(j, M, i, orden, Indaristas, PesosAristas);
    }
}

void Visitar(int k, vector<vector<float>>& M, int i, int orden, vector<queue<char>>& Indaristas, vector<queue<int>>& PesosAristas){
    visitado.push(k);
    cout << char(visitado.top()+96) << endl;
    bool ady;

    do{
        float pesoM = 0;
        int verticeM;
        ady = false;

        for(int x = 1; x <= orden; x++){
            if(M[k][x] != 0 && !Encontrar(visitado, x)){
                if(ady){
                    if(minax == 0){
                        if(pesoM > M[k][x]){
                            pesoM = M[k][x];
                            verticeM = x;
                        }
                    } else {
                        if(pesoM < M[k][x]){
                            pesoM = M[k][x];
                            verticeM = x;
                        }
                    }
                } else{
                    pesoM = M[k][x];
                    verticeM = x;
                    ady = true;
                }
            }
        }

        if(ady){
            Indaristas.push(k+96);
            Indaristas.push(verticeM+96);
            PesosAristas.push(pesoM);
            Visitar(verticeM, M, i, orden, Indaristas, PesosAristas);
        }

    }while(ady);
}
