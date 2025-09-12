#include <iostream>
#include <locale>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un árbol (o bosque) generador de una gráfica dada (Algoritmo de búsqueda en profundidad).

Se empieza por buscar el primer vértice (alfabéticamente) que no ha sido visitado y se usa la función Visitar() para añadirlo a *visitado*,
mostrarlo en pantalla y buscar adyacencias que no esten en *visitado*.
    En caso de tener tales adyacencias, se añade la arista correspondiente a *Indaristas* y se usa Visitar() con el vértice encontrado.
    Este proceso se repite hasta que no haya más adyacencias por visitar, momento en el cual se regresa a Buscar() para repetir el proceso.
El programa termina cuando todos los vértices estén en *visitado*.

Si la gráfica no es conexa, la función Buscar() se encargará de encontrar todas las componentes conexas y generar un bosque generador en lugar de un árbol generador.

Por último, se imprimen las aristas que inducen el árbol (bosque) generador.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
void Buscar(vector<vector<float>>& M, int i, int orden, vector<queue<char>>& Indaristas, vector<queue<float>>& PesosAristas);
void Visitar(int k, vector<vector<float>>& M, int i, int orden, vector<queue<char>>& Indaristas, vector<queue<float>>& PesosAristas);

int i, j, orden, tamano, minax;
float PesoTotal;
stack<int> visitado;

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

    vector<vector<float>> M(orden+1, vector<float>(orden+1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    cout << endl << "Inserte 0 si quiere obtener un árbol mínimo o 1 para un árbol máximo: ";
    cin >> minax;

    vector<queue<float>> PesosAristas(orden + 1);
    vector<queue<char>> Indaristas(orden + 1);

    for(i = 1; i <= orden; i++){
        cout << endl << "Empezando por " << char(i+96) << endl;
        Buscar(M, i, orden, Indaristas, PesosAristas);

        while(!visitado.empty())
            visitado.pop();
    }

    for(i = 1; i <= orden; i++){
        PesoTotal = 0;
        cout << endl << "Empezando por " << char(i+96) << endl;

        if(minax == 0)
            cout<<"El árbol (bosque) generador mínimo es la subgráfica inducida por las aristas: "<<endl;
        else
            cout<<"El árbol (bosque) generador máximo es la subgráfica inducida por las aristas: "<<endl;

        while(!Indaristas[i].empty()){
            cout << Indaristas[i].front();
            Indaristas[i].pop();
            cout << Indaristas[i].front();
            Indaristas[i].pop();

            PesoTotal += PesosAristas[i].front();
            cout << " con peso " << PesosAristas[i].front() << endl;
            PesosAristas[i].pop();
        }

        cout << "El peso del árbol es: " << PesoTotal << endl;
    }

    cout<<endl;

    return 0;
}

//Función para ingresar las adyacencias de la gráfica
void IngresaAristas(int tamano, vector<vector<float>>& M){
    char v1, v2;
    float peso;

    for (int i = 1; i <= tamano; i++){
        cout<<"\nInserte los vértices de la "<<i<<"° arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"vértices fuera de rango. Inténtelo nuevamente.\n";
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

// Función para imprimir la matriz de adyacencia
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

void Buscar(vector<vector<float>>& M, int i, int orden, vector<queue<char>>& Indaristas, vector<queue<float>>& PesosAristas){
    Visitar(i, M, i, orden, Indaristas, PesosAristas);

    for (j = 1; j <= orden; j++){
        if (!Encontrar(visitado, j))
            Visitar(j, M, i, orden, Indaristas, PesosAristas);
    }
}

void Visitar(int k, vector<vector<float>>& M, int i, int orden, vector<queue<char>>& Indaristas, vector<queue<float>>& PesosAristas){
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
            Indaristas[i].push(k+96);
            Indaristas[i].push(verticeM+96);
            PesosAristas[i].push(pesoM);
            Visitar(verticeM, M, i, orden, Indaristas, PesosAristas);
        }

    }while(ady);
}
