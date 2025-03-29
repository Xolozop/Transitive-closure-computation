#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <set> 
#include <iostream>
#include <fstream>

#include "types.h"

class DiGraph {
  public: 
    DiGraph(size_t vertices);
    DiGraph(adjMatrix_t aMatrix);
    void addEdge(size_t u, size_t v);

    void printAdjList(std::ostream& os=std::cout);
    void printAdjMatrix(std::ostream& os=std::cout);
    void printEdgeList(std::ostream& os=std::cout);

    size_t getVertices() { return vertices; }
    adjMatrix_t getAdjMatrix() { return adjMatrix; }

    void visualize(const std::string& filename="graph", bool show=false);
  private:
    size_t vertices;
    adjList_t adjList;
    adjMatrix_t adjMatrix;
    edgeList_t edgeList;
};

#endif