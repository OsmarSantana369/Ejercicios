#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa busca una buena coloraci�n de una gr�fica dada.

Para esto, se obtiene el v�rtice de mayor grado no coloreado y se le asigna el primer color. Luego, se busca la vecindad abierta de los v�rtices ya coloreados y se intenta colorear estos v�rtices con los colores ya existentes, verificando que no sean adyacentes a ning�n v�rtice ya coloreado con ese color. Si no es posible colorear alg�n v�rtice de la vecindad con los colores existentes, se crea un nuevo color y se le asigna el primer v�rtice de la vecindad a este nuevo color. Este proceso se repite hasta que todos los v�rtices hayan sido coloreados. En caso de que queden v�rtices aislados, estos se colorean con el primer color. Y en caso de que la gr�fica sea disconexa, se repite el proceso para el resto de las componentes conexas.

Finalmente, se imprime la coloraci�n obtenida.

Orden del algoritmo: O(colores.size() + tamano + orden^2)
*/

void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias);
void ImprimeMatriz(vector<vector<int>>& M);
bool Encontrar(queue<int> fila, int elemento);
queue<int> VecindadAbierta(queue<int>& conjunto, vector<queue<int>>& adyacencias);
queue<int> FusionarColas(vector<queue<int>>& colas);
queue<int> Eliminar(queue<int> fila, int elemento);
vector<queue<int>> ObtenerColoracion(vector<queue<int>>& adyacencias);

int orden, tamano;
bool Reiniciar;

int main(){
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
    vector<queue<int>> colores = ObtenerColoracion(adyacencias);

	cout << "La coloraci�n obtenida de la gr�fica es: " << endl << endl;

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
        } else{
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

// Funci�n que obtiene la vecindad abierta no coloreada de un conjunto de v�rtices
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

// Funci�n que une los elementos de un vector de colas en una sola
queue<int> FusionarColas(vector<queue<int>>& colas){
	queue<int> resultado;

	for(int i = 0; i < colas.size(); i++){
		queue<int> copia = colas[i];

		while(!copia.empty()){
			resultado.push(copia.front());
			copia.pop();
		}
	}
	return resultado;
}

// Funci�n que elimina un elemento de una cola
queue<int> Eliminar(queue<int> fila, int elemento){
	queue<int> resultado;

	while(!fila.empty()){
		if(fila.front() != elemento)
			resultado.push(fila.front());

		fila.pop();
	}
	return resultado;
}

// Funci�n que obtiene un vector de colas de v�rtices posicionados por color
vector<queue<int>> ObtenerColoracion(vector<queue<int>>& adyacencias){
	vector<queue<int>> coloracion;       // Vector de colas para almacenar la coloraci�n
	vector<bool> coloreados(orden + 1, false);       // Vector para rastrear los v�rtices coloreados
	bool todosColoreados = false;
	
	while(!todosColoreados){
		int gradoMaximo = 0;

		// Se busca el v�rtice con el mayor grado no coloreado
		for(int i = 1; i <= orden; i++){
			if(adyacencias[gradoMaximo].size() < adyacencias[i].size() && !coloreados[i])
				gradoMaximo = i;
		}
		if(gradoMaximo != 0){
			if(coloracion.empty())
				coloracion.push_back(queue<int>());

			coloracion[0].push(gradoMaximo);
			coloreados[gradoMaximo] = true;
			int vecinos = 0;

			do{
				// Se obtiene la vecindad abierta de los v�rtices ya coloreados
				queue<int> vecindad = VecindadAbierta(FusionarColas(coloracion), adyacencias);
				vecinos = vecindad.size();

				// Se intenta colorear la vecindad con los colores ya existentes
				for(int i = 0; i < coloracion.size(); i++){
					queue<int> copia = vecindad;       // Se crea una copia de la vecindad para recorrer los v�rtices de la vencindad y en caso de ser coloreados, eliminarlos de la vecindad original

					while(!copia.empty()){
						int candidato = copia.front();
						copia.pop();
						
						bool puedeColorear = true;
						queue<int> adyacentes = adyacencias[candidato];

						// Se verifica que el candidato no sea adyacente a ning�n v�rtice ya coloreado con el color actual
						while(!adyacentes.empty()){
							int vecino = adyacentes.front();
							adyacentes.pop();

							if(Encontrar(coloracion[i], vecino)){
								puedeColorear = false;
								break;
							}
						}
						if(puedeColorear){
							coloracion[i].push(candidato);
							coloreados[candidato] = true;
							vecindad = Eliminar(vecindad, candidato);
						}
					}
				}
				// Si quedaron v�rtices sin colorear en la vecindad, se crea un nuevo color y se colorea el primer v�rtice de la vecindad
				if(!vecindad.empty()){
					coloracion.push_back(queue<int>());
					coloracion.back().push(vecindad.front());
					coloreados[vecindad.front()] = true;
				}
			} while(vecinos > 0);       // Se repite hasta que no queden v�rtices sin colorear en la componente conexa
		} else{ // Si no quedan v�rtices con adyacencias, se colorean los v�rtices aislados con el primer color
			if(coloracion.empty())
				coloracion.push_back(queue<int>());
				
			for(int i = 1; i <= orden; i++){
				if(!coloreados[i]){
					coloracion[0].push(i);
					coloreados[i] = true;
				}
			}
		}
		// Se verifica si todos los v�rtices han sido coloreados
		todosColoreados = true;

		for(int i = 1; i <= orden; i++){
			if(!coloreados[i]){
				todosColoreados = false;
				break;
			}
		}
	}
	return coloracion;
}
