#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>

#include "graph.h"
#include "algorithms/algorithm.h"
#include "algorithms/ebert.h"
#include "algorithms/cr_tc.h"
#include "algorithms/stack_tc.h"
#include "algorithms/schmitz_algorithm.h"
#include "representations/representation.h"
#include "representations/intervals.h"
#include "representations/succ_list.h"
#include "./utils.h"

void run_tests() {
    const GraphType types[] = {RANDOM, DISCONNECTED_COMPONENTS, STRONGLY_CONNECTED, MANY_CYCLES};
    const size_t sizes[] = {1000, 2000, 3000};
    for (GraphType type : types) {
        for (size_t size : sizes) {
            Graph g(size);
            g.generate(type, 0.15);
            Graph g_copy1 = g;
            Graph g_copy2 = g;
            SuccessorsList SCC(listType::CV);

            Timer timer;
            timer.start();
            Ebert alg_ebert(g);
            alg_ebert.getTransitiveClosure(g, SCC);
            double time_ebert = timer.stop();

            timer.start();
            CR_TC alg_cr(g);
            alg_cr.getTransitiveClosure(g, SCC);
            double time_cr = timer.stop();

            timer.start();
            STACK_TC alg_stack(g);
            alg_stack.getTransitiveClosure(g, SCC);
            double time_stack = timer.stop();
        }
    }
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(3, 1);
    g.addEdge(4, 3);
    g.visualize("graph.dot");
    system("dot -Tpng graph.dot -o graph.png"); // <-- need to install graphvi
    Graph g2 = g;
    Graph g3 = g;

    SuccessorsList gCC(CC);
    CR_TC alg(g);
    alg.getTransitiveClosure(g, gCC);
    gCC.printSCC();
    g.visualize("results/res.dot");
    system("dot -Tpng results/res.dot -o results/res.png"); 

    Intervals gVV2;
    Ebert alg2(g2);
    alg2.getTransitiveClosure(g2, gVV2);
    gVV2.printSCC();
    g2.visualize("results/res2.dot");
    system("dot -Tpng results/res2.dot -o results/res2.png");

    Intervals gVV3;
    STACK_TC alg3(g3);
    alg3.getTransitiveClosure(g3, gVV3);
    gVV3.printSCC();
    g3.visualize("results/res3.dot");
    system("dot -Tpng results/res3.dot -o results/res3.png");

    auto res = g2.cmp(g);
    if (!res.empty()) {
        printf("Difference Ebert & CR_TC:\n");
        for (std::pair<size_t, size_t> i : res)
            printf("%d -> %d\n", i.first, i.second);
    }

    res = g2.cmp(g3);
    if (!res.empty()) {
        printf("Difference Ebert & STACK_TC:\n");
        for (std::pair<size_t, size_t> i : res)
            printf("%d -> %d\n", i.first, i.second);
    }
    return 0;
}