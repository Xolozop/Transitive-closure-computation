#include "stack_tc.h"

STACK_TC::STACK_TC(Graph g) {
    n = g.size();
    adjList = g.getAdjList();

    number.assign(n, 0);
    root.assign(n, 0);
    S = std::stack<size_t>();

    VStack = std::stack<size_t>();
    SavedHeight.assign(n, 0);
    self_loop.assign(n, false);

    comp.resize(n);
    succ.resize(n);

    component_counter = 0;
    num = 0;

    std::cout << "n = " << n << std::endl;
    for (auto& s : succ) 
        s = std::make_shared<std::unordered_set<size_t>>();
}

void STACK_TC::getTransitiveClosure(Graph& g, Representation& components) {
    for (size_t v = 0; v < n; ++v) {
        if (number[v] == 0) stack_tc(v, components);
    }

    puts("ok");
    g.saveTransitiveClosure(succ);
}

void STACK_TC::stack_tc(size_t v, Representation& components) {
    root[v] = number[v] = ++num;
    comp[v] = std::numeric_limits<size_t>::max();

    VStack.push(v);
    S.push(v);

    SavedHeight[v] = VStack.size();

    self_loop[v] = false;

    for (size_t w : adjList[v]) {
        if (w == v) {
            self_loop[v] = true;
            continue;
        }

        if (number[w] == 0) {
            stack_tc(w, components);
            if (comp[w] == std::numeric_limits<size_t>::max()) {
                root[v] = std::min(root[v], root[w]);
            }
        } else if (comp[w] == std::numeric_limits<size_t>::max()) {
            root[v] = std::min(root[v], number[w]);
        }
    }

    if (root[v] == number[v]) {
        std::set<size_t> C;

        bool flag = VStack.top() != v || self_loop[v];

        while (S.size() != SavedHeight[v]) {
            size_t X = S.top();
            S.pop();
            if (succ[v]->find(X) == succ[v]->end()) {
                succ[v]->insert(X);
                for (size_t s : *succ[X]) {
                    succ[v]->insert(s);
                }
            }
        }

        size_t w;
        do {
            w = VStack.top();
            VStack.pop();
            comp[w] = component_counter;
            C.insert(w);
            succ[w] = succ[v];
        } while (w != v);

        if (C.size() > 1) {
            succ[v]->insert(v);
            for (size_t u : C) succ[u] = succ[v];
        }

        if (flag) {
            C.insert(v);
            succ[v]->clear();
            if (self_loop[v]) 
                succ[v]->insert(v);
            C.clear();
        } else {
            succ[v]->clear();
        }
        
        components.update(C);
        component_counter++;
    }
}