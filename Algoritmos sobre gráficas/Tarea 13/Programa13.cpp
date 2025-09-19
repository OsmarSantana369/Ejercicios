#include <iostream>
#include <locale>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un árbol (o bosque) generador de peso mínimo o máximo de una gráfica dada (Algoritmo de Kruskal).

Este programa primero solicita al usuario el orden y tamaño de la gráfica, y luego las aristas con sus respectivos pesos. Esto último con la función IngresaAristas(), la cual también almacena las aristas y sus pesos en el vector *Pesos* ordenado por peso, de menor a mayor. Luego, se imprime la matriz de adyacencia con la función ImprimeMatriz() y se pide al usuario si desea un árbol (bosque) generador mínimo o máximo. 

Después, se encuentran las componentes conexas de la gráfica con la función ComponentesConexas(), la cual utiliza la matriz de distancias para almacenar los vértices que se relacionan entre sí mediante trayectorias dentro de *Componentes* que es un vector de pilas.

Posteriormente, se busca el árbol (bosque) generador mínimo o máximo con la función Buscar(), la cual recorre las aristas ordenadas por peso y las va agregando a *Indaristas* si en la componente conexa a la que pertencen, el número de aristas agregadas es menor que el número de vértices disminuido en uno. La función finaliza cuando se han recorrido todas las aristas o cuando en cada componente conexa se han agregado el número de aristas igual al número de vértices menos uno.

Por último, se imprimen las aristas que inducen el árbol (bosque) generador de peso mínimo o máximo, así como el peso total de este.

Orden del algoritmo: O(potencia*orden^3 + tamano*NumCompCon)
*/

struct Arista{
    float Peso;
    int v1;
    int v2;
};

void IngresaAristas(int tamano, vector<vector<float>>& M, vector<Arista>& Pesos);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
bool Encontrar(stack<int> pila, int elemento);
void ComponentesConexas(vector<vector<float>>& M, stack<int>& visitado, vector<stack<int>>& Componentes);
void Buscar(vector<vector<float>>& M, vector<Arista>& Pesos, vector<stack<int>>& Componentes);

int orden, tamano, minax, NumCompCon = 0;
float PesoTotal = 0;
bool Reiniciar;
stack<int> visitado;
queue<char> Indaristas;

