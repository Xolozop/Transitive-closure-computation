#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <climits>
#include <iostream>

#include "./cr_tc.h"

struct CRTCState {
    std::vector<size_t> Root;
    std::vector<size_t> Comp;
    std::vector<std::set<size_t>> Succ;
    std::vector<bool> SelfLoop;
    std::vector<bool> Visited;
    std::stack<size_t> vertexStack;
    size_t componentCounter;
    
    CRTCState(size_t n) : 
        Root(n, 0),
        Comp(n, INT_MAX),
        Succ(n*2),
        SelfLoop(n, false),
        Visited(n, false),
        componentCounter(0) {}
};

void processEdgeCRTC(size_t v, size_t w, const std::vector<std::vector<size_t>>& adjList, 
                    CRTCState& state) {
    if (w == v) {
        state.SelfLoop[v] = true;
    } else {
        if (!state.Visited[w]) {
            // Root[v] будет обновлен после рекурсивного вызова
        } else {
            bool isOnStack = false;
            auto tempStack = state.vertexStack;
            while (!tempStack.empty()) {
                if (tempStack.top() == w) {
                    isOnStack = true;
                    break;
                }
                tempStack.pop();
            }

            if (isOnStack && state.Succ[state.Root[v]].count(state.Comp[w]) == 0) {
                state.Succ[state.Root[v]].insert(state.Comp[w]);
                if (state.Comp[w] < state.Succ.size()) {
                    for (size_t s : state.Succ[state.Comp[w]]) {
                        if (s < state.Succ.size()) {
                            state.Succ[state.Root[v]].insert(s);
                        }
                    }
                }
            }
        }
    }
}

void CR_TC(size_t v, const std::vector<std::vector<size_t>>& adjList, 
          CRTCState& state, Representation& components) {
    state.Root[v] = v;
    state.Comp[v] = INT_MAX; // Nil
    state.Visited[v] = true;
    state.vertexStack.push(v);
    state.Succ[v].clear();
    state.SelfLoop[v] = false;

    for (size_t w : adjList[v]) {
        
        processEdgeCRTC(v, w, adjList, state);
        
        if (!state.Visited[w]) {
            CR_TC(w, adjList, state, components);
            state.Root[v] = std::min(state.Root[v], state.Root[w]);
        }
    }

    if (state.Root[v] == v) {
        std::set<size_t> component;
        size_t w;
        bool isComponent = false;
        
        do {
            if (state.vertexStack.empty()) {
                std::cerr << "stack is empty" << v << std::endl;
                break;
            }
            w = state.vertexStack.top();
            state.vertexStack.pop();
            state.Comp[w] = state.componentCounter;
            component.insert(w);
            
            if (w != v && !state.Succ[w].empty()) {
                for (size_t s : state.Succ[w]) {
                    if (s < state.Succ.size()) {
                        state.Succ[v].insert(s);
                    }
                }
            }
            
            if (w != v || state.SelfLoop[v]) {
                isComponent = true;
            }
        } while (w != v);

        if (isComponent) {
            state.Succ[state.componentCounter].insert(state.componentCounter);
        }
        
        components.update(component);
        state.componentCounter++;
    }
}

Graph findSCCs_CRTC(const Graph& g, Representation& components) {
    const auto& adjList = g.getAdjList();
    size_t n = adjList.size();
    
    if (n == 0) {
        return Graph(0);
    }

    CRTCState state(n);

    for (size_t v = 0; v < n; ++v) {
        if (!state.Visited[v]) {
            CR_TC(v, adjList, state, components);
        }
    }

    std::vector<std::vector<bool>> tcMatrix(n, std::vector<bool>(n, false));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (g.getAdjMatrix()[i][j]) {
                tcMatrix[i][j] = true;
            }
        }
    }

    return Graph(tcMatrix);
}