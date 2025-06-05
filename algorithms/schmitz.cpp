#include "./schmitz.h"

Schmitz::Schmitz(Graph g) {
    adjList = g.getAdjList();
    n = g.size();
    
    number.assign(n, 0);
    root.resize(n);
    for (size_t i = 0; i < n; i++) 
        root[i] = i;
    num = 0;
    S = std::stack<size_t>();
    R_plus.assign(n, std::vector<bool>(n, false));
    
    for (size_t i = 0; i < n; i++)
        R_plus[i][i] = true;
}

void Schmitz::updateTransitiveClosure(size_t x) {
    // Для циклических графов сначала помечаем все вершины компоненты как достижимые друг из друга
    for (size_t u : componentNodes) {
        for (size_t v : componentNodes)
            R_plus[u][v] = true;
    }
    
    // Затем обрабатываем внешние рёбра. Фактически строим граф конденсации
    std::deque<size_t> q;
    for (size_t v : componentNodes) {
        for (size_t neighbor : adjList[v]) {
            size_t w = root[neighbor];
            if (w != x && !R_plus[x][w]) {
                R_plus[x][w] = true;
                q.push_back(w);
            }
        }
    }
    
    // Соединяем корень текущей КСС со всеми наследниками смежных КСС
    while (!q.empty()) {
        size_t w = q.front();
        q.pop_front();
        
        for (size_t k = 0; k < R_plus.size(); k++) {
            if (R_plus[w][k] && !R_plus[x][k]) {
                R_plus[x][k] = true;
                q.push_back(k);
            }
        }
    }
}

void Schmitz::VISIT(size_t x, Representation& components) {
    number[x] = ++num;
    size_t xpos = number[x];
    S.push(x);
    
    for (size_t w : adjList[x]) {
        if (number[w] == 0) {
            VISIT(w, components);
            number[x] = std::min(number[x], number[w]);
        } else if (number[w] < number[x]) {
            bool on_stack = false;
            auto temp = S;
            while (!temp.empty()) {
                if (temp.top() == w) {
                    on_stack = true;
                    break;
                }
                temp.pop();
            }
            if (on_stack)
                number[x] = std::min(number[x], number[w]);
        }
    }
    
    // Если x - корень компоненты
    if (number[x] == xpos) {
        std::set<size_t> component;
        componentNodes.clear(); // Очищаем перед использованием
        size_t w;
        
        do {
            w = S.top();
            S.pop();
            root[w] = x;
            number[w] = INT_MAX;
            component.insert(w);
            componentNodes.push_back(w);
        } while (w != x);
        
        components.update(component);
        updateTransitiveClosure(x);
        
        // Обновляем R_plus для всех вершин компоненты
        for (size_t u : componentNodes) {
            for (size_t k = 0; k < n; k++)
                // Присваиваем внешние связи корня всей КСС
                R_plus[u][k] = R_plus[u][k] || R_plus[x][k];  
        }
    }
}

void Schmitz::getTransitiveClosure(Graph& g, Representation& components) {
    for (size_t i = 0; i < n; i++) {
        if (number[i] == 0)
            VISIT(i, components);
    }
    
    g.saveTransitiveClosure(R_plus);
}