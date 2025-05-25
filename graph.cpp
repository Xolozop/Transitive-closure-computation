#include "./graph.h"

// Конструктор графа с заданным числом вершин
Graph::Graph(size_t vertices) : vertices(vertices) {
    adjList.resize(vertices); // Инициализация списка смежности
    adjMatrix.resize(vertices, std::vector<bool>(vertices, 0)); // Инициализация матрицы смежности
    edgeList.reserve(vertices*(vertices-1)/2); // Резерв для списка рёбер
}

// Конструктор графа из матрицы смежности
Graph::Graph(std::vector<std::vector<bool>> matrix) : vertices(matrix.size()) {
    adjList.resize(vertices); // Инициализация списка смежности
    adjMatrix = matrix; // Копирование матрицы
    edgeList.reserve(vertices*(vertices-1)/2); // Резерв для списка рёбер
    for (size_t row = 0; row < vertices; row++) {
        for (size_t col = 0; col < vertices; col++) {
            if (adjMatrix[row][col] == true) {
                adjList[row].push_back(col); // Добавление ребра в список смежности
                edgeList.push_back(std::pair<size_t, size_t>(row, col)); // Добавление ребра в список рёбер
            }
        }
    }
}

// Возвращаение количества вершин графа
const size_t Graph::size() const {
    return vertices;
}

// Добавление ребра от вершины u к вершине v
void Graph::addEdge(size_t u, size_t v) {
    adjList[u].push_back(v); // Обновление списка смежности
    adjMatrix[u][v] = true; // Обновление матрицы смежности
    edgeList.push_back({u, v}); // Добавление ребра в список рёбер
}

// Возвращение матрицы смежности
std::vector<std::vector<bool>> Graph::getAdjMatrix() const {
    return adjMatrix;
}

// Возвращение списка смежности
std::vector<std::vector<size_t>> Graph::getAdjList() const {
    return adjList;
}

// Вывод списка смежности
void Graph::printAdjList() {
    std::cout << "Список смежности:\n";
    for (size_t i = 0; i < vertices; i++) {
        std::cout << i << ": ";
        for (size_t v : adjList[i]) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}

// Вывод матрицы смежности
void Graph::printAdjMatrix() {
    std::cout << "Матрица смежности:\n";
    for (const auto& row : adjMatrix) {
        for (size_t val : row) {
            std::cout << std::setw(2) << val << " "; 
        }
        std::cout << std::endl;
    }
}

// Вывод списка рёбер
void Graph::printEdgeList() {
    std::cout << "Список рёбер:\n";
    for (const auto& edge : edgeList) {
        std::cout << "(" << edge.first << " -> " << edge.second << "); "; 
    }
    std::cout << std::endl;
}

// Генерация графа заданного типа
void Graph::generate(size_t edges, GraphType type) {
    const double edgeProbability = 0.3; // Вероятность добавления ребра
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<int> vertexDist(0, vertices - 1);

    switch (type) {
        case RANDOM:
            // Случайный граф: добавление рёбер с вероятностью
            for (size_t i = 0; i < vertices; i++) {
                for (size_t j = 0; j < vertices; j++) {
                    if (j < vertices && probDist(gen) < edgeProbability)
                        addEdge(i, j);
                }
            }
            break;
        case STRONGLY_CONNECTED:
            // Сильно связный граф: создание цикла
            for (size_t i = 0; i < vertices - 1; i++)
                addEdge(i, i + 1);
            addEdge(vertices - 1, 0);
            break;
        case DISCONNECTED_COMPONENTS:
            // Несколько несвязных компонент
            for (size_t k = 0; k < vertices; k += vertices/5) {
                for (size_t i = 0; i < vertices/5; i++)
                    if (probDist(gen) < edgeProbability)
                        addEdge(k + i, k + i + 1);
            }
            break;
        case MANY_CYCLES:
            // Граф с множеством циклов
            std::cout << vertices << " ";
            for (size_t k = 0; k < vertices; k += (int)vertices/5) {
                std::cout << k << " ";
                std::cout << std::endl;
                for (size_t i = 0; i < vertices/5-1; i++)
                    addEdge(k + i, k + i + 1);
                if (vertices < edges && k+vertices/5 < vertices)
                    addEdge(k + vertices/5, k); // Замыкание цикла
            }
            break;
    }
}

// Сохранение графа в формате DOT для визуализации
void Graph::visualize(const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph G {\n";
    for (const auto& edge : edgeList) {
        out << "    " << edge.first << " -> " << edge.second << ";\n"; 
    }
    out << "}\n";
    out.close();
}