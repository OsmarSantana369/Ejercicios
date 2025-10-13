#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa obtiene la matriz de distancias de una gráfica y la imprime.

Para esto la matriz de distancias se obtiene igualandola con la matriz de adyacencia, ya que todos los vértices adyacentes tienen distancia 1 entre sí. Después, se eleva la matriz de adyacencia a las potencias 2, 3, ..., *orden*-1 (pues las trayectorias tienen longitud a lo más *orden*-1) y se revisa si en la matriz resultante hay entradas no nulas en posiciones donde la matriz de distancias aún tiene un 0 (esto indica que ese par de vértices no ha tenido algún camino que los conecte hasta antes de la potencia actual). Si se encuentra una entrada no nula en la matriz elevada, se actualiza la matriz de distancias con el valor de la potencia actual, que representa la distancia entre esos vértices.

Orden del algoritmo: O(tamano + potencia*orden^3)
*/

void IngresaAristas(vector<vector<int>>& M, vector<queue<int>>& adyacencias);
void ImprimeMatriz(vector<vector<int>>& M);
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int n);
vector<vector<int>> MatrizDistancia(vector<vector<int>>& M);
int Minimo(vector<int>& vector);
int Maximo(vector<int>& vector);
queue<int> Buscar(vector<int>& vec, int valor);

int orden, tamano;
bool Reiniciar;

int main()
{
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
    vector<int> excentricidades(orden, 0);

    IngresaAristas(M, adyacencias);
    ImprimeMatriz(M);
    
    vector<vector<int>> MDist = MatrizDistancia(M);

    for(int i = 1; i <= orden; i++){
        excentricidades[i-1] = Maximo(MDist[i]);
    }

    cout << "Las excentricidades de cada vértice son:" << endl;

    for(int i = 1; i <= orden; i++){
        cout << "e(" << char(96+i) << ") = " << excentricidades[i-1] << endl;
    }
    
    cout << endl << "El radio de la gráfica es: " << Minimo(excentricidades) << endl;
    cout << "El diámetro de la gráfica es: " << Maximo(excentricidades) << endl;
    cout << "El centro de la gráfica es: {";

    queue<int> centro = Buscar(excentricidades, Minimo(excentricidades));

    while(centro.size() > 1){
        cout << char(97 + centro.front()) << ", ";
        centro.pop();
    }
    cout << char(97 + centro.front()) << "}" << endl << endl;

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
        }
        else{
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

// Función para elevar una matriz a una n-ésima potencia
vector<vector<int>> PotenciaMatriz(vector<vector<int>>& M, int potencia, int orden){
    vector<vector<int>> resultado(orden + 1, vector<int>(orden + 1, 0));

    for (int i = 1; i <= orden; i++)
        resultado[i][i] = 1;

    for (int k = 1; k <= potencia; k++){
        vector<vector<int>> temp(orden + 1, vector<int>(orden + 1, 0));

        for (int i = 1; i <= orden; i++){
            for (int j = 1; j <= orden; j++){
                for (int l = 1; l <= orden; l++)
                    temp[i][j] += resultado[i][l] * M[l][j];
            }
        }
        resultado = temp;
    }
    return resultado;
}

// Función para obtener la matriz de distancias
vector<vector<int>> MatrizDistancia(vector<vector<int>>& M){
    vector<vector<int>> MDist = M;

    for (int n = 2; n < orden; n++){
        vector<vector<int>> MPot = PotenciaMatriz(M, n, orden);

        for (int i = 1; i < orden; i++){
            for (int j = i+1; j <= orden; j++){
                if (MDist[i][j] == 0 && MPot[i][j] != 0){
                    MDist[i][j] = n;
                    MDist[j][i] = n;
                }
            }
        }
    }

    return MDist;
}

// Función que obtiene el mínimo de un vector
int Minimo(vector<int>& vector){
    int resultado = vector[0];

    for(int i = 1; i < vector.size(); i++){
        if(resultado > vector[i])
            resultado = vector[i];
    }
    return resultado;
}

// Función que obtiene el máximo de un vector
int Maximo(vector<int>& vector){
    int resultado = vector[0];

    for(int i = 1; i < vector.size(); i++){
        if(resultado < vector[i])
            resultado = vector[i];
    }
    return resultado;
}

// Función que devuelve los índices en los que se encuentra un valor dado dentro de un vector
queue<int> Buscar(vector<int>& vec, int valor){
    vector<int> copia = vec;
    queue<int> indices;
    
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == valor){
            indices.push(i);
        }
    }
    return indices;
}