int main()
{
    setlocale(LC_ALL, "");

    do{
        cout << "Ingrese el orden de la gráfica: ";
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
    vector<Arista> Pesos(tamano+1);

    for(int i = 1; i <= tamano; i++){
        Pesos[i].Peso = 0;
        Pesos[i].v1 = 0;
        Pesos[i].v2 = 0;
    }

    IngresaAristas(tamano, M, Pesos);
    ImprimeMatriz(orden, M);

    do{
        cout << endl << "Inserte 0 si quiere obtener un árbol mínimo o 1 para un árbol máximo: ";
        cin >> minax;

        if(minax != 0 && minax != 1){
            cout << "Valor inválido." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    vector<stack<int>> Componentes(orden+1);

    ComponentesConexas(M, visitado, Componentes);
    Buscar(M, Pesos, Componentes);

    if(minax == 0)
        cout << endl << "El árbol (bosque) generador mínimo es la subgráfica inducida por las aristas: " << endl;
    else
        cout << endl << "El árbol (bosque) generador máximo es la subgráfica inducida por las aristas: " << endl;

    while(!Indaristas.empty()){
        char v1 = Indaristas.front();
        Indaristas.pop();
        char v2 = Indaristas.front();
        Indaristas.pop();

        cout << v1 << v2 << endl;
    }

    cout << endl << "El peso del árbol es: " << PesoTotal << endl << endl;

    return 0;
}

// Función para ingresar las adyacencias de la gráfica
void IngresaAristas(int tamano, vector<vector<float>>& M, vector<Arista>& Pesos){
    char v1, v2;
    float peso;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            cout << "Ingrese el peso de la arista: ";
            cin >> peso;
            M[ver1][ver2] = peso;
            M[ver2][ver1] = peso;

            Arista nuevaArista;
            nuevaArista.Peso = peso;
            nuevaArista.v1 = ver1;
            nuevaArista.v2 = ver2;

            for(int j = 1; j <= i; j++){
                if(Pesos[j].Peso == 0){
                    Pesos[j] = nuevaArista;
                    break;
                }
                else if(nuevaArista.Peso <= Pesos[j].Peso){
                    for(int k = i; k > j; k--){
                        Pesos[k] = Pesos[k-1];
                    }

                    Pesos[j] = nuevaArista;
                    break;
                }
            }

        } else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<float>>& M){
    cout << endl << endl;

    for(int i = 1; i <= orden; i++){
        cout << "   " << char(96 + i);
    }

    for(int i = 1; i <= orden; i++){
        cout << endl << char(96 + i) << "  ";
        for(int j = 1; j <= orden; j++){
            cout << M[i][j] << "   ";
        }
    }

    cout << endl;
}

// Función para elevar una matriz a una n-ésima potencia
vector<vector<float>> PotenciaMatriz(vector<vector<float>>& M, int potencia, int orden){
    vector<vector<float>> resultado(orden + 1, vector<float>(orden + 1, 0));
    vector<vector<float>> copia(orden + 1, vector<float>(orden + 1, 0));

    for(int i = 1; i <= orden; i++){
        for(int j = 1; j <= orden; j++){
            if(M[i][j] != 0)
                copia[i][j] = 1;
        }
    }

    for(int i = 1; i <= orden; i++){
        resultado[i][i] = 1;
    }

    for(int k = 1; k <= potencia; k++){
        vector<vector<float>> temp(orden + 1, vector<float>(orden + 1, 0));

        for(int i = 1; i <= orden; i++){
            for(int j = 1; j <= orden; j++){
                for(int l = 1; l <= orden; l++){
                    temp[i][j] += resultado[i][l] * copia[l][j];
                }
            }
        }

        resultado = temp;
    }

    return resultado;
}

// Función para obtener la matriz de distancias
vector<vector<float>> MatrizDistancia(vector<vector<float>>& M, int orden){
	vector<vector<float>> MDist(orden + 1, vector<float>(orden + 1, 0));

	for(int n = 1; n < orden; n++){
		vector<vector<float>> MPot = PotenciaMatriz(M, n, orden);

		for(int i = 1; i < orden; i++){
			for(int j = i+1; j <= orden; j++){
				if(MDist[i][j] == 0 && MPot[i][j] != 0){
					MDist[i][j] = n;
					MDist[j][i] = n;
				}
			}
		}
	}

	return MDist;
}

// Función para determinar si un elemento está en una pila
bool Encontrar(stack<int> pila, int elemento){
    stack<int> copia = pila;
    while(!copia.empty()){
        if(copia.top() == elemento)
            return true;

        copia.pop();
    }

    return false;
}

// Función para encontrar las componentes conexas de la gráfica
void ComponentesConexas(vector<vector<float>>& M, stack<int>& visitado, vector<stack<int>>& Componentes){
    vector<vector<float>>& MDist = MatrizDistancia(M, orden);

    for(int i = 1; i <= orden; i++){
        if(!Encontrar(visitado, i)){
            NumCompCon++;
            Componentes[NumCompCon].push(i);
            visitado.push(i);
            
            for(int j = i+1; j <= orden; j++){
                if(MDist[i][j] != 0){
                    Componentes[NumCompCon].push(j);
                    visitado.push(j);
                }
            }
        }
    }

    while(!visitado.empty())
        visitado.pop();
}

// Función para encontrar el árbol (bosque) generador mínimo o máximo
void Buscar(vector<vector<float>>& M, vector<Arista>& Pesos, vector<stack<int>>& Componentes){
    int ordenComp;
    vector<int> tamanoComp(NumCompCon+1, 0);
    vector<vector<float>> MDist = MatrizDistancia(M, orden);

    for(int i = 1; i <= tamano; i++){
        if(minax == 0){
            for(int j = 1; j <= NumCompCon; j++){
                if(Encontrar(Componentes[j], Pesos[i].v1) && tamanoComp[j] < Componentes[j].size()-1){
                    tamanoComp[j]++;
                    Indaristas.push(char(96 + Pesos[i].v1));
                    Indaristas.push(char(96 + Pesos[i].v2));
                    PesoTotal += Pesos[i].Peso;
                    break;
                }
            }
        } else{
            for(int j = 1; j <= NumCompCon; j++){
                if(Encontrar(Componentes[j], Pesos[tamano - i + 1].v1) && tamanoComp[j] <= Componentes[j].size()-1){
                    tamanoComp[j]++;
                    Indaristas.push(char(96 + Pesos[tamano - i + 1].v1));
                    Indaristas.push(char(96 + Pesos[tamano - i + 1].v2));
                    PesoTotal += Pesos[tamano - i + 1].Peso;
                    break;
                }
            }
        }
    }
}
