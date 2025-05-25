#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <fstream>
#include <vector> 
#include <iomanip> 
#include <random>

// Определение типов графов для генерации.
enum GraphType {
    RANDOM,              // Случайный граф с произвольными ребрами.
    STRONGLY_CONNECTED,  // Граф, где каждая вершина достижима из любой другой.
    DISCONNECTED_COMPONENTS, // Граф с изолированными компонентами связности.
    MANY_CYCLES          // Граф с большим числом циклических путей.
};

// Реализация ориентированного графа с операциями над ним.
class Graph {
public:
    // Создание графа с заданным числом вершин.
    Graph(size_t vertices);
    
    // Создание графа из матрицы смежности.
    Graph(std::vector<std::vector<bool>> matrix);
    
    // Получение числа вершин графа.
    const size_t size() const;
    
    // Добавление ребра от вершины u к вершине v.
    void addEdge(size_t u, size_t v);
    
    // Получение матрицы смежности графа.
    std::vector<std::vector<bool>> getAdjMatrix() const;
    
    // Получение списка смежности графа.
    std::vector<std::vector<size_t>> getAdjList() const;
    
    // Вывод списка смежности в консоль.
    void printAdjList();
    
    // Вывод матрицы смежности в консоль.
    void printAdjMatrix();
    
    // Вывод списка ребер в консоль.
    void printEdgeList();
    
    // Генерация графа с заданным числом ребер и типом.
    void generate(size_t edges, GraphType type);
    
    // Сохранение визуального представления графа в файл.
    void visualize(const std::string& filename);

private:
    // Хранение числа вершин графа.
    size_t vertices;
    
    // Хранение списка смежности для каждой вершины.
    std::vector<std::vector<size_t>> adjList;
    
    // Хранение матрицы смежности графа.
    std::vector<std::vector<bool>> adjMatrix;
    
    // Хранение списка всех ребер графа.
    std::vector<std::pair<size_t, size_t>> edgeList;
    
    // Генерация случайных чисел для создания графов.
    std::mt19937 gen{std::random_device{}()};
};

#endif