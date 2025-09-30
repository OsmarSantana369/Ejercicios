#include <iostream>
#include <locale>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
Osmar Dominique Santana Reyes

Este programa encuentra un �rbol (o bosque) generador de peso m�nimo o m�ximo de una gr�fica dada (Algoritmo de Kruskal).

Este programa primero solicita al usuario el orden y tama�o de la gr�fica, y luego las aristas con sus respectivos pesos. Esto �ltimo con la funci�n IngresaAristas(), la cual tambi�n almacena las aristas y sus pesos en el vector *Pesos* ordenado por peso, de menor a mayor. Luego, se imprime la matriz de adyacencia con la funci�n ImprimeMatriz() y se pide al usuario si desea un �rbol (bosque) generador m�nimo o m�ximo. 

Despu�s, se encuentran las componentes conexas de la gr�fica con la funci�n ComponentesConexas(), la cual utiliza la matriz de distancias para almacenar los v�rtices que se relacionan entre s� mediante trayectorias dentro de *Componentes* que es un vector de pilas.

Posteriormente, se busca el �rbol (bosque) generador m�nimo o m�ximo con la funci�n Buscar(), la cual recorre las aristas ordenadas por peso y las va agregando a *Indaristas* si en la componente conexa a la que pertencen, el n�mero de aristas agregadas es menor que el n�mero de v�rtices disminuido en uno. La funci�n finaliza cuando se han recorrido todas las aristas o cuando en cada componente conexa se han agregado el n�mero de aristas igual al n�mero de v�rtices menos uno.

Por �ltimo, se imprimen las aristas que inducen el �rbol (bosque) generador de peso m�nimo o m�ximo, as� como el peso total de este.

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
        cout << "Ingrese el orden de la gr�fica: ";
        cin >> orden;

        if(orden <= 0){
            cout << "Orden inv�lido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    do{
        cout << endl << "Ingrese el tama�o de la gr�fica: ";
        cin >> tamano;

        if(tamano < 0 || tamano > orden*(orden - 1)/2){
            cout << "Tama�o inv�lido para una gr�fica simple." << endl;
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
        cout << endl << "Inserte 0 si quiere obtener un �rbol m�nimo o 1 para un �rbol m�ximo: ";
        cin >> minax;

        if(minax != 0 && minax != 1){
            cout << "Valor inv�lido." << endl;
            Reiniciar = true;
        } else
            Reiniciar = false;

    } while(Reiniciar);

    vector<stack<int>> Componentes(orden+1);

    ComponentesConexas(M, visitado, Componentes);
    Buscar(M, Pesos, Componentes);

    if(minax == 0)
        cout << endl << "El �rbol (bosque) generador m�nimo es la subgr�fica inducida por las aristas: " << endl;
    else
        cout << endl << "El �rbol (bosque) generador m�ximo es la subgr�fica inducida por las aristas: " << endl;

    while(!Indaristas.empty()){
        char v1 = Indaristas.front();
        Indaristas.pop();
        char v2 = Indaristas.front();
        Indaristas.pop();

        cout << v1 << v2 << endl;
    }

    cout << endl << "El peso del �rbol es: " << PesoTotal << endl << endl;

    return 0;
}

// Funci�n para ingresar las adyacencias de la gr�fica
void IngresaAristas(int tamano, vector<vector<float>>& M, vector<Arista>& Pesos){
    char v1, v2;
    float peso;

    for(int i = 1; i <= tamano; i++){
        cout << endl << "Inserte los v�rtices de la " << i << "� arista: ";
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
            cout << "V�rtices fuera de rango. Int�ntelo nuevamente." << endl;
            i--;
        }
    }
}

// Funci�n para imprimir la matriz de adyacencia
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

// Funci�n para elevar una matriz a una n-�sima potencia
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

// Funci�n para obtener la matriz de distancias
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

// Funci�n para determinar si un elemento est� en una pila
bool Encontrar(stack<int> pila, int elemento){
    stack<int> copia = pila;
    while(!copia.empty()){
        if(copia.top() == elemento)
            return true;

        copia.pop();
    }

    return false;
}

// Funci�n para encontrar las componentes conexas de la gr�fica
void ComponentesConexas(vector<vector<float>>& M, stack<int>& visitado, vector<stack<int>>& Componentes){
    vector<vector<float>> MDist = MatrizDistancia(M, orden);

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

// Funci�n para encontrar el �rbol (bosque) generador m�nimo o m�ximo
void Buscar(vector<vector<float>>& M, vector<Arista>& Pesos, vector<stack<int>>& Componentes){
    vector<int> tamanoArbolComp(NumCompCon+1, 0);
    vector<stack<int>> vertVisitados(NumCompCon+1);

    for(int i = 1; i <= tamano; i++){
        for(int j = 1; j <= NumCompCon; j++){
            if(minax == 0){
                if(vertVisitados[j].empty() && Encontrar(Componentes[j], Pesos[i].v1)){
                    vertVisitados[j].push(Pesos[i].v1);
                    vertVisitados[j].push(Pesos[i].v2);
                }

                if(Encontrar(Componentes[j], Pesos[i].v1) && tamanoArbolComp[j] + 1 == vertVisitados[j].size()-1){
                    tamanoArbolComp[j]++;
                    Indaristas.push(char(96 + Pesos[i].v1));
                    Indaristas.push(char(96 + Pesos[i].v2));
                    PesoTotal += Pesos[i].Peso;

                    if(!Encontrar(vertVisitados[j], Pesos[i].v1))
                        vertVisitados[j].push(Pesos[i].v1);

                    if(!Encontrar(vertVisitados[j], Pesos[i].v2))
                        vertVisitados[j].push(Pesos[i].v2);

                    break;
                }
            } else{
                if(vertVisitados[j].empty() && Encontrar(Componentes[j], Pesos[tamano - i + 1].v1)){
                    vertVisitados[j].push(Pesos[tamano - i + 1].v1);
                    vertVisitados[j].push(Pesos[tamano - i + 1].v2);
                }

                if(Encontrar(Componentes[j], Pesos[tamano - i + 1].v1) && tamanoArbolComp[j] == vertVisitados[j].size()-1){
                    tamanoArbolComp[j]++;
                    Indaristas.push(char(96 + Pesos[tamano - i + 1].v1));
                    Indaristas.push(char(96 + Pesos[tamano - i + 1].v2));
                    PesoTotal += Pesos[tamano - i + 1].Peso;

                    if(Encontrar(vertVisitados[j], Pesos[tamano - i + 1].v1))
                        vertVisitados[j].push(Pesos[tamano - i + 1].v1);

                    if(Encontrar(vertVisitados[j], Pesos[tamano - i + 1].v2))
                        vertVisitados[j].push(Pesos[tamano - i + 1].v2);

                    break;
                }
            }
        }
    }
}
