#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>

#include "graph.h"
#include "algorithms/ebert_algorithm.h"
#include "representations/representation.h"
#include "representations/succ_list.h"

int main() {
    // Example
    Graph g(10);
    g.addEdge(1, 4);
    g.addEdge(7, 1);
    g.addEdge(4, 7);
    g.addEdge(9, 7);
    g.addEdge(6, 9);
    g.addEdge(3, 6);
    g.addEdge(9, 3);
    g.addEdge(8, 6);
    g.addEdge(2, 8);
    g.addEdge(5, 2);
    g.addEdge(8, 5);

    g.printAdjList();
    g.visualize("graph.dot");
    system("dot -Tpng graph.dot -o graph.png"); // <-- need to install graphvi

    SuccessorsList gCV(listType::CV); 
    findSCCs_Ebert(g, gCV);
    gCV.printSCC();

    return 0;
}