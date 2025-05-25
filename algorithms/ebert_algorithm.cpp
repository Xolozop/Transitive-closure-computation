#include <vector>
#include <stack>
#include <set>
#include <algorithm>

#include "./ebert_algorithm.h"

// Глобальные переменные (как в оригинальном алгоритме Эберта)
std::vector<int> NUMBER;
std::vector<int> LOWLINK;
std::stack<int> S;
size_t NUM = 0;
std::vector<std::vector<bool>> R; // Матрица транзитивного замыкания
SuccessorsList SCCs(listType::CV);

void initializeTransitiveClosure(size_t n) {
    R.assign(n, std::vector<bool>(n, false));
    for (size_t i = 0; i < n; ++i) {
        R[i][i] = true; // Каждая вершина достижима сама из себя
    }
}

void processEdge(size_t v, size_t w) {
    // R[v, *] := R[v, *] or e_w (единичный вектор для w)
    for (size_t j = 0; j < R.size(); ++j) {
        R[v][j] = R[v][j] || (j == w);
    }
}

void processTreeArc(size_t v, size_t w) {
    // R[v, *] := R[v, *] or R[w, *]
    for (size_t j = 0; j < R.size(); ++j) {
        R[v][j] = R[v][j] || R[w][j];
    }
}

void processIntercomponentCrossLink(size_t v, size_t w) {
    // Аналогично processTreeArc
    processTreeArc(v, w);
}

void processVertexOfComponent(size_t x, size_t v) {
    // R[x, *] := R[v, *]
    R[x] = R[v];
}

void DFS(size_t v, const std::vector<std::vector<size_t>>& adjList, Representation& components) {
    NUMBER[v] = LOWLINK[v] = ++NUM;
    S.push(v);

    for (size_t w : adjList[v]) {
        if (NUMBER[w] == 0) {
            // Деревянная дуга
            DFS(w, adjList, components);
            LOWLINK[v] = std::min(LOWLINK[v], LOWLINK[w]);
            processTreeArc(v, w);
        } 
        else if (NUMBER[w] < NUMBER[v]) {
            // Обратная или перекрестная дуга
            bool is_on_stack = false;
            std::stack<int> temp = S;
            while (!temp.empty()) {
                if (temp.top() == w) {
                    is_on_stack = true;
                    break;
                }
                temp.pop();
            }
            
            if (is_on_stack) {
                LOWLINK[v] = std::min(LOWLINK[v], NUMBER[w]);
                processEdge(v, w); // Обработка обратной дуги
            }
            else {
                processIntercomponentCrossLink(v, w); // Обработка перекрестной дуги
            }
        }
    }

    if (LOWLINK[v] == NUMBER[v]) {
        std::set<size_t> component;
        size_t x;
        do {
            x = S.top();
            S.pop();
            component.insert(x);
            processVertexOfComponent(x, v); // Обновляем транзитивное замыкание для компоненты
        } while (x != v);
        components.update(component);
    }
}

Graph findSCCs_Ebert(Graph g, Representation& components) {
    std::vector<std::vector<size_t>> adjList = g.getAdjList(); 
    size_t n = adjList.size();
    
    // Инициализация
    NUMBER.assign(n, 0);
    LOWLINK.assign(n, 0);
    NUM = 0;
    S = std::stack<int>();
    initializeTransitiveClosure(n);

    for (size_t i = 0; i < n; ++i) {
        if (NUMBER[i] == 0) {
            DFS(i, adjList, components);
        }
    }
    return Graph(R);
}