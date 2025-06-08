#ifndef WARSHALL_H
#define WARSHALL_H

#include "algorithm.h"
#include "../graph.h"
#include "../representations/representation.h"

class Warshall : public Algorithm {
public:
    Warshall(Graph g);
    void getTransitiveClosure(Graph& g, Representation& repr) override;
};

#endif