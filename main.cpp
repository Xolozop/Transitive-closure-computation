#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>

#include "graph.h"
#include "algorithms/algorithm.h"
#include "algorithms/ebert.h"
#include "algorithms/schmitz.h"
#include "algorithms/cr_tc.h"
#include "algorithms/stack_tc.h"
#include "representations/representation.h"
#include "representations/intervals.h"
#include "representations/succ_list.h"
#include "./utils.h"

const char* getType(GraphType t) {
    switch(t) {
        case GraphType::RANDOM:
            return "Random";
        case GraphType::STRONGLY_CONNECTED:
            return "Strongly connected";
        case GraphType::DISCONNECTED_COMPONENTS:
            return "Disconnected components";
        case GraphType::MANY_CYCLES:
            return "Many cycles";
        default:
            return "Unknown";
    }
}

void run_tests() {
    const GraphType types[] = {RANDOM, STRONGLY_CONNECTED, MANY_CYCLES};
    for (GraphType type : types) {
        std::cout << "TYPE: " << getType(type) << " (edge probability = 0.3)" << std::endl;
        std::cout << "n Ebert Schmitz CR_TC" << std::endl;
        for (size_t size = 100; size < 2100; size+=100) {
            std::cout << size << " ";
            Graph g(size);
            g.generate(type, 0.3);
            Graph g_copy1 = g;
            Graph g_copy2 = g;
            SuccessorsList SCC(listType::CV);

            Timer timer;
            timer.start();
            Ebert alg_ebert(g);
            alg_ebert.getTransitiveClosure(g, SCC);
            double time_ebert = timer.stop();
            std::cout << time_ebert << " ";

            timer.start();
            Schmitz alg_schmitz(g);
            alg_schmitz.getTransitiveClosure(g, SCC);
            double time_schmitz = timer.stop();
            std::cout << time_schmitz << " ";

            timer.start();
            CR_TC alg_cr(g);
            alg_cr.getTransitiveClosure(g, SCC);
            double time_cr = timer.stop();
            std::cout << time_cr << std::endl;
        }
    }
}

int main() {
    run_tests();

    // Example
    // Uncomment section below to generate an example transitive closure of example graph

    /*
    Graph g(20);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(3, 1);
    g.addEdge(4, 3);
    g.generate(RANDOM, 0.12);
    g.visualize("results/graph.dot");
    system("dot -Tpng results/graph.dot -o results/graph.png"); // <-- need to install graphvi
    Graph g2 = g;
    Graph g3 = g;

    SuccessorsList gCC(CC);
    CR_TC alg_cr(g);
    alg_cr.getTransitiveClosure(g, gCC);
    gCC.printSCC();
    g.visualize("results/res.dot");
    system("dot -Tpng results/res.dot -o results/res.png"); 

    Intervals gVV2;
    Ebert alg_ebert(g2);
    alg_ebert.getTransitiveClosure(g2, gVV2);
    gVV2.printSCC();
    g2.visualize("results/res2.dot");
    system("dot -Tpng results/res2.dot -o results/res2.png");

    Intervals gVV3;
    Schmitz alg_schmitz(g);
    alg_schmitz.getTransitiveClosure(g3, gVV3);
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
        printf("Difference Ebert & Schmitz:\n");
        for (std::pair<size_t, size_t> i : res)
            printf("%d -> %d\n", i.first, i.second);
    }
    */

    return 0;
}