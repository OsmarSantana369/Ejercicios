#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes







Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M, vector<queue<int>>& Adyacencias);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
vector<queue<int>> Buscar(vector<vector<float>>& M);
void Visitar(int k, vector<vector<float>>& M, queue<queue<int>>& ComponentesCopia);

int orden, tamano, NumeroComponentes = 0;
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

    IngresaAristas(tamano, M, Adyacencias);
    ImprimeMatriz(orden, M);

	vector<queue<int>> Componentes = Buscar(M);

	if(NumeroComponentes == 1)
		cout << endl << "La gráfica es conexa." << endl;
	else{
		for(int i = 1; i <= NumeroComponentes; i++){
			cout << "La " << i << "° componente conexa tiene a los vértices: ";
			while(!Componentes[i].empty()){
				cout << char(96 + Componentes[i].front()) << " ";
				Componentes[i].pop();
			}
			cout << endl;
		}
	}

    return 0;
}

// Función para ingresar las adyacencias de la gráfica o digráfica
void IngresaAristas(int tamano, vector<vector<float>>& M, vector<queue<int>>& Adyacencias){
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
void ImprimeMatriz(int orden, vector<vector<float>>& M){
    cout << endl << endl << " ";

    for(int i = 1; i <= orden; i++){
        cout << setw(3) << char(96 + i);
    }
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

vector<queue<int>> Buscar(vector<vector<float>>& M){
    vector<queue<int>> ComponentesCopia(orden + 1);

    for(int i = 1; i <= orden; i++){
        if(!Encontrar(visitado, i)){
            NumeroComponentes++;
            Visitar(i, M, ComponentesCopia);
        }
    }

    vector<queue<int>> Componentes(NumeroComponentes + 1);

    for(int i = 1; i <= NumeroComponentes; i++)
        Componentes[i] = ComponentesCopia[i];

    return Componentes;
}

void Visitar(int k, vector<vector<float>>& M, vector<queue<int>>& ComponentesCopia){
    ComponentesCopia[NumeroComponentes].push(k);
	visitado.push(k);

    for(int x = 1; x <= orden; x++){
        if(M[k][x] != 0 && !Encontrar(ComponentesCopia[NumeroComponentes], x))
            Visitar(x, M, ComponentesCopia);
    }
}
