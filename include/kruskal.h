#include <vector>
#include <string>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    std::vector<Edge> edges;
};

void kruskal(Graph &graph, int solution, string outputPath);