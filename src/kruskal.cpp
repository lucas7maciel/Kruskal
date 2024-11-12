#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

#include "../include/kruskal.h"

using namespace std;

// Função para encontrar o conjunto de um elemento usando compressão de caminho
int find(vector<int> &parent, int i)
{
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Função para unir dois conjuntos
void unionSets(vector<int> &parent, int x, int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset; // Une os conjuntos
}

// Função para comparar duas arestas (usada pelo sort)
bool compareEdge(Edge e1, Edge e2)
{
    return e1.weight < e2.weight;
}

// Função principal do algoritmo de Kruskal
void kruskal(Graph &graph, int solution, string outputPath)
{
    vector<Edge> result;             // Armazena a árvore geradora mínima
    vector<int> parent(graph.V, -1); // Inicializa todos os pais como -1

    ofstream outfile(outputPath);

    // Ordena todas as arestas em ordem crescente pelo peso
    sort(graph.edges.begin(), graph.edges.end(), compareEdge);

    // Itera por todas as arestas
    for (auto edge : graph.edges)
    {
        int x = find(parent, edge.src);
        int y = find(parent, edge.dest);

        // Se não formarem um ciclo, adiciona à árvore geradora mínima
        if (x != y)
        {
            result.push_back(edge);
            unionSets(parent, x, y);
        }
    }

    // Imprime as arestas da árvore geradora mínima
    // cout << "Arestas da Árvore Geradora Mínima:\n";
    int totalWeight = 0;

    for (auto edge : result)
    {
        // edge.src + 1 << " -- " << edge.dest + 1 << " == " <<
        // cout << edge.weight << endl; // Ajuste para exibição correta dos vértices
        if (edge.weight > 0)
        {
            totalWeight += edge.weight;
        }

        if (solution && outfile.is_open()) {
            outfile << "(" << edge.src + 1 << ", " << edge.dest + 1 << ") "; 
        } else if (solution)
        {
            printf("(%i, %i) ", edge.src + 1, edge.dest + 1);
        }
    }

    // Otimizar
    if (!solution && outfile.is_open())
    {
        outfile << totalWeight << " \n";
    } else if (!solution) {
        printf("%i \n", totalWeight);
    }
    
    if (solution && outfile.is_open()) {
        outfile << endl;
    } else if (solution) {
        printf("\n");
    }

    if (outfile.is_open()) {
        outfile.close();
    }
}
