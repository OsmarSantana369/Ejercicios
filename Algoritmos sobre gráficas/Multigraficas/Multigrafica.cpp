#include <iostream>
#include <fstream>
#include <vector>
#include <clocale>
using namespace std;

// Estructura para almacenar los extremos de una arista
struct Arista
{
    char vertice_1, vertice_2;
    int numero_arista;
};

void ExportarAristas (vector<vector<Arista>>& Frente_Atras, vector<vector<Arista>>& Izquierda_Derecha, const string& filename)
{
    ofstream file(filename);
    file<<"FrenteCubo1, AtrasCubo1, IzquierdaCubo1, DerechaCubo1, FrenteCubo2, AtrasCubo2, IzquierdaCubo2, DerechaCubo2, FrenteCubo3, AtrasCubo3, IzquierdaCubo3, DerechaCubo3, FrenteCubo4, AtrasCubo4, IzquierdaCubo4, DerechaCubo4, \n";
    for(int i=0;i<Frente_Atras.size();i++)
    {
        file << Frente_Atras[i][0].vertice_1 << ", " << Frente_Atras[i][0].vertice_2 << ", " << Izquierda_Derecha[i][0].vertice_1 << ", " << Izquierda_Derecha[i][0].vertice_2 << ", " << Frente_Atras[i][1].vertice_1 << ", " << Frente_Atras[i][1].vertice_2 << ", " << Izquierda_Derecha[i][1].vertice_1 << ", " << Izquierda_Derecha[i][1].vertice_2 << ", " << Frente_Atras[i][2].vertice_1 << ", " << Frente_Atras[i][2].vertice_2 << ", " << Izquierda_Derecha[i][2].vertice_1 << ", " << Izquierda_Derecha[i][2].vertice_2 << ", " << Frente_Atras[i][3].vertice_1 << ", " << Frente_Atras[i][3].vertice_2 << ", " << Izquierda_Derecha[i][3].vertice_1 << ", " << Izquierda_Derecha[i][3].vertice_2 << "\n";
    }
    file.close();
}

// Estructura para almacenar un vértice y su grado
struct GradoVertice
{
    char vertice;
    int grado;
};

// Función para actualizar el grado de un vértice
void actualizarGrado(vector<GradoVertice>& grados, char v)
{
    for (auto& g:grados)
    {
        if (g.vertice==v)
        {
            g.grado++;  // Si el vértice ya está en la lista, incrementar grado
            return;
        }
    }
    grados.push_back({v, 1});  // Si el vértice no estaba, agregarlo con grado 1
}

// Función para determinar el grado de los vértices en una combinación
vector<GradoVertice> contarVertices(const vector<Arista>& combinacionAristas)
{
    vector<GradoVertice> grados;

    for (const auto& arista:combinacionAristas)
    {
        actualizarGrado(grados, arista.vertice_1);
        actualizarGrado(grados, arista.vertice_2);
    }

    return grados;  // Regresa el vector con los grados de cada vértice
}

// Función para verificar si una combinación cumple que cada vértice es de grado 2
bool cumpleGrado2(const vector<GradoVertice>& grados)
{
    for (const auto& g:grados)
    {
        if (g.grado!=2)
        {
            return false;  // Si algún vértice no es de grado 2, la combinación no es válida
            break;
        }
    }
    return true;
}

void reordenarAristas(vector<Arista>& combinacion)
{
    for(int i=0;i<combinacion.size();i++)
    {
        for(int j=0;j<i;j++)
        {
            if(combinacion[i].vertice_1==combinacion[j].vertice_1 || combinacion[i].vertice_2==combinacion[j].vertice_2)
            {
                char temp;
                temp=combinacion[i].vertice_1;
                combinacion[i].vertice_1=combinacion[i].vertice_2;
                combinacion[i].vertice_2=temp;
            }
        }
    }

}

// Función que almacena combinaciones que cumplen la condición
void validarCombinacion(vector<Arista>& combinacionAristas, vector<vector<Arista>>& Subgraficas)
{
    vector<GradoVertice> grados = contarVertices(combinacionAristas);

    if (cumpleGrado2(grados))
    {
        reordenarAristas(combinacionAristas);
        Subgraficas.push_back(combinacionAristas);  // Agregar a la lista de combinaciones
        for (const auto& arista:combinacionAristas)
        {
            cout<<" \t ("<<arista.vertice_1<<", "<<arista.vertice_2<< ") ";
        }
        cout<<endl;
    }
}

// Función que genera todas las combinaciones posibles eligiendo un elemento de cada cubo
void generarCombinaciones(const vector<vector<Arista>>& AdyacenciasCubos, vector<Arista> combinacionAristas, int n, vector<vector<Arista>>& Subgraficas)
{
    if (n==AdyacenciasCubos.size())
    {
        validarCombinacion(combinacionAristas, Subgraficas);
        return;
    }

    for (auto arista:AdyacenciasCubos[n])
    {
        combinacionAristas.push_back(arista);
        generarCombinaciones(AdyacenciasCubos, combinacionAristas, n+1, Subgraficas);
        combinacionAristas.pop_back();
    }
}

