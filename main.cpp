#include <iostream>
#include <vector>
#include <list>
#include <iomanip>
#include <fstream>

class Graph {
public:
    Graph(int vertices) : vertices(vertices) {
        adjList.resize(vertices);
        adjMatrix.resize(vertices, std::vector<int>(vertices, 0));
        edgeList.reserve(vertices * (vertices - 1) / 2);
    }

    void addEdge(int u, int v) {
        // Добавление в список смежностей
        adjList[u].push_back(v);

        // Добавление в матрицу смежностей
        adjMatrix[u][v] = 1;

        // Добавление в список рёбер
        edgeList.push_back({u, v});
    }

    void printAdjList() {
        std::cout << "Список смежностей:\n";
        for (int i = 0; i < vertices; ++i) {
            std::cout << i << ": ";
            for (int v : adjList[i]) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }

    void printAdjMatrix() {
        std::cout << "Матрица смежностей:\n";
        for (const auto& row : adjMatrix) {
            for (int val : row) {
                std::cout << std::setw(2) << val << " ";
            }
            std::cout << std::endl;
        }
    }

    void printEdgeList() {
        std::cout << "Список рёбер:\n";
        for (const auto& edge : edgeList) {
            std::cout << "(" << edge.first << ", " << edge.second << "); "; // Изменено на "->" для ориентированного графа
        }
        std::cout << std::endl;
    }

    void visualize(const std::string& filename) {
        std::ofstream out(filename);
        out << "digraph G {\n"; // Изменено на "digraph" для обозначения ориентированного графа
        for (const auto& edge : edgeList) {
            out << "    " << edge.first << " -> " << edge.second << ";\n"; // Изменено на "->" для ориентированного графа
        }
        out << "}\n";
        out.close();
    }

private:
    int vertices; // Количество вершин
    std::vector<std::list<int>> adjList; // Список смежностей
    std::vector<std::vector<int>> adjMatrix; // Матрица смежностей
    std::vector<std::pair<int, int>> edgeList; // Список рёбер
};

int main() {
    Graph g(5); // Создаем граф с 5 вершинами

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printAdjList();
    g.printAdjMatrix();
    g.printEdgeList();

    // Визуализация графа
    g.visualize("graph.dot");

    // Для генерации изображения из .dot файла, выполните команду:
    // dot -Tpng graph.dot -o graph.png

    return 0;
}
