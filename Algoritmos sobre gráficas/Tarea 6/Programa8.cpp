#include <iostream>
#include <queue>
#include <locale>

using namespace std;

char letra(int p){
	char c = p + 96;
	return c;
}

int numero_de_letra(char c){
	if (c >= 97) c = c-32;
	return c-64;
}

void MatrizAD(int n, int AD[100][100]){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			AD[i][j] = 0;
		}
	}

	int q;
	cout << endl << "Escribe el número de aristas: ";
	cin >> q;
	char v1, v2;

	for(int i=1; i<=q; i++){
		cout << "Dame los extremos de la " << i << "° arista: ";
		cin >> v1 >> v2;
		AD[numero_de_letra(v1)][numero_de_letra(v2)] = 1;
		AD[numero_de_letra(v2)][numero_de_letra(v1)] = 1;
	}
}

struct Vertice{
	char v;
	int d;
};

int MA[100][100];
int p;

int grado(int v){
	int cont = 0;

	for(int i=1; i<=p; i++){
		if(MA[v][i] == 1)
			cont++;
	}
	return cont;
}

queue<Vertice> cola;   // Se define la cola

int main() {
	setlocale(LC_ALL, "");
	cout << "Este programa muestra los vértices de grado par de una gráfica." << endl;

	cout << endl << "Ingresa el número de vértices de la gráfica: ";
	cin >> p;

	MatrizAD(p, MA);

	for (int i = 1; i <= p; i++) {
		if (grado(i) % 2 == 0) {
			Vertice v1;
			char aux = letra(i);
			v1.v = aux;
			v1.d = grado(i);
			cola.push(v1);
		}
	}

	cout << endl << "Los vértices que tienen grado par son: " << endl;
	while (!cola.empty()) {
		Vertice f = cola.front();
		cout << f.v << " con grado " << f.d << endl;
		cola.pop();
	}
	cout << endl;

	return 0;
}
