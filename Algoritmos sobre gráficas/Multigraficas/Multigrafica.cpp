
#include <fstream>
#include <vector>
using namespace std;

struct Edge {
    int from;
    int to;
    int color;
};

void exportEdges(const vector<Edge>& edges, const string& filename) {
    ofstream file(filename);
    file << "from,to,color\n";
    for (const auto& edge : edges) {
        file << edge.from << "," << edge.to << "," << edge.color << "\n";
    }
    file.close();
}

int main() {
    vector<Edge> edges = {
        {1, 2, 0},
        {2, 3, 1},
        {3, 1, 2}
    };
    exportEdges(edges, "edges.csv");
    return 0;
}
