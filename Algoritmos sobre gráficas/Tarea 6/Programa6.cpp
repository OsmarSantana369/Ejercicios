#include <iostream>
#include <stack>
#include <locale>

using namespace std;

stack<int> pila;   // Se define la pila

int main() {
	setlocale(LC_ALL, "");
	cout << "Este programa recibe n n�meros y los escribe en orden inverso." << endl;
	int n;
	cout << endl << "Di cu�ntos n�meros vas a ingresar: " << endl;
	cin >> n;

	// Llenar la pila con los n�meros del 1 al n
	for (int i = 1; i <= n; ++i) {
		int num;
		cout << endl << "Ingresa el " << i <<"� n�mero: ";
		cin >> num;
		pila.push(num);   // Ingresa valores a la pila
	}

	cout << endl << "Los n�meros en orden inverso son:" << endl;

	// Imprimir y vaciar la pila
	while (!pila.empty()) {
		int aux = pila.top();   // Valor que se encuentra en la cima de la pila
		cout << aux << " ";
		pila.pop();   // Saca el valor que se encuentra en la cima de la pila
	}
	cout << endl << endl;

	return 0;
}
