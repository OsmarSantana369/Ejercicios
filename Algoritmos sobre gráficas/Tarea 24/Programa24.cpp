#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa busca una buena coloración de una gráfica dada.

Para esto, se obtiene el vértice de mayor grado no coloreado y se le asigna el primer color. Luego, se toma el siguiente vértice de mayor grado y si está en la vecindad abierta del conjunto de vértices ya coloreados con el primer color, se le asigna otro color. En caso contrario, se le asigna el mismo color. Este proceso se repite hasta que todos los vértices estén coloreados.

Finalmente, se imprime la coloración obtenida.

Orden del algoritmo: O(coloracion.size() + tamano + orden^2)
*/
struct grado;

void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias);
void ImprimeMatriz(vector<vector<int>>& M);
bool Encontrar(queue<int> cola, int elemento);
queue<queue<int>> ObtenerGrados(vector<queue<int>>& adyacencias);
queue<int> VecindadAbierta(queue<int>& conjunto, vector<queue<int>>& adyacencias);
vector<queue<int>> ObtenerColoracion(vector<queue<int>>& adyacencias);

int orden, tamano;
bool Reiniciar;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la gráfica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inválido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tamaño de la gráfica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tamaño inválido para una gráfica simple." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

    vector<vector<int>> M(orden + 1, vector<int>(orden + 1, 0));
    vector<queue<int>> adyacencias(orden + 1);

    IngresaAristas(M, adyacencias);
    ImprimeMatriz(M);
    vector<queue<int>> colores = ObtenerColoracion(adyacencias);

	cout << "La coloración obtenida de la gráfica es: " << endl << endl;

	for(int i = 0; i < colores.size(); i++){
		cout << "Color " << i + 1 << ": ";
		queue<int> copia = colores[i];

		while(!copia.empty()){
			cout << char(96 + copia.front()) << " ";
			copia.pop();
		}
		cout << endl;
	}
	cout << endl;

    return 0;
}

// Función para ingresar las adyacencias de la gráfica
void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° arista: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
            adyacencias[ver1].push(ver2);
            M[ver2][ver1] = 1;
            adyacencias[ver2].push(ver1);
        } else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
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

// Función para verificar si un entero está almacenado en una cola
bool Encontrar(queue<int> cola, int elemento){
    queue<int> copia = cola;

    while(!copia.empty()){
        if(copia.front() == elemento)
            return true;

        copia.pop();
    }
    return false;
}

// Función que crea una cola de colas con vértices del mismo grado y ordenadas por grado de mayor a menor
queue<queue<int>> ObtenerGrados(vector<queue<int>>& adyacencias){
    vector<queue<int>> grados(orden);
    queue<queue<int>> gradosOrdenados;

    for(int i = 1; i <= orden; i++)
        grados[adyacencias[i].size()].push(i);
    
    // Ordenar los grados de mayor a menor
    for(int i = orden-1; i >= 0; i--){
        if(!grados[i].empty())
            gradosOrdenados.push(grados[i]);
    }
    return gradosOrdenados;
}

// Función que obtiene la vecindad abierta de un conjunto de vértices
queue<int> VecindadAbierta(queue<int>& conjunto, vector<queue<int>>& adyacencias){
	queue<int> vecindad;
	queue<int> copia = conjunto;

	while(!copia.empty()){
		queue<int> adyacentes = adyacencias[copia.front()];

		while(!adyacentes.empty()){
			int vecino = adyacentes.front();
			adyacentes.pop();

			if(!Encontrar(conjunto, vecino) && !Encontrar(vecindad, vecino))
				vecindad.push(vecino);
		}
		copia.pop();
	}
	return vecindad;
}

// Función que obtiene un vector de colas de vértices posicionados por color
vector<queue<int>> ObtenerColoracion(vector<queue<int>>& adyacencias){
	vector<queue<int>> coloracion;       // Vector de colas para almacenar la coloración
	queue<queue<int>> grados = ObtenerGrados(adyacencias);
    coloracion.push_back(queue<int>());
    coloracion[0].push(grados.front().front());
    grados.front().pop();

    if(grados.front().empty())
        grados.pop();

	while(!grados.empty()){
		while(!grados.front().empty()){
            int vertice = grados.front().front();
            grados.front().pop();

            for(int i = 0; i < coloracion.size(); i++){
                if(!Encontrar(VecindadAbierta(coloracion[i], adyacencias), vertice)){
                    coloracion[i].push(vertice);
                    break;
                } else if(i == coloracion.size() - 1){
                    queue<int> nuevoColor;
                    nuevoColor.push(vertice);
                    coloracion.push_back(nuevoColor);
                    break;
                }
            }
        }
        grados.pop();
    }
    return coloracion;
}
