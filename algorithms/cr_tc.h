#ifndef CR_TC_H
#define CR_TC_H

#include <climits>

#include "../representations/succ_list.h"
#include "./algorithm.h"

class CR_TC : public Algorithm {
public:
    CR_TC(Graph g);
    void getTransitiveClosure(Graph& g, Representation& components) override;

private:
    void cr_tc(size_t v, Representation& components);
    void processEdge(size_t v, size_t w);
    
    std::vector<std::shared_ptr<std::unordered_set<size_t>>> succ; // список саксессоров
    std::vector<size_t> comp;  // comp[v] - номер компоненты сильной связности для v
    std::vector<bool> self_loop;  // comp[v] - номер компоненты сильной связности для v
    size_t component_counter; 
};

#endif