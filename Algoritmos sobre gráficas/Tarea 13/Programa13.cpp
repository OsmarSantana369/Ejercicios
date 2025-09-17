#include <iostream>
#include <locale>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un árbol (o bosque) generador de una gráfica dada (Algoritmo de bï¿½squeda en profundidad).

Se empieza por buscar el primer vï¿½rtice (alfabï¿½ticamente) que no ha sido visitado y se usa la función Visitar() para aï¿½adirlo a *visitado*,
mostrarlo en pantalla y buscar adyacencias que no esten en *visitado*.
    En caso de tener tales adyacencias, se aï¿½ade la arista correspondiente a *Indaristas* y se usa Visitar() con el vï¿½rtice encontrado.
    Este proceso se repite hasta que no haya mï¿½s adyacencias por visitar, momento en el cual se regresa a Buscar() para repetir el proceso.
El programa termina cuando todos los vértices estï¿½n en *visitado*.

Si la gráfica no es conexa, la función Buscar() se encargarï¿½ de encontrar todas las componentes conexas y generar un bosque generador en lugar de un árbol generador.

Por ï¿½ltimo, se imprimen las aristas que inducen el árbol (bosque) generador.

Orden del algoritmo: O(orden^2 + tamano)
*/

void IngresaAristas(int tamano, vector<vector<float>>& M);
void ImprimeMatriz(int orden, vector<vector<float>>& M);
void Buscar(vector<vector<float>>& M);
void Ordenar();

int orden, tamano, minax, contador;
float PesoTotal = 0;
bool Reiniciar;
stack<int> visitado;
queue<char> Indaristas;

struct Arista{
    float Peso;
    int v1;
    int v2;
};

queue<Arista> Pesos;

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

    IngresaAristas(tamano, M);
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

    Ordenar();

    while(!Pesos.empty()){
        cout << Pesos.front().Peso << "\t";
        Pesos.pop();
    }

    Buscar(M);

    if(minax == 0)
        cout << "El árbol (bosque) generador mínimo es la subgráfica inducida por las aristas: " << endl;
    else
        cout << "El árbol (bosque) generador máximo es la subgráfica inducida por las aristas: " << endl;



    cout << "El peso del árbol es: " << PesoTotal << endl;

    return 0;
}

// Función para ingresar las adyacencias de la gráfica
void IngresaAristas(int tamano, vector<vector<float>>& M){
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
            Pesos.push(nuevaArista);
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

// Función para ordenar *Pesos* de forma ascendente (si minax = 0) o descendente (si minax = 1)
void Ordenar(){
    queue<Arista> PesosPrima;
    Arista aux;

    do{
        contador = 0;

        while(!PesosPrima.empty())
            PesosPrima.pop();

        while(!Pesos.empty()){
            aux = Pesos.front();
            Pesos.pop();

            if(minax == 0){
                if(aux.Peso <= Pesos.front().Peso)
                    PesosPrima.push(aux);
                else{
                    PesosPrima.push(Pesos.front());
                    PesosPrima.push(aux);
                    Pesos.pop();
                    contador += 1;
                }
            } else{
                if(aux.Peso >= Pesos.front().Peso)
                    PesosPrima.push(aux);
                else{
                    PesosPrima.push(Pesos.front());
                    PesosPrima.push(aux);
                    Pesos.pop();
                    contador += 1;
                }
            }
        }

        Pesos = PesosPrima;
    } while(contador > 0);
}

// Función para elevar una matriz a una n-ésima potencia
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int potencia, int orden){
    vector<vector<int>> resultado(orden + 1, vector<int>(orden + 1, 0));

    for(int i = 1; i <= orden; i++){
        resultado[i][i] = 1;
    }

    for(int k = 1; k <= potencia; k++){
        vector<vector<int>> temp(orden + 1, vector<int>(orden + 1, 0));

        for(int i = 1; i <= orden; i++){
            for(int j = 1; j <= orden; j++){
                for(int l = 1; l <= orden; l++){
                    temp[i][j] += resultado[i][l] * M[l][j];
                }
            }
        }

        resultado = temp;
    }

    return resultado;
}

//Función para obtener la matriz de distancias
vector<vector<int>> MatrizDistancia(vector<vector<int>>& M, int orden){
	vector<vector<int>> MDist = M;

	for(int n = 2; n < orden; n++){
		vector<vector<int>> MPot = PotenciaMatriz(M, n, orden);

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

void Buscar(vector<vector<float>>& M){
    vector<vector<float>> CopiaM = M;

    for(int i = 1; i <= tamano; i++){

    }
}

