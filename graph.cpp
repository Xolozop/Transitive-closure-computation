#include "./graph.h"

// Резервируем память для хранения графа с n вершинами
Graph::Graph(size_t vertices) : vertices(vertices) {
    adjList.resize(vertices);
    adjMatrix.resize(vertices, std::vector<bool>(vertices, 0));
    edgeList.reserve(vertices*(vertices-1)/2);
    transMatrix.resize(vertices, std::vector<bool>(vertices, 0));
}

// Конструктор графа из матрицы смежности
Graph::Graph(std::vector<std::vector<bool>> matrix) : vertices(matrix.size()) {
    adjList.resize(vertices);
    adjMatrix = matrix;
    edgeList.reserve(vertices*(vertices-1)/2);
    transMatrix.resize(vertices, std::vector<bool>(vertices, 0));
    // Резервируем память 
    
    for (size_t row = 0; row < vertices; row++) {
        for (size_t col = 0; col < vertices; col++) {
            if (adjMatrix[row][col] == true) {
                adjList[row].emplace(col);
                edgeList.push_back(std::pair<size_t, size_t>(row, col));
            }
        }
    }
}

std::vector<std::pair<size_t, size_t>> Graph::cmp(Graph g) {
    std::vector<std::pair<size_t, size_t>> diff;
    std::vector<std::vector<bool>> adjMatrix2 = g.getAdjMatrix();
    std::vector<std::vector<bool>> transMatrix2 = g.getTransMatrix();
    for (size_t i = 0; i < adjMatrix.size(); i++) {
        for (size_t j = 0; j < adjMatrix.size(); j++) {
            if (i == j)
                continue;

            if ((adjMatrix[i][j] != adjMatrix2[i][j]) || (transMatrix[i][j] != transMatrix2[i][j]))
                diff.push_back({i, j});
        }
    }
    return diff;
}


// Генерация графа заданного типа
void Graph::generate(GraphType type, double edgeProbability) {
    type = type;
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<int> vertexDist(0, vertices - 1);

    switch (type) {
        case RANDOM:
            // Случайный граф: добавление рёбер со вероятностью
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
            addEdge(vertices - 1, 0); // Замыкание цикла
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
                if (k+vertices/5 < vertices)
                    addEdge(k + vertices/5, k); // Замыкание цикла
            }
            break;
    }
}

// Добавление ребра от вершины u к вершине v
void Graph::addEdge(size_t u, size_t v) {
    adjList[u].emplace(v);    
    adjMatrix[u][v] = true;     
    edgeList.push_back({u, v});
}


const char* Graph::getType() const {
    switch(type) {
        case GraphType::RANDOM:
            return "Random";
        case GraphType::STRONGLY_CONNECTED:
            return "Strongly connected";
        case GraphType::DISCONNECTED_COMPONENTS:
            return "Disconnected components";
        case GraphType::MANY_CYCLES:
            return "Many cycles";
        default:
            return "Unknown";
    }
}

// Возвращаение количества вершин графа
const size_t Graph::size() const {
    return vertices;
}


std::vector<std::vector<bool>> Graph::getAdjMatrix() const {
    return adjMatrix;
}

std::vector<std::set<size_t>> Graph::getAdjList() const {
    return adjList;
}

std::vector<std::pair<size_t, size_t>> Graph::getEdgeList() const {
    return edgeList;
}

std::vector<std::vector<bool>> Graph::getTransMatrix() const {
    return transMatrix;
}


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

void Graph::printAdjMatrix() {
    std::cout << "Матрица смежности:\n";
    for (const auto& row : adjMatrix) {
        std::cout << "{";
        for (size_t val : row) {
            std::cout << std::setw(2) << val << ", "; 
        }
        std::cout << "}";
        std::cout << std::endl;
    }
}

void Graph::printEdgeList() {
    std::cout << "Список рёбер:\n";
    for (const auto& edge : edgeList) {
        std::cout << "(" << edge.first << " -> " << edge.second << "); "; 
    }
    std::cout << std::endl;
}


void Graph::saveTransitiveClosure(std::vector<std::vector<bool>> R_plus) {
    for (size_t i = 0; i < vertices; i++) {
        for (size_t j = 0; j < vertices; j++) {
            if (R_plus[i][j] != adjMatrix[i][j]) {
                transMatrix[i][j] = true;
                transList.push_back({i, j});  
            }
        }
    }
}

void Graph::saveTransitiveClosure(std::vector<std::shared_ptr<std::unordered_set<size_t>>> V_plus) {
    for (size_t i = 0; i < vertices; ++i) {
        for (size_t j : *V_plus[i]) {
            if (adjMatrix[i][j] == 0) {
                transMatrix[i][j] = true;
                transList.push_back({i, j});  
            }
        }
        transMatrix[i][i] = true; // Рефлексивность
    }
}


// Сохранение графа в формате DOT для визуализации
void Graph::visualize(const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph G {\n";
    for (const auto& edge : edgeList)
        out << "    " << edge.first << " -> " << edge.second << ";\n"; 
    for (const auto& transEdge : transList)
        out << "    " << transEdge.first << " -> " << transEdge.second << "[style = dashed];\n"; 
    out << "}\n";
    out.close();
}