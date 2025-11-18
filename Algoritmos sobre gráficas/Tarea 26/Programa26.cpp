#include <iostream>
#include <locale>
#include <vector>
#include <cctype>
#include <queue>
#include <iomanip>
using namespace std;

/*
Osmar Dominique Santana Reyes

Programa que pide una tabla de preferencias sobre el interés tanto de hombres como de mujeres y encuentra un emparejamiento óptimo.

parejas del algoritmo: O(tamano + parejas^2)
*/

void IngresaPreferencias(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres);
void ImprimeMatriz(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres);

int parejas;
bool Reiniciar;

struct Emparejamiento{
    int hombre;
    int mujer;
    int correspondencia;
};

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << endl << "Ingrese la cantidad de parejas (el número de mujeres debe ser igual al número de hombres): ";
        cin >> parejas;

        if(parejas <= 0){
            cout << "Número de parejas inválido. Debe ser mayor que 0." << endl;
            Reiniciar = true;
        }
        else
            Reiniciar = false;
    } while(Reiniciar);

	vector<vector<int>> Mujeres(parejas + 1, vector<int>(parejas + 1, 0));
	vector<vector<int>> Hombres(parejas + 1, vector<int>(parejas + 1, 0));

    IngresaPreferencias(Mujeres, Hombres);
    ImprimeMatriz(Mujeres, Hombres);


    return 0;
}

// Función para ingresar las preferencias de las mujeres y hombres
void IngresaPreferencias(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres){
    // Mujeres
    cout << endl << endl << "Ingreso de preferencias de las mujeres:" << endl;

    for(int j = 1; j <= parejas; j++){
		for(int i = 1; i <= parejas; i++){
			cout << endl << "Inserte la " << i << "° preferencia (número del hombre) de la mujer " << char(96 + j) << ": ";
			cin >> Mujeres[i][j];

			if(Mujeres[i][j] < 0 || Mujeres[i][j] > parejas){
				cout << "Número fuera de rango. Inténtelo nuevamente." << endl;
				i--;
			}
		}
    }

    // Hombres
    cout << endl << endl << "Ingreso de preferencias de los hombres:" << endl;

    for(int j = 1; j <= parejas; j++){
		for(int i = 1; i <= parejas; i++){
			cout << endl << "Inserte la " << i << "° preferencia (número de la mujer) del hombre " << char(96 + j) << ": ";
			cin >> Hombres[i][j];

			if(Hombres[i][j] < 0 || Hombres[i][j] > parejas){
				cout << "Número fuera de rango. Inténtelo nuevamente." << endl;
				j--;
			}
		}
    }
}

// Función para imprimir las matrices de preferencias
void ImprimeMatriz(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres){
	// Mujeres
    cout << endl << endl << "Matriz de preferencias de las mujeres:" << endl << endl;
    cout << setw(9) << " ";

    for(int i = 1; i <= parejas; i++)
        cout << " Mujer " << i << " ";

    cout << endl;

    for(int i = 1; i <= parejas; i++){
        cout << "Hombre " << i << " ";

        for(int j = 1; j <= parejas; j++)
            cout << setw(8) << Mujeres[i][j] << " ";

        cout << endl;
    }
	// Hombres
	cout << endl << endl << "Matriz de preferencias de los hombres:" << endl << endl;
    cout << setw(8) << " ";

	for(int i = 1; i <= parejas; i++)
		cout << setw(8) << " Hombre " << i << " ";

	cout << endl;

	for(int i = 1; i <= parejas; i++){
		cout << "Mujer " << i << " ";

		for(int j = 1; j <= parejas; j++)
			cout << setw(9) << Hombres[i][j] << " ";

		cout << endl;
	}
}

// Función que obtiene un vector con emparejamientos óptimos
vector<Emparejamiento> EmparejamientoOptimo(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres){
    vector<Emparejamiento> resultado;
    
    
    return resultado;
}