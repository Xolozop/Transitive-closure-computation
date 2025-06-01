#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stack>

#include "../representations/representation.h"
#include "../graph.h"

class Algorithm {
public:
    Algorithm() = default;
    Algorithm(Graph g) {};
    virtual void getTransitiveClosure(Graph& g, Representation& components) = 0;
protected:
    size_t n;
    std::vector<std::set<size_t>> adjList;

    std::vector<size_t> number;                // Номер вершины при обходе DFS
    std::vector<size_t> root;                  // Корень текущей компоненты
    std::stack<size_t> S;                      // Стек вершин текущей компоненты
    size_t num;                                // Счётчик номеров вершин
    
    std::vector<std::vector<bool>> R_plus;     // Матрица транзитивного замыкания
};

#endif