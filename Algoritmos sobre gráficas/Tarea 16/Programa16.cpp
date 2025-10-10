#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Programa que encuentra los vertices de corte, quitando un vértice a la vez y comparando el número de componetes conexas de la subgráfica respecto a la original.

Después, se imprime los vértices que son de corte y sus componentes conexas.

Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(vector<vector<float>>& M, vector<queue<int>>& Adyacencias);
void ImprimeMatriz(vector<vector<float>>& M);
void Visitar(int k, vector<queue<int>>& ComponentesCopia, vector<queue<int>>& Adyacencias);
queue<int> Eliminar(queue<int>& fila, int elemento);
vector<queue<int>> QuitarVertice(vector<queue<int>>& Adyacencias, int vertice);
void VerticesCorte(vector<queue<int>>& Adyacencias);
vector<queue<int>> Buscar(vector<queue<int>>& Adyacencias, int orden, int numeroComponentes);

int orden, tamano, numeroComponentes = 0;
bool Reiniciar;
queue<int> visitado;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la gráfica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inválido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;
    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tamaño de la gráfica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tamaño inválido para una gráfica simple." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;
    } while(Reiniciar);

    vector<vector<float>> M(orden + 1, vector<float>(orden + 1, 0));
	vector<queue<int>> Adyacencias(orden + 1);

    IngresaAristas(M, Adyacencias);
    ImprimeMatriz(M);

	vector<queue<int>> Componentes = Buscar(Adyacencias, orden, numeroComponentes);

    VerticesCorte(Adyacencias);
	
    cout << endl;

    return 0;
}

// Función para ingresar las adyacencias de la gráfica o digráfica
void IngresaAristas(vector<vector<float>>& M, vector<queue<int>>& Adyacencias){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            Adyacencias[ver1].push(ver2);
            M[ver2][ver1] = 1;
			Adyacencias[ver2].push(ver1);
        } else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
void ImprimeMatriz(vector<vector<float>>& M){
    cout << endl << endl << " ";

    for(int i = 1; i <= orden; i++)
        cout << setw(3) << char(96 + i);

    cout << endl;

    for(int i = 1; i <= orden; i++){
        cout << char(96 + i);

        for(int j = 1; j <= orden; j++)
            cout << setw(3) << M[i][j];

		cout << endl;
    }
    cout << endl;
}

bool Encontrar(queue<int> fila, int elemento){
    queue<int> copia = fila;

    while(!copia.empty()){
        if(copia.front() == elemento)
            return true;

        copia.pop();
    }
    return false;
}

queue<int> Eliminar(queue<int>& fila, int elemento){
    queue<int> resultado;

    while(!fila.empty()){
        if(fila.front() != elemento)
            resultado.push(fila.front());

        fila.pop();
    }
    return resultado;
}

vector<queue<int>> QuitarVertice(vector<queue<int>>& Adyacencias, int vertice){
    vector<queue<int>> resultado(Adyacencias.size());
    
    for(int i = 1; i < Adyacencias.size(); i++){
        if(i < vertice){
            resultado[i] = Adyacencias[i];
            resultado[i] = Eliminar(resultado[i], vertice);
        }
        else if(i > vertice){
            resultado[i] = Adyacencias[i+1];
            resultado[i] = Eliminar(resultado[i], vertice);
        }
    }
    
    return resultado;
}

void VerticesCorte(vector<queue<int>>& Adyacencias){
    int numeroComp = 0;
    
    for(int i = 1; i <= orden; i++){
        vector<queue<int>> Adyver = QuitarVertice(Adyacencias, i);
        vector<queue<int>> Componentesver = Buscar(Adyver, orden - 1, numeroComp);

        if(Componentesver.size() > numeroComponentes){
            cout << "El vértice " << char(96 + i) << " es de corte. A continuación se muestran las componentes de la gráfica sin el vértice" << char(96 + i);

            for(int j = 1; j <= Componentesver.size(); j++){
                cout << "La " << j << "° componente conexa tiene a los vértices: ";

                while(!Componentesver[j].empty()){
                    cout << char(96 + Componentesver[j].front()) << " ";
                    Componentesver[j].pop();
                }
                cout << endl;
            }
        } else{
            cout << "El vértice " << char(96 + i) << " no es de corte.";
        }
    }
}

vector<queue<int>> Buscar(vector<queue<int>>& Adyacencias, int orden, int numeroComponentes){
    vector<queue<int>> ComponentesCopia(orden + 1);

    for(int i = 1; i <= orden; i++){
        if(!Encontrar(visitado, i)){
            numeroComponentes++;
            Visitar(i, ComponentesCopia, Adyacencias);
        }
    }
    vector<queue<int>> Componentes(numeroComponentes + 1);

    for(int i = 1; i <= numeroComponentes; i++)
        Componentes[i] = ComponentesCopia[i];

    return Componentes;
}

void Visitar(int k, vector<queue<int>>& ComponentesCopia, vector<queue<int>>& Adyacencias){
    ComponentesCopia[numeroComponentes].push(k);
	visitado.push(k);

    for(int j = 1; j <= Adyacencias[k].size(); j++){
        int x = Adyacencias[k].front();
        Adyacencias[k].pop();

        if(!Encontrar(ComponentesCopia[numeroComponentes], x))
            Visitar(x, ComponentesCopia, Adyacencias);

        Adyacencias[k].push(x);
    }
}
