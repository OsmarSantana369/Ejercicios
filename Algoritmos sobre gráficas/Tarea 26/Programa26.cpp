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

struct Pareja{
    int mujer;
    int hombre;
    int correspondencia;
};

void IngresaPreferencias(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres);
void ImprimeMatriz(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres);
Pareja MaximaCorrespondencia(vector<Pareja>& parejasOptimas);
int BuscarEnColumna(vector<vector<int>>& matriz, int columna, int valorBuscado);
void EliminarParejasRepetidas(vector<Pareja>& parejasOptimas);
vector<Pareja> ObtenerParejasOptimas(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres, vector<bool>& mujeresEmparejadas, vector<bool>& hombresEmparejados);
vector<Pareja> Emparejar(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres);

int parejas;
bool Reiniciar;

int main(){
    setlocale(LC_ALL, "");

    do{
        cout << "Ingrese la cantidad de parejas (el número de mujeres debe ser igual al número de hombres): ";
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
    vector<Pareja> resultado = Emparejar(Mujeres, Hombres);

    cout << endl << endl << "Emparejamientos óptimos encontrados:" << endl << endl;
    for(const auto& pareja : resultado){
        cout << "Mujer " << pareja.mujer << "  <-->  Hombre " << pareja.hombre << "    (Correspondencia: " << pareja.correspondencia << ")" << endl;
    }

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
    cout << setw(14) << " ";

    for(int i = 1; i <= parejas; i++)
        cout << " Mujer " << i << " ";

    cout << endl;

    for(int i = 1; i <= parejas; i++){
        cout << "Preferencia " << i << " ";

        for(int j = 1; j <= parejas; j++)
            cout << setw(8) << Mujeres[i][j] << " ";

        cout << endl;
    }
	// Hombres
	cout << endl << endl << "Matriz de preferencias de los hombres:" << endl << endl;
    cout << setw(14) << " ";

	for(int i = 1; i <= parejas; i++)
		cout << setw(8) << " Hombre " << i << " ";

	cout << endl;

	for(int i = 1; i <= parejas; i++){
		cout << "Preferencia " << i << " ";

		for(int j = 1; j <= parejas; j++)
			cout << setw(9) << Hombres[i][j] << " ";

		cout << endl;
	}
}

// Función que encuentra la pareja con mayor correspondencia y devuelve dicha pareja y su posición en el vector
Pareja MaximaCorrespondencia(vector<Pareja>& parejasOptimas){
    Pareja maxPareja = parejasOptimas[0];

    for(const auto& pareja : parejasOptimas){
        if(pareja.correspondencia > maxPareja.correspondencia){
            maxPareja = pareja;
        }
    }

    return maxPareja;
}

// Función que regresa la fila donde se encuentra un entero dado en una columna dada de una matriz
int BuscarEnColumna(vector<vector<int>>& matriz, int columna, int valorBuscado){
    for(int i = 1; i <= parejas; i++){
        if(matriz[i][columna] == valorBuscado){
            return i;
        }
    }
    return -1; // Valor no encontrado
}

// Función que elimina los elementos repetidos de un vector de parejas
void EliminarParejasRepetidas(vector<Pareja>& parejasOptimas){
    for(int i = 0; i < parejasOptimas.size(); i++){
        for(int j = i + 1; j < parejasOptimas.size(); j++){
            if(parejasOptimas[i].mujer == parejasOptimas[j].mujer && parejasOptimas[i].hombre == parejasOptimas[j].hombre){
                parejasOptimas.erase(parejasOptimas.begin() + j);
                j--; // Ajustar el índice después de eliminar un elemento
            }
        }
    }
}

// Función que obtiene un vector con las parejas disponibles de mayor correspondencia
vector<Pareja> ObtenerParejasOptimas(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres, vector<bool>& mujeresEmparejadas, vector<bool>& hombresEmparejados){
    vector<Pareja> parejasOptimas;

    // Mujeres eligen
    for(int i = 1; i <= parejas; i++){
        if(!mujeresEmparejadas[i]){
            for(int j = 1; j <= parejas; j++){
                int hombrePreferido = Mujeres[j][i];

                if(!hombresEmparejados[hombrePreferido]){
                    Pareja nuevaPareja;
                    nuevaPareja.hombre = hombrePreferido;
                    nuevaPareja.mujer = i;
                    
                    for(int k = 1; k <= parejas; k++){
                        if(Hombres[k][hombrePreferido] == i){
                            nuevaPareja.correspondencia = 2*(parejas + 1) - j - k;
                            break;
                        }
                    }
                    parejasOptimas.push_back(nuevaPareja);
                    break;
                }
            }
        }
    }
    // Hombres eligen
    for(int i = 1; i <= parejas; i++){
        if(!hombresEmparejados[i]){
            for(int j = 1; j <= parejas; j++){
                int mujerPreferida = Hombres[j][i];

                if(!mujeresEmparejadas[mujerPreferida]){
                    Pareja nuevaPareja;
                    nuevaPareja.hombre = i;
                    nuevaPareja.mujer = mujerPreferida;
                    
                    for(int k = 1; k <= parejas; k++){
                        if(Mujeres[k][mujerPreferida] == i){
                            nuevaPareja.correspondencia = 2*(parejas + 1) - j - k;
                            break;
                        }
                    }
                    parejasOptimas.push_back(nuevaPareja);
                    break;
                }
            }
        }
    }
    return parejasOptimas;
}

// Función que obtiene un vector con emparejamientos
vector<Pareja> Emparejar(vector<vector<int>>& Mujeres, vector<vector<int>>& Hombres){
    vector<Pareja> resultado;
    vector<bool> mujeresEmparejadas(parejas + 1, false);
    vector<bool> hombresEmparejados(parejas + 1, false);

    do{
        vector<Pareja> parejasOptimas = ObtenerParejasOptimas(Mujeres, Hombres, mujeresEmparejadas, hombresEmparejados);
        EliminarParejasRepetidas(parejasOptimas);
        
        do{
            Pareja parejaSeleccionada = MaximaCorrespondencia(parejasOptimas);
            bool agregarPareja = true;

            if(resultado.size() == 0){
                mujeresEmparejadas[parejaSeleccionada.mujer] = true;
                hombresEmparejados[parejaSeleccionada.hombre] = true;
                resultado.push_back(parejaSeleccionada);
            }
            for(int i = 0; i < resultado.size(); i++){
                if(resultado[i].mujer == parejaSeleccionada.mujer){
                    agregarPareja = false;

                    if(resultado[i].correspondencia == parejaSeleccionada.correspondencia){
                        int h1 = BuscarEnColumna(Mujeres, parejaSeleccionada.mujer, resultado[i].hombre);
                        int h2 = BuscarEnColumna(Mujeres, parejaSeleccionada.mujer, parejaSeleccionada.hombre);

                        if(h1 > h2){
                            // La nueva pareja es mejor, deshacer el emparejamiento anterior
                            hombresEmparejados[resultado[i].hombre] = false;
                            hombresEmparejados[parejaSeleccionada.hombre] = true;
                            resultado[i] = parejaSeleccionada;
                        }
                    }
                }
                if(resultado[i].hombre == parejaSeleccionada.hombre){
                    agregarPareja = false;

                    if(resultado[i].correspondencia == parejaSeleccionada.correspondencia){
                        int m1 = BuscarEnColumna(Hombres, parejaSeleccionada.hombre, resultado[i].mujer);
                        int m2 = BuscarEnColumna(Hombres, parejaSeleccionada.hombre, parejaSeleccionada.mujer);

                        if(m1 > m2){
                            // La nueva pareja es mejor, deshacer el emparejamiento anterior
                            mujeresEmparejadas[resultado[i].mujer] = false;
                            mujeresEmparejadas[parejaSeleccionada.mujer] = true;
                            resultado[i] = parejaSeleccionada;
                        }
                    }
                }
            }
            if(agregarPareja){
                mujeresEmparejadas[parejaSeleccionada.mujer] = true;
                hombresEmparejados[parejaSeleccionada.hombre] = true;
                resultado.push_back(parejaSeleccionada);
            }
            // Descartar la pareja seleccionada de las opciones
            for(int i = 0; i < parejasOptimas.size(); i++){
                if(parejasOptimas[i].mujer == parejaSeleccionada.mujer && parejasOptimas[i].hombre == parejaSeleccionada.hombre){
                    parejasOptimas.erase(parejasOptimas.begin() + i);
                    break;
                }
            }
        } while(!parejasOptimas.empty() && resultado.size() < parejas - 1);
    } while(resultado.size() < parejas - 1);
    
    int sumaMujer = 0, sumaHombre = 0;

    for(int i = 0; i < resultado.size(); i++){
        sumaMujer += resultado[i].mujer;
        sumaHombre += resultado[i].hombre;
    }
    Pareja ultimaPareja;
    ultimaPareja.mujer = (parejas * (parejas + 1)) / 2 - sumaMujer;
    ultimaPareja.hombre = (parejas * (parejas + 1)) / 2 - sumaHombre;
    ultimaPareja.correspondencia = 2 * (parejas + 1) - BuscarEnColumna(Mujeres, ultimaPareja.mujer, ultimaPareja.hombre) - BuscarEnColumna(Hombres, ultimaPareja.hombre, ultimaPareja.mujer);
    resultado.push_back(ultimaPareja);

    return resultado;
}