#include "./intervals.h"

GraphVV::GraphVV(int n) : adj(n) {}

void GraphVV::addEdge(int u, int v) {
    adj[u].push_back(v);
}

int GraphVV::size() const {
    return adj.size();
}

const std::vector<int>& GraphVV::getSuccessors(int v) const {
    return adj[v];
}

void GraphVV::printList() {
    for (int i = 0; i < adj.size(); i++) {
        std::cout <<  i << ": ";
        for (int j = 0; j < adj[i].size(); j++) {
            std::cout << j;
            if (j != adj[i].size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

void GraphVV::visualize(const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph G {\n"; // Изменено на "digraph" для обозначения ориентированного графа
    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj[i].size(); j++)
            out << "    " << i << " -> " << adj[i][j] << ";\n"; // Изменено на "->" для ориентированного графа
    }
    out << "}\n";
    out.close();
}