#ifndef SCHMITZ_H
#define SCHMITZ_H

#include <climits>

#include "./algorithm.h"

class Schmitz : public Algorithm {
public:
    Schmitz(Graph g);
    void getTransitiveClosure(Graph& g, Representation& components) override;

private:
    void VISIT(size_t v, Representation& components);
    void updateTransitiveClosure(size_t v);

    std::vector<size_t> componentNodes;
};

#endif