#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa obtiene la matriz de distancias de una gr�fica y la imprime.

Para esto la matriz de distancias se obtiene igualandola con la matriz de adyacencia, ya que todos los v�rtices adyacentes tienen distancia 1 entre s�. Despu�s, se eleva la matriz de adyacencia a las potencias 2, 3, ..., *orden*-1 (pues las trayectorias tienen longitud a lo m�s *orden*-1) y se revisa si en la matriz resultante hay entradas no nulas en posiciones donde la matriz de distancias a�n tiene un 0 (esto indica que ese par de v�rtices no ha tenido alg�n camino que los conecte hasta antes de la potencia actual). Si se encuentra una entrada no nula en la matriz elevada, se actualiza la matriz de distancias con el valor de la potencia actual, que representa la distancia entre esos v�rtices.

Orden del algoritmo: O(tamano + potencia*orden^3)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int n);
vector<vector<int>> MatrizDistancia(vector<vector<int>>& M, int orden);

int main()
{
    setlocale(LC_ALL, "");
    int orden, tamano;

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

    vector<vector<int>> M(orden+1, vector<int>(orden+1, 0));

    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    vector<vector<int>> M_distancia = MatrizDistancia(M, orden);
	cout<<endl<<"La matriz de distancias es:"<<endl;
    ImprimeMatriz(orden, M_distancia);
	cout<<endl;

    return 0;
}

// Funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(int tamano, vector<vector<int>>& M)
{
    char v1, v2;
    for (int i = 1; i <= tamano; i++) {
        cout<<"\nInserte los v�rtices de la "<<i<<"� arista: ";
        cin>>v1>>v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if (ver1 > 0 && ver1 <= M.size() && ver2 > 0 && ver2 <= M.size()) {
            M[ver1][ver2] = 1;
            M[ver2][ver1] = 1;
        } else {
            cout<<"V�rtices fuera de rango. Int�ntelo nuevamente.\n";
            i--;
        }
    }
}

// Funci�n para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<int>>& M)
{
    cout<<"\n ";
    for (int i = 1; i <= orden; i++) {
        cout<<"   "<<char(96 + i);
    }

    for (int i = 1; i <= orden; i++) {
        cout<<"\n"<<char(96 + i)<<"   ";
        for (int j = 1; j <= orden; j++) {
            cout<<M[i][j]<<"   ";
        }
    }
    cout<<endl;
}

//Funci�n para elevar una matriz a una n-�sima potencia
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int potencia, int orden){
    vector<vector<int>> resultado(orden + 1, vector<int>(orden + 1, 0));

    // Inicializar resultado como la matriz identidad
    for (int i = 1; i <= orden; i++) {
        resultado[i][i] = 1;
    }

    // Multiplicar la matriz por s� misma n veces
    for (int k = 1; k <= potencia; k++) {
        vector<vector<int>> temp(orden + 1, vector<int>(orden + 1, 0));

        for (int i = 1; i <= orden; i++) {
            for (int j = 1; j <= orden; j++) {
                for (int l = 1; l <= orden; l++) {
                    temp[i][j] += resultado[i][l] * M[l][j];
                }
            }
        }
		
        resultado = temp;
    }

    return resultado;
}

//Funci�n para obtener la matriz de distancias
vector<vector<int>> MatrizDistancia(vector<vector<int>>& M, int orden){
	vector<vector<int>> MDist = M;

	for (int n = 2; n < orden; n++) {
		vector<vector<int>> MPot = PotenciaMatriz(M, n, orden);

		for (int i = 1; i < orden; i++) {
			for (int j = i+1; j <= orden; j++) {
				if (MDist[i][j] == 0 && MPot[i][j] != 0) {
					MDist[i][j] = n;
					MDist[j][i] = n;
				}
			}
		}
	}

	return MDist;
}
