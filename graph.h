#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <fstream>
#include <vector> 
#include <iomanip> 
#include <set>
#include <random>
#include <memory>
#include <unordered_set>

// Определение типов графов для генерации
enum GraphType {
    RANDOM,                   // Случайный граф с произвольными ребрами
    STRONGLY_CONNECTED,       // Граф, где каждая вершина достижима из любой другой
    DISCONNECTED_COMPONENTS,  // Граф с изолированными компонентами связности
    MANY_CYCLES,               // Граф с большим числом циклических путей
    ACYCLIC
};

class Graph {
public:
    Graph(size_t vertices);
    Graph(std::vector<std::vector<bool>> matrix); // Создание графа из матрицы смежности

    void generate(GraphType type, double edgeProbability=0.3);
    void addEdge(size_t u, size_t v);
    
    std::vector<std::pair<size_t, size_t>> cmp(Graph g); 
    
    const char* getType() const; // Получение названия типа графа
    const size_t size() const; // Получение числа вершин графа

    std::vector<std::vector<bool>> getAdjMatrix() const;
    std::vector<std::set<size_t>> getAdjList() const;
    std::vector<std::pair<size_t, size_t>> getEdgeList() const;

    std::vector<std::vector<bool>> getTransMatrix() const;
    std::vector<std::set<size_t>> getTransList() const;

    void printAdjList();
    void printAdjMatrix();
    void printEdgeList();

    void saveTransitiveClosure(std::vector<std::vector<bool>> R_plus);
    void saveTransitiveClosure(std::vector<std::shared_ptr<std::unordered_set<size_t>>> V_plus);
    
    void visualize(const std::string& filename);

private:
    size_t vertices;
    GraphType type;
    
    std::vector<std::set<size_t>> adjList;
    std::vector<std::vector<bool>> adjMatrix;
    std::vector<std::pair<size_t, size_t>> edgeList;

    // Матрица транзитивного замыкания
    std::vector<std::vector<bool>> transMatrix;
    std::vector<std::pair<size_t, size_t>> transList;
    
    // Генерация случайных чисел для создания графов
    std::mt19937 gen{std::random_device{}()};
};

#endif