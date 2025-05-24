#include "./ebert_algorithm.h"

std::vector<int> NUMBER;
std::vector<int> LOWLINK;
std::stack<int> S;
size_t NUM = 0;
SuccessorsList SCCs(listType::CV);

void DFS(size_t v, const std::vector<std::vector<size_t>>& adjList, Representation& components) {
    NUMBER[v] = ++NUM;
    LOWLINK[v] = NUMBER[v];
    S.push(v);

    for (size_t w : adjList[v]) {
        if (NUMBER[w] == 0) {
            DFS(w, adjList, components);
            LOWLINK[v] = std::min(LOWLINK[v], LOWLINK[w]);
        } 
        else if (NUMBER[w] < NUMBER[v]) {
            bool is_on_stack = false;
            std::stack<int> temp = S;
            while (!temp.empty()) {
                if (temp.top() == w) {
                    is_on_stack = true;
                    break;
                }
                temp.pop();
            }
            if (is_on_stack)
                LOWLINK[v] = std::min(LOWLINK[v], NUMBER[w]);
        }
    }

    if (LOWLINK[v] == NUMBER[v]) {
        std::vector<size_t> component;
        size_t x;
        do {
            x = S.top();
            S.pop();
            component.push_back(x);
        } while (x != v);
        components.update(component);
    }
}

void findSCCs_Ebert(Graph g, Representation& components) {
    std::vector<std::vector<size_t>> adjList = g.getAdjList(); 
    size_t n = adjList.size();
    NUMBER.assign(n, 0);
    LOWLINK.resize(n);
    NUM = 0;

    for (size_t i = 0; i < n; ++i) {
        if (NUMBER[i] == 0)
            DFS(i, adjList, components);
    }
}