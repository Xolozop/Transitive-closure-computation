#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>

#include "graph.h"
#include "algorithms/ebert_algorithm.h"
#include "algorithms/schmitz_algorithm.h"
#include "representations/representation.h"
#include "representations/intervals.h"
#include "representations/succ_list.h"

int main() {
    // Example
    Graph g(10);
    g.generate(20, RANDOM);
    /*
    0: 
    1: 0 1 3 5 6 7 8 
    2: 7 
    3: 2 8 
    4: 
    5: 2 
    6: 0 7 
    7: 0 2 5 8 9 
    8: 0 1 
    9: 3 6 
    */
    // g.addEdge(1, 4);
    // g.addEdge(7, 1);
    // g.addEdge(4, 7);
    // g.addEdge(9, 7);
    // g.addEdge(6, 9);
    // g.addEdge(3, 6);
    // g.addEdge(9, 3);
    // g.addEdge(8, 6);
    // g.addEdge(2, 8);
    // g.addEdge(5, 2);
    // g.addEdge(8, 5);

    g.printAdjList();
    g.visualize("graph.dot");
    system("dot -Tpng graph.dot -o graph.png"); // <-- need to install graphvi

    Intervals gVV; 
    findSCCs_Schmitz(g, gVV);
    gVV.printSCC();

    SuccessorsList gVV2(listType::VV); 
    Graph res = findSCCs_Ebert(g, gVV2);
    res.visualize("res.dot");
    system("dot -Tpng graph.dot -o graph.png"); // <-- need to install graphvi
    gVV2.printSCC();

    return 0;
}