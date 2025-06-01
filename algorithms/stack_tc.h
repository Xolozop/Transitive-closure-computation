#ifndef STACK_TC_H
#define STACK_TC_H

#include <vector>
#include <stack>
#include <limits>
#include <memory>
#include <unordered_set>
#include <algorithm>

#include "algorithm.h"
#include "../graph.h"
#include "../representations/representation.h"

class STACK_TC : public Algorithm {
public:
    STACK_TC(Graph g);
    void getTransitiveClosure(Graph& g, Representation& components) override;

private:
    void stack_tc(size_t v, Representation& components);
    
    std::vector<std::shared_ptr<std::unordered_set<size_t>>> succ;
    std::vector<bool> self_loop;
    std::vector<size_t> comp;  // comp[v] - ID компоненты сильной связности для v
    size_t component_counter;
    std::stack<size_t> VStack;
    std::vector<size_t> SavedHeight;
};

#endif