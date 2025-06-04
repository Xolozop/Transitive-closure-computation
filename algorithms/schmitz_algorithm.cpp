#include "./schmitz_algorithm.h"

std::vector<size_t> h;   // Номер обнаружения и lowlink для вершин
std::vector<size_t> rep; // Представитель компоненты для каждой вершины
std::stack<size_t> s;    // Стек вершин текущей компоненты
size_t current_pos = 0;  // Счётчик времени обнаружения
std::vector<std::vector<bool>> R_plus; // Матрица транзитивного замыкания

// First subalgorithm (Fig 4.1) for transitive closure
void transitive_closure_subalgorithm_1(size_t x, const std::vector<std::set<size_t>>& adjList) {
    size_t v, w;
    std::stack<size_t> s_copy = s; // Work with a copy of the stack
    
    // Process vertices from xpos to top (which are in the stack)
    while (!s_copy.empty()) {
        size_t current_vertex = s_copy.top();
        s_copy.pop();
        
        for (size_t v : adjList[current_vertex]) {
            w = rep[v];
            if (w != x && !R_plus[x][w]) {
                // R^+(x, *) := R^+(x, *) ∨ R^+(w, *)
                for (size_t k = 0; k < R_plus.size(); ++k) {
                    R_plus[x][k] = R_plus[x][k] || R_plus[w][k];
                }
            }
            R_plus[x][w] = true;
        }
    }
}
void updateTransitiveClosure(std::size_t x, const std::vector<std::set<std::size_t>>& adjList, const std::vector<std::size_t>& componentNodes) {
    std::deque<std::size_t> q; // Очередь для вершин, которые нужно обработать

    // Первый проход: формирование очереди q
    for (size_t v : componentNodes) {
        for (size_t neighbor : adjList[v]) {
            std::size_t w = rep[neighbor]; // Представитель соседа
            if (w == x) {
                R_plus[x][w] = true; // Петля x → x
            } else {
                // Проверяем, нужно ли добавлять w в очередь
                bool should_add = true;
                for (size_t y : q) {
                    if (R_plus[y][w] || (y == w)) {
                        should_add = false;
                        break;
                    }
                }
                if (should_add) {
                    q.push_front(w); // Добавляем w в начало очереди
                }
            }
        }
    }

    // Второй проход: обновление R⁺ на основе очереди q
    while (!q.empty()) {
        std::size_t w = q.front();
        q.pop_front();

        if (!R_plus[x][w]) {
            // R⁺(x, *) = R⁺(x, *) ∨ R⁺(w, *)
            for (std::size_t k = 0; k < R_plus.size(); ++k) {
                R_plus[x][k] = R_plus[x][k] || R_plus[w][k];
            }
            R_plus[x][w] = true; // Устанавливаем связь x → w
        }
    }
}

void VISIT(size_t x, const std::vector<std::set<size_t>>& adjList, Representation& components) {
    h[x] = ++current_pos; // Устанавливаем время обнаружения
    s.push(x);            // Добавляем вершину в стек
    size_t xpos = h[x];   // Запоминаем начальное время обнаружения x

    // Обход соседей вершины x
    for (size_t w : adjList[x]) {
        if (h[w] == 0) { // Если сосед не посещён
            VISIT(w, adjList, components); // Рекурсивный вызов DFS
            h[x] = std::min(h[x], h[w]);   // Обновляем lowlink
        } else if (h[w] < h[x]) { // Если сосед уже посещён и находится выше в стеке
            bool on_stack = false;
            auto temp = s;
            while (!temp.empty()) { // Проверяем, есть ли w в стеке
                if (temp.top() == w) {
                    on_stack = true;
                    break;
                }
                temp.pop();
            }
            if (on_stack) {
                h[x] = std::min(h[x], h[w]); // Обновляем lowlink
            }
        }
    }

    // Если x — корень компоненты
    if (h[x] == xpos) {
        std::set<size_t> component;         // Множество вершин компоненты
        std::vector<size_t> componentNodes; // Список вершин для обработки
        size_t w;
        do {
            w = s.top(); s.pop();
            rep[w] = x;          // Устанавливаем представителя
            h[w] = INT_MAX;      // Помечаем как обработанную
            component.insert(w);  // Добавляем в компоненту
            componentNodes.push_back(w);
        } while (w != x);

        components.update(component); // Сохраняем компоненту
        transitive_closure_subalgorithm_1(x, adjList); // Обновляем R⁺
        updateTransitiveClosure(x, adjList, componentNodes); // Дополняем R⁺
    }
}


// Поиск сильно связанных компонент по алгоритму Шмитца
Graph findSCCs_Schmitz(const Graph g, Representation& components) {
    const auto& adjList = g.getAdjList(); // Получаем список смежности
    size_t n = g.size();                  // Количество вершин

    // Инициализация
    h.assign(n, 0);        // Сбрасываем номера вершин
    rep.resize(n);         // Готовим массив представителей
    current_pos = 0;       // Сбрасываем счётчик времени
    s = std::stack<size_t>(); // Очищаем стек
    // R_plus = g.getAdjMatrix();

    R_plus.assign(n, std::vector<bool>(n, false));
    for (size_t i = 0; i < n; ++i)
        R_plus[i][i] = true; // Вершина достижима из себя

    // Обходим все вершины графа
    for (size_t i = 0; i < n; ++i) {
        if (h[i] == 0) { // Если вершина не посещена
            VISIT(i, adjList, components); // Запускаем DFS
        }
    }
    return Graph(R_plus);
}