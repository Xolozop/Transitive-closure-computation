#include "digraph.h"

DiGraph::DiGraph(size_t verts) : vertices(verts) {
    adjList.resize(vertices);
    adjMatrix.resize(vertices, std::vector<size_t>(vertices));
}

DiGraph::DiGraph(adjMatrix_t aMatrix) : adjMatrix(aMatrix) {
    vertices = adjMatrix.size();
    adjList.resize(vertices);
    for (size_t row = 0; row < vertices; row++) {
        for (size_t col = 0; col < vertices; col++) {
            if (adjMatrix[row][col] == 1) {
                adjList[row].insert(col);
                edgeList.insert({row, col});
            }
        }
    }
}
    

void DiGraph::addEdge(size_t u, size_t v) {
    size_t max_int = std::max(u, v)+1;
    if (max_int > vertices) {
        adjList.resize(max_int);
        adjMatrix.resize(max_int);
        for (auto& row : adjMatrix)
            row.resize(max_int);
        vertices = max_int;
    }
    adjList[u].insert(v);
    adjMatrix[u][v] = 1;
    edgeList.insert({u, v});
}

void DiGraph::printAdjList(std::ostream& os) {
    os << "Adjacency list:\n";
    for (int i = 0; i < vertices; ++i) {
        os << '\t' << i << ": ";
        for (int v : adjList[i])
            os << v << ' ';
        os << '\n';
    }
}
    
void DiGraph::printAdjMatrix(std::ostream& os) {
    os << "Adjacency matrix:\n";
    for (const auto& row : adjMatrix) {
        os << '\t';
        for (const auto& val : row)
            os << val << " ";
        os << std::endl;
    }
}
    
void DiGraph::printEdgeList(std::ostream& os) {
    os << "Edge list:\n\t";
    size_t i = 0;
    for (const auto& edge : edgeList) {
        os << "(" << edge.first << ", " << edge.second << ")";
        if (++i != edgeList.size())
            os << "; ";
    }
    os << std::endl;
}
    
void DiGraph::visualize(const std::string& filename, bool show) {
    std::system("mkdir -p results");
    std::string dotFile = "results/" + filename + ".dot";
    std::ofstream out(dotFile);
    out << "digraph G {\n";
    for (const auto& edge : edgeList)
        out << "\t" << edge.first << " -> " << edge.second << ";\n"; 
    out << "}";
    out.close();

    std::string pngFile = "results/" + filename + ".png";
    char buffer[22 + dotFile.size() + pngFile.size()];
    sprintf(buffer, "dot -Tpng %s -o %s", dotFile.data(), pngFile.data());
    std::system(buffer);
    if (show) {
        char buffer[4 + pngFile.size()];
        sprintf(buffer, "feh %s", pngFile.data());
        std::system(buffer);
    }
}