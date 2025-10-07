
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
