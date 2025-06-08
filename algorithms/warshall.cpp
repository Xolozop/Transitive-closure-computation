#include "./warshall.h"

Warshall::Warshall(Graph g) {
    n = g.size();
    R_plus = g.getAdjMatrix();
}

void Warshall::getTransitiveClosure(Graph& g, Representation& repr) {
    for (size_t k = 0; k < n; k++) {
        for (size_t i = 0; i < n; i++) {
            if ((i != k) && R_plus[k][i]) {
                for (size_t j = 0; j < n; j++)
                    R_plus[i][j] = R_plus[i][j] || R_plus[k][j];
            }
        }
    }

    g.saveTransitiveClosure(R_plus);
}