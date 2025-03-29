#include "digraph.h"
#include "algorithms.h"

int main() {
    DiGraph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(1, 6);

    g.printAdjList();
    g.printAdjMatrix();
    g.printEdgeList();

    g.visualize("graph");

    DiGraph h1 = Warshall(g);
    h1.visualize("graph2");
    DiGraph h2 = Warshall(g);
    h2.visualize("graph3", true);
    return 0;
}

