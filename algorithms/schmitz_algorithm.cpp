#include "./schmitz_algorithm.h"

std::vector<size_t> h;          // time of detection + lowlink
std::vector<size_t> rep;        // component representation
std::stack<size_t> s;
size_t current_pos = 0;         // time counter 

void VISIT(size_t x, const std::vector<std::vector<size_t>>& adjList, Representation& components) {
    h[x] = ++current_pos;
    s.push(x);
    size_t xpos = h[x];  // save detection time

    // Обработка смежных вершин
    for (size_t w : adjList[x]) {
        if (h[w] == 0) {
            VISIT(w, adjList, components);
            h[x] = std::min(h[x], h[w]);   // update lowlink
        } else if (h[w] < h[x]) {  // if inversed/crossed edge check if w in stack
            bool on_stack = false;
            auto temp = s;
            while (!temp.empty()) {
                if (temp.top() == w) {
                    on_stack = true;
                    break;
                }
                temp.pop();
            }

            if (on_stack)
                h[x] = std::min(h[x], h[w]);
        }
    }

    // Еif x - component root
    if (h[x] == xpos) {
        std::set<size_t> component;
        size_t w;
        do {
            w = s.top();
            s.pop();
            rep[w] = x;          // choose representation
            h[w] = INT_MAX;      // mark as proccessed
            component.insert(w);
        } while (w != x);
        components.update(component);
    }
}

void findSCCs_Schmitz(const Graph g, Representation& components) {
    const auto& adjList = g.getAdjList();
    size_t n = g.size();
    
    h.assign(n, 0);
    rep.resize(n);
    current_pos = 0;
    s = std::stack<size_t>();

    for (size_t i = 0; i < n; ++i) {
        if (h[i] == 0) // if i is not already proccessed
            VISIT(i, adjList, components);
    }
}