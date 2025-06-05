#include "./ebert.h"

Ebert::Ebert(Graph g) {
    n = g.size();
    adjList = g.getAdjList();
    number.assign(n, 0);
    root.assign(n, 0);
    num = 0;
    S = std::stack<size_t>();
    R_plus.assign(n, std::vector<bool>(n, false));
    for (size_t i = 0; i < n; ++i)
        R_plus[i][i] = true; // Вершина достижима из себя
}

void Ebert::DFS(size_t v, Representation& components) {
    number[v] = root[v] = ++num; // Присваиваем номер и root
    S.push(v); // Добавляем в стек

    for (size_t w : adjList[v]) {
        if (number[w] == 0) {
            // Дуга дерева: w не посещена
            Ebert::DFS(w, components);
            root[v] = std::min(root[v], root[w]); // Обновляем root
            processTreeArc(v, w);
        } else if (number[w] < number[v]) {
            // Обратное или перекрестное ребро
            bool is_on_stack = false;
            std::stack<size_t> temp = S;
            while (!temp.empty()) {
                if (temp.top() == w) {
                    is_on_stack = true;
                    break;
                }
                temp.pop();
            }
            
            if (is_on_stack) {
                // Обратное ребро: обновляем root
                root[v] = std::min(root[v], number[w]);
                processEdge(v, w);
            } else {
                // Перекрестное ребро
                processIntercomponentCrossLink(v, w);
            }
        }
    }

    // Если v — корень компоненты
    if (root[v] == number[v]) {
        std::set<size_t> component;
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

void Ebert::getTransitiveClosure(Graph& g, Representation& components) {
    for (size_t i = 0; i < n; ++i) {
        if (number[i] == 0)
            Ebert::DFS(i, components);
    }

    g.saveTransitiveClosure(R_plus);
}

// Обновление достижимости для ребра v -> w
void Ebert::processEdge(size_t v, size_t w) {
    for (size_t j = 0; j < R_plus.size(); ++j)
        R_plus[v][j] = R_plus[v][j] || (j == w); // j достижим из v, если j = w
}

// Обновление достижимости для дуги дерева v -> w
void Ebert::processTreeArc(size_t v, size_t w) {
    for (size_t j = 0; j < R_plus.size(); ++j)
        R_plus[v][j] = R_plus[v][j] || R_plus[w][j]; // j достижим из v, если достижим из w
}

// Обработка перекрестного ребра между компонентами
void Ebert::processIntercomponentCrossLink(size_t v, size_t w) {
    processTreeArc(v, w); // Аналогично дуге дерева
}

// Обновление достижимости для вершины x в компоненте v
void Ebert::processVertexOfComponent(size_t x, size_t v) {
    R_plus[x] = R_plus[v]; // Копируем достижимость v для x
}