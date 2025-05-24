#include "./graph.h"

Graph::Graph(size_t vertices) : vertices(vertices) {
    // gen();
    // probDist(0.0, 1.0);
    // vertexDist(0, (int)vertices-1);
    adjList.resize(vertices);
    adjMatrix.resize(vertices, std::vector<size_t>(vertices, 0));
    edgeList.reserve(vertices*(vertices-1)/2);
}

const size_t Graph::size() const {
    return vertices;
}

void Graph::addEdge(size_t u, size_t v) {
    adjList[u].push_back(v);
    adjMatrix[u][v] = 1;
    edgeList.push_back({u, v});
}

std::vector<std::vector<size_t>> Graph::getAdjList() const {
    return adjList;
}

void Graph::printAdjList() {
    std::cout << "Список смежностей:\n";
    for (size_t i = 0; i < vertices; i++) {
        std::cout << i << ": ";
        for (size_t v : adjList[i]) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::printAdjMatrix() {
    std::cout << "Матрица смежностей:\n";
    for (const auto& row : adjMatrix) {
        for (size_t val : row) {
            std::cout << std::setw(2) << val << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::printEdgeList() {
    std::cout << "Список рёбер:\n";
    for (const auto& edge : edgeList) {
        std::cout << "(" << edge.first << ", " << edge.second << "); "; // Изменено на "->" для ориентированного графа
    }
    std::cout << std::endl;
}

void Graph::generate(size_t edges, GraphType type) {
    const double edgeProbability = 0.3;
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<int> vertexDist(0, vertices - 1);

    switch (type) {
        case RANDOM:
            for (size_t i = 0; i < vertices; i++) {
                for (size_t j = 0; j < vertices; j++) {
                    if (j < vertices && probDist(gen) < edgeProbability)
                        addEdge(i, j);
                }
            }
            break;
        case STRONGLY_CONNECTED:
            for (size_t i = 0; i < vertices - 1; i++)
                addEdge(i, i + 1);
            addEdge(vertices - 1, 0);
            break;
            // creating one large cycle
        case DISCONNECTED_COMPONENTS:
            for (size_t k = 0; k < vertices; k += vertices/5) {
                for (size_t i = 0; i < vertices/5; i++)
                    if (probDist(gen) < edgeProbability)
                        addEdge(k + i, k + i + 1);
            }
            break;
        case MANY_CYCLES:
            std::cout << vertices << " ";
            for (size_t k = 0; k < vertices; k += (int)vertices/5) {
                std::cout << k << " ";
                std::cout << std::endl;
                for (size_t i = 0; i < vertices/5-1; i++)
                    addEdge(k + i, k + i + 1);
                if (vertices < edges && k+vertices/5 < vertices)
                    addEdge(k + vertices/5, k);
            }
            std::cout << "ok" << std::endl;
            break;
    }
}

void Graph::visualize(const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph G {\n";
    for (const auto& edge : edgeList) {
        out << "    " << edge.first << " -> " << edge.second << ";\n";
    }
    out << "}\n";
    out.close();
}