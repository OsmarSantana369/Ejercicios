#include <iostream>
#include <ctype.h>
# define max 20

using namespace std;

void buscar();
int visitar(int k);
void listady();
int val[max];
int novisto = 0, id = 0, x, h, k, w;

struct nodo{
	int clave;
	struct nodo *siguiente;
};

int v, a;
struct nodo *ady[max], *z, *t, *q;
struct nodo *visitar(int m, struct nodo*n);

int main(){
	listady();
	buscar();
	return 0;
}

void listady(){
	int i, j;
	char v1, v2, v3, v4;

	cout << "Da el número de vértices de la gráfica: ";
	cin >> v;
	cout << "Da el número de aristas de la gráfica: ";
	cin >> a;

	z = new nodo;
	z -> siguiente = z;
	for(j = 1; j <= v; j++)
		ady[j] = z;

	for(i = 1; i <= a; i++){
		cout << "Inserte la" << i << "° arista: ";
		cin >> v3 >> v4;
		v1 = toupper(v3);
		v2 = toupper(v4);
		int x = v1;
		int y = v2;
		t = new nodo;
		t -> clave = x;
		t -> siguiente = ady[y];
		ady[y] = t;
		t = new nodo;
		t -> clave = y;
		t -> siguiente = ady[x];
		ady[x] = t;
	}

	cout << "La lista de adyacencias de los vértices de la gráfica es:" << endl;

	for(i = 1; i <= v; i++){
		cout << char(96 + i) << ":";

		for(t = ady[i]; t != z; t = t -> siguiente){
			cout << char(96 + t -> clave);

			if(t != z)
				cout << " ";
		}
		cout << endl;
	}
}

int visitar(int k){
	struct nodo *t;
	int m, mini;
	val[k] = ++id;
	mini = id;

	for(t = ady[k]; t != z; t = t -> siguiente){
		if(val[t -> clave] == novisto){
			cout << endl << " visitare:" << t -> clave;
			m = visitar(t -> clave);
			cout << "\t m =" << m << "\t mini = " << mini;

			if(m < mini){
				mini = m;
			}
		}
	}
}