// Función para verificar si dos combinaciones son diferentes
bool sonDiferentes (const vector<Arista>& comb_1, const vector<Arista>& comb_2)
{
    for (int k=0;k<comb_1.size(); k++)
    {
        if ((comb_1[k].vertice_1==comb_2[k].vertice_1 && comb_1[k].vertice_2==comb_2[k].vertice_2) ||
            (comb_1[k].vertice_1==comb_2[k].vertice_2 && comb_1[k].vertice_2==comb_2[k].vertice_1))
        {
            if (comb_1[k].numero_arista==comb_2[k].numero_arista)
            {
                return false; // Si en la misma posición hay una arista igual, no son completamente diferentes
                break;
            }

        }
    }
    return true;
}

// Función para comparar todas las combinaciones
void compararCombinaciones(const vector<vector<Arista>>& Combinaciones, int c,vector<vector<Arista>>& Frente_Atras, vector<vector<Arista>>& Izquierda_Derecha)
{
    c=0;
    if(Combinaciones.size()==0)
    {
        cout<<"\n El Juego de Locura Instantánea no tiene solución.\n";
        return;
    }
    else
    {
        for (int i=0;i<Combinaciones.size();i++)
        {
            for (int j=i+1;j<Combinaciones.size();j++)
            {
                if (sonDiferentes(Combinaciones[i], Combinaciones[j]))
                {
                    Frente_Atras.push_back(Combinaciones[i]);
                    Izquierda_Derecha.push_back(Combinaciones[j]);
                }
            }
        }

        if(Frente_Atras.size()==0)
        {
            cout<<"\n El Juego de Locura Instantánea no tiene solución.\n";
            return;
        }
        else
        {
            cout<<"\n\n Las soluciones al juego de Locura Instantánea son:\n\n";
            cout<<"\t\t Frente / Atrás \t\t\t\t Izquierda / Derecha \n\n";
            cout<< "      Cubo 1    Cubo 2    Cubo 3    Cubo 4\t\tCubo 1    Cubo 2    Cubo 3    Cubo 4\n";
            for(int i=0;i<Frente_Atras.size();i++)
            {
                c++;
                cout<<"\n "<<c;
                for (const auto& arista:Frente_Atras[i])
                {
                    cout<<"    ("<<arista.vertice_1<<", "<<arista.vertice_2<< ")";
                }
                cout<<"    \t    ";
                for (const auto& arista:Izquierda_Derecha[i])
                {
                    cout<<"    ("<<arista.vertice_1<<", "<<arista.vertice_2<< ")";
                }
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "spanish");

    vector<vector<Arista>> AdyacenciasCubos(4);
    char v_1, v_2;
    int numero_arista=0;

    cout<<"\n\t LOCURA INSTANTÁNEA\n\n";

    for (int i=0;i<AdyacenciasCubos.size();i++)
    {
        cout<<"\n Ingrese las 3 aristas del cubo "<<i+1<< ":\n";
        for (int j=0;j<3;j++) //Número de aristas por cubo=3
        {
            cin>>v_1>>v_2;
            numero_arista++;
            AdyacenciasCubos[i].push_back({v_1, v_2,numero_arista});
        }
    }

    vector<vector<Arista>> Subgraficas;
    vector<Arista> combinacionAristas;
    vector<vector<Arista>> Frente_Atras;
    vector<vector<Arista>> Izquierda_Derecha;

    cout<<"\n Combinaciones donde cada vértice tiene grado 2:\n\n";
    cout<<"\t Cubo 1 \t Cubo 2 \t Cubo 3 \t Cubo 4\n\n";

    generarCombinaciones(AdyacenciasCubos, combinacionAristas, 0, Subgraficas);

    int c;
    compararCombinaciones(Subgraficas,c,Frente_Atras,Izquierda_Derecha);
    ExportarAristas(Frente_Atras, Izquierda_Derecha, "aristas.csv");
    cout<<endl<<endl;
    return 0;
}


/*
#include <fstream>
#include <vector>
using namespace std;

struct Edge {
    int v1;
    int v2;
    float weight;
    vector<float> color;
};

void exportEdges(const vector<Edge>& edges, const string& filename) {
    ofstream file(filename);
    file << "EndNodes_1,EndNodes_2,Weight,Color_R,Color_G,Color_B\n";
    for (const auto& edge : edges) {
        file << edge.v1 << "," << edge.v2 << "," << edge.weight << ",";
        for (const auto& c : edge.color) {
            file << c << ",";
        }
        file << "\n";
    }
    file.close();
}

int main() {
    vector<Edge> edges = {
        {1, 2, 6, {0, 0, 0}},
        {1, 3, 6, {1, 0, 0}},
        {1, 2, 7, {0, 1, 0}},
        {2, 3, 11, {0, 0, 1}},
        {3, 4, 17, {1, 1, 0}}
    };
    exportEdges(edges, "edges.csv");

    vector<Edge> edges2 = {
        {1, 2, 6, {0, 0, 0}},
        {1, 3, 6, {1, 0, 0}},
        {1, 2, 7, {0, 1, 0}},
        {2, 3, 11, {0, 0, 1}},
        {3, 2, 17, {1, 1, 0}}
    };
    exportEdges(edges2, "edges2.csv");
    return 0;
}
*/