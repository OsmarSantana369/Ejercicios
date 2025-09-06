//Abelardo Javier Flores Huesca.
//Programa de matriz de distancia.


//#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>

using namespace std;

void ImprimirMat2(int n, int X[26][26]) {
    char letra;
    letra = 65;
    cout << "\t";
    for (int i = 0;i < n;i++) {
        if (letra < 91) {
            cout << letra << "\t";
            letra++;
        }
        else letra = 65;
    }
    letra = 65;
    cout << endl;
    for (int i = 0;i < n;i++) {
        cout << letra << "\t|";
        letra++;
        for (int j = 0;j < n;j++) {
            if (j < n - 1) cout << X[i][j] << "\t";
            else cout << X[i][j] << "|\n";
        }
    }
}


void MultMat(int n, int m, int p, int A[26][26], int B[26][26], int C[26][26]) {
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < p;j++) {
            int c = 0;
            for (int k = 0;k < m;k++) {
                c = c + A[i][k] * B[k][j];
            }
            C[i][j] = c;
        }
    }
}

void CopMat(int n, int A[26][26], int B[26][26]) {
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++) {
            B[i][j] = A[i][j];
        }
}

void PotMat(int n, int p, int A[26][26], int D[26][26]) {
    int  C[26][26], B[26][26];
    if (p == 0) {
        for (int i = 0;i < n;i++)
            for (int j = 0;j < n;j++) {
                if (i == j) B[i][j] = 1;
                else B[i][j] = 0;
            }
        CopMat(n, B, D);
    } else
    if (p == 1) {
        CopMat(n, A, D);
    }
    else {
        for (int i = 2;i <= p;i++) {
            if (i == 2) MultMat(n, n, n, A, A, B);
            else {
                if (i % 2 == 1) MultMat(n, n, n, A, B, C);
                else MultMat(n, n, n, A, C, B);
            }
        }
        if (p % 2 == 1) CopMat(n, C, D);
        else CopMat(n, B, D);
    }
}

void Dist(int n, int A[26][26], int D[26][26]) {
    int cont;
    int E[26][26];
    for (int i = 1;i < 26;i++) {
        cont = 0;
        for (int k = 0;k < n;k++)
            for (int j = 0;j < n;j++)
                E[k][j] = 0;
        PotMat(n, i, A, E);
        for (int k = 0;k < n;k++)
            for (int j = 0;j < n;j++) {
                if (E[k][j] == 1 && k != j) {
                    D[k][j] = i;
                    cont++;
                }
            }
        if (cont == 0) break;
    }
}

int main() {
    char repetir;
    int n, m, p;
    int A[26][26],D[26][26];

    setlocale(LC_ALL, "");
    do {
        system("CLS");
        cout << "\n\t\t\tPrograma que da la matriz de distancia para una gráfica.\n\nIntroduzca la cantidad de vértices de la gráfica: ";
        cin >> n;

        for (int i = 0;i < n;i++) {
            for (int j = 0;j < n;j++) {
                A[i][j] = 0;
                D[i][j]=0;
            }
        }

        cout << "\nIntroduzca la cantidad de aristas de la gráfica: ";
        cin >> m;
        if (m > 0)
            cout << "\nLos vértices de la matriz se nombran de la A a la Z. Sabiendo esto, introduzca las aristas de la gráfica.";

        int a = 1, a1, a2;
        char v1, v2;
        for (int i = 0;i < m;i++) {
            cout << "\nArista " << a << ".\n";
            cout << "\n\tVértice inicial: ";
            cin >> v1;
            cout << "\n\tVértice final: ";
            cin >> v2;
            if (v1 > 96 && v1 < 123) v1 = v1 - 32;
            if (v2 > 96 && v2 < 123) v2 = v2 - 32;
            if (v1 > 64 && v1 < 91 && v2>64 && v2 < 91 && v1 != v2) {
                a1 = v1 - 65;
                a2 = v2 - 65;
                A[a1][a2] = 1;
                A[a2][a1] = 1;
            }
            a++;
        }
        cout << "\nLa gráfica que ingresó es:\n";
        ImprimirMat2(n, A);


        cout << "\n\nLa matriz de distancia es:\n";
        Dist(n, A, D);
        ImprimirMat2(n, D);

        cout << "\n\nPara repetir el programa pulse s.\nPara terminar pulse cualquier otra tecla.\n";
        cin >> repetir;
        if (repetir == 'S') repetir = 's';
    } while (repetir == 's');

    return 0;
}

