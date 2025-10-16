#include <iostream>
using namespace std;

int main() {
    int num = 42;       // Variable normal
    int* ptr = &num;    // Puntero que almacena la dirección de 'num'

    cout << "Valor de num: " << num << endl;          // Imprime 42
    cout << "Dirección de num: " << &num << endl;     // Dirección de memoria
    cout << "Valor de ptr: " << ptr << endl;          // Dirección de 'num'
    cout << "Valor apuntado por ptr: " << *ptr << endl; // Imprime 42 (desreferenciación)

    return 0;
}
