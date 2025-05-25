#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <fstream>
#include <vector> 
#include <iomanip> 
#include <random>

enum GraphType {
    RANDOM,
    STRONGLY_CONNECTED,
    DISCONNECTED_COMPONENTS,
    MANY_CYCLES
};

class Graph {
public:
    Graph(size_t vertices);
    Graph(std::vector<std::vector<bool>> matrix);
    const size_t size() const;
    void addEdge(size_t u, size_t v);
    std::vector<std::vector<bool>> getAdjMatrix() const;
    std::vector<std::vector<size_t>> getAdjList() const;
    void printAdjList();
    void printAdjMatrix();
    void printEdgeList();
    void generate(size_t edges, GraphType type);
    void visualize(const std::string& filename);

private:
    size_t vertices;
    std::vector<std::vector<size_t>> adjList;
    std::vector<std::vector<bool>> adjMatrix;
    std::vector<std::pair<size_t, size_t>> edgeList;
    std::mt19937 gen{std::random_device{}()};
};

#endif 