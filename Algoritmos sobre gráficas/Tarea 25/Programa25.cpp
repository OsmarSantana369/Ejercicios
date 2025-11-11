#include <iostream>
#include <locale>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa verifica si una digráfica dada es débil, unilateral o fuertemente conexa.

Para esto, se obtiene la matriz de distancias mínimas entre los vértices. Si para cada par de vértices existe un camino en ambas direcciones, la digráfica es fuertemente conexa. Si para cada par de vértices existe un camino en al menos una dirección y no en ambas, la digráfica es a lo más unilateralmente conexa. Si alguna de las dos anteriores no se cumple, se comprueba si al convertir la digráfica en gráfica (haciendo las aristas no dirigidas) es conexa; si es así, la digráfica es débilmente conexa. En caso contrario, la digráfica no es conexa.

Orden del algoritmo: O(tamano + orden^2)
*/

void IngresaAristas(int tamano, vector<vector<int>>& M);
void ImprimeMatriz(int orden, vector<vector<int>>& M);
vector<int> Encontrar(vector<vector<int>>& M, int elemento);
vector<vector<int>> ObtenerDistancias(vector<vector<int>>& M);
int TipoConexidad(vector<vector<int>>& MDist);

int orden, tamano, infinito = INT_MAX;
int grafdigraf;
bool Reiniciar;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese el orden de la digráfica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inválido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tamaño de la digráfica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)){
            cout << "Tamaño inválido para una digráfica simple." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    vector<vector<int>> M(orden + 1, vector<int>(orden + 1, 0));
    
    IngresaAristas(tamano, M);
    ImprimeMatriz(orden, M);

    int tipo = TipoConexidad(M);

    switch(tipo){
        case 0:
            cout << "La digráfica no es conexa." << endl;
            break;
        case 1:
            cout << "La digráfica es débilmente conexa." << endl;
            break;
        case 2:
            cout << "La digráfica es unilateralmente conexa." << endl;
            break;
        case 3:
            cout << "La digráfica es fuertemente conexa." << endl;
            break;
    }
    cout << endl;
    return 0;
}

// Función para ingresar las adyacencias de la digráfica
void IngresaAristas(int tamano, vector<vector<int>>& M){
    char v1, v2;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los vértices de la " << i << "° flecha: ";
        cin >> v1 >> v2;

        int ver1 = tolower(v1) - 96;
        int ver2 = tolower(v2) - 96;

        if(ver1 > 0 && ver1 <= orden && ver2 > 0 && ver2 <= orden){
            M[ver1][ver2] = 1;
        } else{
            cout << "Vértices fuera de rango. Inténtelo nuevamente." << endl;
            i--;
        }
    }
}

// Función para imprimir la matriz de adyacencia
void ImprimeMatriz(int orden, vector<vector<int>>& M){
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

//Función que comprueba si hay un elemento en una matriz y devuelve el índice de su posición
vector<int> Encontrar(vector<vector<int>>& M, int elemento){
    for(int i = 1; i <= orden; i++){
        for(int j = 1; j <= orden; j++){
            if(M[i][j] == elemento)
                return {i, j};
        }
    }
    return {};
}

// Función para obtener las distancias mínimas entre los vértices
vector<vector<int>> ObtenerDistancias(vector<vector<int>>& M){
    queue<int> aux;
    vector<vector<int>> MDist(orden + 1, vector<int>(orden + 1, infinito));

    for(int i = 1; i <= orden; i++){
        MDist[i][i] = 0;
        aux.push(i);

        while(!aux.empty()){
            int actual = aux.front();
            aux.pop();

            for(int j = 1; j <= orden; j++){
                if(M[actual][j] != 0 && MDist[i][actual] + M[actual][j] < MDist[i][j]){
                    MDist[i][j] = MDist[i][actual] + M[actual][j];
                    aux.push(j);
                }
            }
        }
    }
    return MDist;
}

// Función que obtiene el tipo de conexidad de la digráfica
int TipoConexidad(vector<vector<int>>& M){
    bool debil = true, unilateral = true, fuerte = true;
    vector<vector<int>> MDist = ObtenerDistancias(M);

    do{
        vector<int> indices = Encontrar(MDist, infinito);
        if(indices.size() != 0){
            fuerte = false;
            int i = indices[0];
            int j = indices[1];

            if(MDist[j][i] == infinito){
                unilateral = false;
                vector<vector<int>> Mcopia = M;

                for(int k = 1; k <= orden; k++){
                    for(int l = 1; l <= orden; l++){
                        if(Mcopia[k][l] != 0)
                            Mcopia[l][k] = Mcopia[k][l];
                    }
                }
                if(Encontrar(ObtenerDistancias(Mcopia), infinito).size() != 0){
                    debil = false;
                    break;
                }
            } else
                MDist[i][j] = -1;
        }
    } while (Encontrar(MDist, infinito).size() != 0 && unilateral);

    if(fuerte)
        return 3; // Fuertemente conexa
    if(unilateral)
        return 2; // Unilateralmente conexa
    if(debil)
        return 1; // Débilmente conexa

    return 0; // No conexa
}
