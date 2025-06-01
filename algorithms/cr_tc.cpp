#include "./cr_tc.h"

CR_TC::CR_TC(Graph g) {
    n = g.size();
    adjList = g.getAdjList();

    number.assign(n, 0);
    root.assign(n, 0);
    S = std::stack<size_t>();

    succ.resize(n);
    comp.resize(n);
    for (auto& s : succ) {
        s = std::make_shared<std::unordered_set<size_t>>();
    }
}

void CR_TC::getTransitiveClosure(Graph& g, Representation& components) {
    for (size_t v = 0; v < n; ++v) {
        if (number[v] == 0)
            cr_tc(v, components);
    }
    
    g.saveTransitiveClosure(succ);
}

void CR_TC::cr_tc(size_t v, Representation& components) {
    number[v] = root[v] = ++num;
    S.push(v);
    comp[v] = std::numeric_limits<size_t>::max();
    
    succ[v]->clear();
    for (size_t w : adjList[v]) {
        succ[v]->insert(w);
        if (w == v) continue; // Пропускаем петли
        
        // если вершина ещё не посещалась - посещаем
        if (number[w] == 0) {
            cr_tc(w, components);
            root[v] = std::min(root[v], root[w]);
        } 
        
        // Добавляем саксессоры компоненты w, если она уже обработана (принадлежит какой-либо компоненте)
            // иными словами если имеется путь из v в какую-то вершину, то имеется и путь из v в вершины, смежные с ней
            // если же w не принадлежит существующей ксс, то она состоит с v в одной компоненте
        if (comp[w] != std::numeric_limits<size_t>::max()) {
            for (size_t s : *succ[w])
                succ[v]->insert(s);
        } else{
            root[v] = std::min(root[v], number[w]);
        }
    }

    // Если v - корень компоненты
    if (root[v] == number[v]) {
        std::set<size_t> component;
        size_t w;
        auto component_successors = std::make_shared<std::unordered_set<size_t>>();
        
        do {
            w = S.top();
            S.pop();
            comp[w] = component_counter;
            component.insert(w);
            
            // Объединяем successors всех вершин компоненты
            for (size_t s : *succ[w])
                component_successors->insert(s);
        } while (w != v);

        // Присваиваем всем вершинам компоненты общие successors
        for (size_t u : component) {
            succ[u] = component_successors;
        }
        
        components.update(component);
        component_counter++;
    }
}