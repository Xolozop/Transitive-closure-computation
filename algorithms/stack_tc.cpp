#include "./stack_tc.h"

STACK_TC::STACK_TC(Graph g) {
    n = g.size();
    adjList = g.getAdjList();
    number.assign(n, 0);
    self_loop.assign(n, 0);
    root.assign(n, 0);
    SavedHeight.assign(n, 0);
    S = std::stack<size_t>();
    VStack = std::stack<size_t>();
    comp.assign(n, std::numeric_limits<size_t>::max());
    succ.resize(n);
    component_counter = 0;
    for (auto& s : succ)
        s = std::make_shared<std::unordered_set<size_t>>();
}

void STACK_TC::getTransitiveClosure(Graph& g, Representation& components) {
    for (size_t v = 0; v < n; ++v) {
        if (number[v] == 0)
            stack_tc(v, components);
    }
    
    g.saveTransitiveClosure(succ);
}

void STACK_TC::stack_tc(size_t v, Representation& components) {
    number[v] = root[v] = ++num;
    S.push(v);
    VStack.push(v);
    comp[v] = std::numeric_limits<size_t>::max();
    SavedHeight[v] = S.size();
    self_loop[v] = false;

    for (size_t w : adjList[v]) {
        succ[v]->insert(w);  // Добавляем прямое ребро
        
        if (w == v) {
            self_loop[v] = true;
            continue;
        }

        if (number[w] == 0) {
            // Tree edge
            stack_tc(w, components);
            root[v] = std::min(root[v], root[w]);
            
            // Добавляем successors дочерней компоненты
            for (size_t s : *succ[w])
                succ[v]->insert(s);
        } else if (comp[w] == std::numeric_limits<size_t>::max()) {
            // Back edge - важное изменение!
            root[v] = std::min(root[v], number[w]);
            succ[v]->insert(w);  // Явно добавляем обратное ребро
            for (size_t s : *succ[w])  // И все его successors
                succ[v]->insert(s);
        } else {
            // Cross edge
            for (size_t s : *succ[w])
                succ[v]->insert(s);
        }
    }

    if (root[v] != number[v])
        return;

    // Обработка компоненты сильной связности
    std::set<size_t> component;
    auto component_successors = std::make_shared<std::unordered_set<size_t>>();

    // Собираем вершины компоненты
    size_t w;
    do {
        w = VStack.top();
        VStack.pop();
        comp[w] = component_counter;
        component.insert(w);
        
        // Добавляем всех successors вершин компоненты
        for (size_t s : *succ[w]) {
            if (component.find(s) == component.end()) {
                component_successors->insert(s);
            }
        }
    } while (w != v);

    // Для циклических компонент добавляем все внутренние связи
    if (component.size() > 1) {
        for (size_t u : component) {
            for (size_t v_in : component) {
                if (u != v_in) {
                    component_successors->insert(v_in);
                }
            }
        }
    }

    // Обновляем successors для всех вершин компоненты
    for (size_t u : component) {
        succ[u] = component_successors;
    }

    components.update(component);
    component_counter++;
}