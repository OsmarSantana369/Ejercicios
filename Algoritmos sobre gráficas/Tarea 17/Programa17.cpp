#include <iostream>
#include <ctype.h>
# define max 20

/*
Osmar Dominique Santana Reyes

Programa que usa punteros para obtener los vértices de corte de una gráfica.

Para esto se usa un recorrido de búsqueda en profundidad, guardando para cada vértice su tiempo de descubrimiento y el valor más bajo al que se puede llegar desde él. Un vértice es de corte si no es raíz y no existe una arista hacia un antecesor que evite el corte (es decir, si existe un hijo tal que no se puede llegar a un antecesor del vértice desde él o alguno de sus descendientes) o si es raíz y tiene más de un hijo en el recorrido DFS. 

También se imprime la lista de adyacencias de la gráfica.

Orden del algoritmo: O(v + a)
*/

using namespace std;

void buscar();
int visitar(int k, int parent);
void listady();
int val[max];
int novisto = 0, id = 0, x, h, k, w;

struct nodo{
    int clave;
    struct nodo *siguiente;
};

int v, a;
struct nodo *ady[max], *z, *t, *q;

int main(){
    setlocale(LC_ALL, "");
    listady();
    buscar();
    return 0;
}

void listady(){
    int i, j;
    char v1, v2, v3, v4;

    cout << "Da el número de vértices de la gráfica: ";
    cin >> v;
    if(v <= 0 || v >= max){
        cout << "Número de vértices inválido (debe estar entre 1 y " << max-1 << ")." << endl;
        return;
    }
    cout << "Da el número de aristas de la gráfica: ";
    cin >> a;

    z = new nodo;
    z -> siguiente = z;
    z -> clave = 0; // sentinel

    for(j = 1; j <= v; j++)
        ady[j] = z;

    for(i = 1; i <= a; i++){
        cout << endl << "Inserte la " << i << "° arista: ";
        cin >> v3 >> v4;
        v1 = toupper(v3);
        v2 = toupper(v4);
        int x = v1 - 'A' + 1; // mapear 'A'->1, 'B'->2, ...
        int y = v2 - 'A' + 1;
        if(x < 1 || x > v || y < 1 || y > v){
            cout << "Vértices fuera de rango. Use letras entre A y " << char('A' + v - 1) << endl;
            i--; // repetir esta arista
            continue;
        }
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
        cout << char('A' + i - 1) << ":";

        for(t = ady[i]; t != z; t = t -> siguiente){
            cout << char('A' + t -> clave - 1);
            if(t->siguiente != z)
                cout << " ";
        }
        cout << endl;
    }
}

void buscar(){
    int i;
    // inicializar como no vistos
    for(i = 1; i <= v; i++) val[i] = novisto;
    id = 0;

    for(i = 1; i <= v; i++){
        if(val[i] == novisto){
            // parent = 0 indica raíz
            visitar(i, 0);
        }
    }
}

int visitar(int k, int parent){
    struct nodo *t;
    int m, mini;
    val[k] = ++id;    // discovery time
    mini = val[k];    // low value inicial
    int children = 0;

    for(t = ady[k]; t != z; t = t -> siguiente){
        int vtx = t->clave;
        if(val[vtx] == novisto){
            children++;
            m = visitar(vtx, k);
            if(m < mini) mini = m;
            // si no es raíz y no existe arista hacia antecesor que evite corte
            if(parent != 0 && m >= val[k]){
                cout << "El vértice " << char('A' + k - 1) << " es un vértice de corte" << endl;
            }
        } else if(vtx != parent){
            // arista de retroceso
            if(val[vtx] < mini) mini = val[vtx];
        }
    }
    // caso raíz: vértice de corte si tiene más de un hijo en DFS
    if(parent == 0 && children > 1){
        cout << "El vértice " << char('A' + k - 1) << " es un vértice de corte" << endl;
    }
    return mini;
}
