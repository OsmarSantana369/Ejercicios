#include <iostream>
#include <queue>
#include <locale>

using namespace std;

queue<int> cola;   // Se define la cola

int main() {
	setlocale(LC_ALL, "");
	cout << "Este programa lee n datos y muestra los que son pares." << endl;
	int n;
	cout << endl << "Ingresa el número de datos: " << endl;
	cin >> n;

	// Llenar la cola con los números del 1 al n
	for (int i = 1; i <= n; ++i) {
		int x;
		cout << endl << "Ingresa el " << i <<"° dato: ";
		cin >> x;

		if (x % 2 == 0){
			cola.push(x);   // Ingresa el valor a la cola
		}
	}

	cout << endl << "Los datos que son pares son:" << endl;

	// Imprimir y vaciar la cola
	while (!cola.empty()) {
		int p = cola.front();   // Valor que se encuentra en la parte inicial de la cola
		cout << p << " ";
		cola.pop();   // Saca el valor que se encuentra en la parte inicial de la cola
	}
	cout << endl << endl;

	return 0;
}
