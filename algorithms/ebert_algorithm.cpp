#include <vector>
#include <stack>
#include <set>
#include <algorithm>

#include "./ebert_algorithm.h"

// Глобальные переменные для алгоритма Эберта
std::vector<int> NUMBER; // Номер вершины при обходе DFS
std::vector<int> LOWLINK; // Наименьший достижимый номер вершины
std::stack<int> S; // Стек вершин текущей компоненты
size_t NUM = 0; // Счётчик номеров вершин
std::vector<std::vector<bool>> R; // Матрица транзитивного замыкания
SuccessorsList SCCs(listType::CV); // Список компонент связности

// Инициализация матрицы транзитивного замыкания (n x n)
void initializeTransitiveClosure(size_t n) {
    R.assign(n, std::vector<bool>(n, false));
    for (size_t i = 0; i < n; ++i) {
        R[i][i] = true; // Вершина достижима из себя
    }
}

// Обновление достижимости для ребра v -> w
void processEdge(size_t v, size_t w) {
    for (size_t j = 0; j < R.size(); ++j) {
        R[v][j] = R[v][j] || (j == w); // j достижим из v, если j = w
    }
}

// Обновление достижимости для дуги дерева v -> w
void processTreeArc(size_t v, size_t w) {
    for (size_t j = 0; j < R.size(); ++j) {
        R[v][j] = R[v][j] || R[w][j]; // j достижим из v, если достижим из w
    }
}

// Обработка перекрестного ребра между компонентами
void processIntercomponentCrossLink(size_t v, size_t w) {
    processTreeArc(v, w); // Аналогично дуге дерева
}

// Обновление достижимости для вершины x в компоненте v
void processVertexOfComponent(size_t x, size_t v) {
    R[x] = R[v]; // Копируем достижимость v для x
}

// DFS для поиска компонент связности
void DFS(size_t v, const std::vector<std::vector<size_t>>& adjList, Representation& components) {
    NUMBER[v] = LOWLINK[v] = ++NUM; // Присваиваем номер и lowlink
    S.push(v); // Добавляем в стек

    for (size_t w : adjList[v]) {
        if (NUMBER[w] == 0) {
            // Дуга дерева: w не посещена
            DFS(w, adjList, components);
            LOWLINK[v] = std::min(LOWLINK[v], LOWLINK[w]); // Обновляем lowlink
            processTreeArc(v, w);
        } else if (NUMBER[w] < NUMBER[v]) {
            // Обратное или перекрестное ребро
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
                // Обратное ребро: обновляем lowlink
                LOWLINK[v] = std::min(LOWLINK[v], NUMBER[w]);
                processEdge(v, w);
            } else {
                // Перекрестное ребро
                processIntercomponentCrossLink(v, w);
            }
        }
    }

    // Если v — корень компоненты
    if (LOWLINK[v] == NUMBER[v]) {
        std::set<size_t> component;
67
        size_t x;
        do {
            x = S.top();
            S.pop();
            component.insert(x);
            processVertexOfComponent(x, v);
        } while (x != v);
        components.update(component); // Сохраняем компоненту
    }
}

// Поиск сильно связанных компонент
Graph findSCCs_Ebert(Graph g, Representation& components) {
    std::vector<std::vector<size_t>> adjList = g.getAdjList();
    size_t n = adjList.size();

    // Инициализация
    NUMBER.assign(n, 0);
    LOWLINK.assign(n, 0);
    NUM = 0;
    S = std::stack<int>();
    initializeTransitiveClosure(n);

    // Обход всех вершин
    for (size_t i = 0; i < n; ++i) {
        if (NUMBER[i] == 0) {
            DFS(i, adjList, components);
        }
    }

    return Graph(R); // Возвращаем граф транзитивного замыкания
}