#include "./schmitz_algorithm.h"


std::vector<size_t> h;   // Номер обнаружения и lowlink для вершин
std::vector<size_t> rep; // Представитель компоненты для каждой вершины
std::stack<size_t> s;    // Стек вершин текущей компоненты
size_t current_pos = 0;  // Счётчик времени обнаружения

// Обход вершины x в глубину (DFS)
void VISIT(size_t x, const std::vector<std::vector<size_t>>& adjList, Representation& components) {
    h[x] = ++current_pos; // Присваиваем номер обнаружения
    s.push(x);           // Добавляем вершину в стек
    size_t xpos = h[x];  // Сохраняем время обнаружения

    // Проверяем всех соседей вершины x
    for (size_t w : adjList[x]) {
        if (h[w] == 0) {
            // Если w не посещена — это дуга дерева
            VISIT(w, adjList, components);
            h[x] = std::min(h[x], h[w]); // Обновляем lowlink
        } else if (h[w] < h[x]) {
            // Если w посещена раньше x — это обратное или перекрестное ребро
            bool on_stack = false;
            auto temp = s;
            while (!temp.empty()) {
                if (temp.top() == w) {
                    on_stack = true; // w в стеке
                    break;
                }
                temp.pop();
            }
            if (on_stack) {
                // Если w в стеке — это обратное ребро
                h[x] = std::min(h[x], h[w]); // Обновляем lowlink
            }
        }
    }

    // Если x — корень сильно связной компоненты
    if (h[x] == xpos) {
        std::set<size_t> component; // Новая компонента
        size_t w;
        do {
            w = s.top();        // Извлекаем вершину из стека
            s.pop();
            rep[w] = x;         // Назначаем x представителем компоненты
            h[w] = INT_MAX;     // Помечаем вершину как обработанную
            component.insert(w); // Добавляем в компоненту
        } while (w != x);
        components.update(component); // Сохраняем компоненту
    }
}

// Поиск сильно связанных компонент по алгоритму Шмитца
void findSCCs_Schmitz(const Graph g, Representation& components) {
    const auto& adjList = g.getAdjList(); // Получаем список смежности
    size_t n = g.size();                  // Количество вершин

    // Инициализация
    h.assign(n, 0);        // Сбрасываем номера вершин
    rep.resize(n);         // Готовим массив представителей
    current_pos = 0;       // Сбрасываем счётчик времени
    s = std::stack<size_t>(); // Очищаем стек

    // Обходим все вершины графа
    for (size_t i = 0; i < n; ++i) {
        if (h[i] == 0) { // Если вершина не посещена
            VISIT(i, adjList, components); // Запускаем DFS
        }
    }
}