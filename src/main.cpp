
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include "../include/kruskal.h"
#include "../include/helper.h"

using namespace std;

int main(int argc, char **args)
{
    string inputPath, outputPath;
    int solution = 0;

    // Receber opcoes do usuario
    for (int i = 0; i < argc; i++)
    {
        // Indicar arquivo que contem o grafo de entrada
        if (!strcmp(args[i], "-f") && i != argc - 1)
        {
            inputPath = args[++i];
        }
        else if (!strcmp(args[i], "-f"))
        {
            printf("Um caminho para o arquivo precisa ser especificado apos '-f'\n");
            return 1;
        }

        // Indicar arquivo em que a saida sera armazenada (opcional)
        if (!strcmp(args[i], "-o") && i != argc - 1)
        {
            outputPath = args[++i];
        }
        else if (!strcmp(args[i], "-o"))
        {
            printf("Um caminho para o arquivo de saida precisa ser especificado apos '-o'\n");
            return 1;
        }

        // Verifica se o usuario quer a solucao
        if (!strcmp(args[i], "-s"))
        {
            solution = 1;
        }

        // Verifica se o usuario precisa do helper
        if (!strcmp(args[i], "-h"))
        {
            printHelper();
        }
    }

    if (inputPath.empty())
    {
        printf("Por favor, informe o arquivo de entrada (-f <arquivo>)\n");
        return 1;
    }

    // Ler inputs do arquivo informado (-f <arquivo>)
    ifstream inputFile(inputPath);


    if (!inputFile.is_open())
    {
        printf("O arquivo informado nao foi encontrado, verifique o caminho\n");
        return 1;
    }

    string line;

    if (!getline(inputFile, line))
    {
        printf("Falha ao ler inputs do usuario\n");
        return 1;
    }

    int vertices, arestas;
    stringstream ss(line);

    if (!(ss >> vertices >> arestas))
    {
        printf("Falha ao ler definicoes do grafo\n");
        return 1;
    }

    Graph graph;

    graph.V = vertices; // Número de vértices
    graph.E = arestas;  // Número de arestas

    // Adiciona arestas ao grafo
    for (int i = 0; i < arestas; i++)
    {
        if (!getline(inputFile, line))
        {
            printf("O input tem dados faltando\n");
            return 1;
        }

        int origem, destino, peso;
        stringstream ss(line);

        if (!(ss >> origem >> destino >> peso))
        {
            printf("Falha ao ler valores\n");
            return 1;
        }

        // Ajuste para indexação base 0
        graph.edges.push_back({origem - 1, destino - 1, peso});
    }

    kruskal(graph, solution, outputPath); // Executa o algoritmo de Kruskal
    return 0;
}
