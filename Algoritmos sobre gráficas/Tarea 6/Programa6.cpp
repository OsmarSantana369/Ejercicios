#include <iostream>
#include <stack>
#include <locale>

using namespace std;

stack<int> pila;   // Se define la pila

int main() {
	setlocale(LC_ALL, "");
	cout << "Este programa recibe n números y los escribe en orden inverso." << endl;
	int n;
	cout << endl << "Di cuántos números vas a ingresar: " << endl;
	cin >> n;

	// Llenar la pila con los números del 1 al n
	for (int i = 1; i <= n; ++i) {
		int num;
		cout << endl << "Ingresa el " << i <<"° número: ";
		cin >> num;
		pila.push(num);   // Ingresa valores a la pila
	}

	cout << endl << "Los números en orden inverso son:" << endl;

	// Imprimir y vaciar la pila
	while (!pila.empty()) {
		int aux = pila.top();   // Valor que se encuentra en la cima de la pila
		cout << aux << " ";
		pila.pop();   // Saca el valor que se encuentra en la cima de la pila
	}
	cout << endl << endl;

	return 0;
}
