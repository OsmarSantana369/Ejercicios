#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa verifica si una gr�fica es bipartita, obtiene la partici�n de los v�rtices y los colorea de distinto color.

Para esto, se usa la funci�n Biparticion() que se fija en un v�rtice no visitado, lo marca como visitado y lo asigna a un conjunto de la partici�n. Luego, se usa una cola para recorrer sus adyacencias, asign�ndolos a la partici�n opuesta del v�rtice actual y marc�ndolos como visitados. Si se encuentra un v�rtice adyacente que ya ha sido visitado y est� en la misma partici�n que el v�rtice actual, se concluye que la gr�fica no es bipartita y se retorna una partici�n vac�a (para esto se usa la funci�n EsIndependiente()). Si se recorren todos los v�rtices sin encontrar tal caso, se retorna la partici�n obtenida. Como observaci�n, se usa al principio un for que recorre todos los v�rtices por si se tiene una gr�fica disconexa.

Al final, se imprime la matriz de adyacencia y la partici�n de colores si la gr�fica es bipartita.

Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias);
void ImprimeMatriz(vector<vector<int>>& M);
bool Encontrar(queue<int> fila, int elemento);
bool EsIndependiente(queue<int>& conjunto, vector<queue<int>>& adyacencias);
vector<queue<int>> Biparticion(vector<queue<int>>& adyacencias);

int orden, tamano;
bool Reiniciar;

int main()
{
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la gr�fica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inv�lido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tama�o de la gr�fica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tama�o inv�lido para una gr�fica simple." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    vector<vector<int>> M(orden + 1, vector<int>(orden + 1, 0));
    vector<queue<int>> adyacencias(orden + 1);

    IngresaAristas(M, adyacencias);
    ImprimeMatriz(M);
    vector<queue<int>> Particion = Biparticion(adyacencias);
    
	if(!Particion.empty()){
		cout << "La gr�fica es bipartita." << endl << endl;
		cout << "La coloraci�n de la gr�fica es: " << endl << endl;
		cout << "Azul: ";
		while(!Particion[0].empty()){
			cout << char(96 + Particion[0].front()) << " ";
			Particion[0].pop();
		}
		cout << endl << "Rojo: ";
		while(!Particion[1].empty()){
			cout << char(96 + Particion[1].front()) << " ";
			Particion[1].pop();
		}
		cout << endl << endl;
	} else
		cout << "La gr�fica no es bipartita." << endl << endl;

    return 0;
}

// Funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los v�rtices de la " << i << "� arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            adyacencias[ver1].push(ver2);
            M[ver2][ver1] = 1;
            adyacencias[ver2].push(ver1);
        }
        else{
            cout << "V�rtices fuera de rango. Int�ntelo nuevamente." << endl;
            i--;
        }
    }
}

// Funci�n para imprimir la matriz de adyacencia
void ImprimeMatriz(vector<vector<int>>& M){
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

// Funci�n para verificar si un entero est� almacenado en una cola
bool Encontrar(queue<int> fila, int elemento){
    queue<int> copia = fila;

    while(!copia.empty()){
        if(copia.front() == elemento)
            return true;

        copia.pop();
    }
    return false;
}

bool EsIndependiente(queue<int>& conjunto, vector<queue<int>>& adyacencias){
	queue<int> copia = conjunto;

	while(!copia.empty()){
		int actual = copia.front();
		copia.pop();

		queue<int> adyacentes = adyacencias[actual];
		while(!adyacentes.empty()){
			int vecino = adyacentes.front();
			adyacentes.pop();

			if(Encontrar(conjunto, vecino))
				return false;
		}
	}
	return true;
}

//Funci�n que obtiene la Biparticion de la gr�fica
vector<queue<int>> Biparticion(vector<queue<int>>& adyacencias){
	vector<queue<int>> particion(2);
	vector<bool> visitados(orden + 1, false);
	queue<int> cola;

	for(int i = 1; i <= orden; i++){
		if(!visitados[i]){
			cola.push(i);
			visitados[i] = true;
			particion[0].push(i);

			while(!cola.empty()){
				int actual = cola.front();
				cola.pop();

				int particionActual = -1;
				for(int c = 0; c < 2; c++){
					if(Encontrar(particion[c], actual)){
						particionActual = c;
						break;
					}
					if(particionActual != -1)
						break;
				}

				queue<int> adyacentes = adyacencias[actual];
				while(!adyacentes.empty()){
					int vecino = adyacentes.front();
					adyacentes.pop();

					if(!visitados[vecino]){
						visitados[vecino] = true;
						cola.push(vecino);
						particion[1 - particionActual].push(vecino);
					}
				}

				if(!EsIndependiente(particion[0], adyacencias) || !EsIndependiente(particion[1], adyacencias))
					return {};
			}
		}
	}
	return particion;
}
