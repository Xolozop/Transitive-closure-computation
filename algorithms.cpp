#include "algorithms.h"

DiGraph Warshall(DiGraph G) {
    std::vector<std::vector<size_t>> A = G.getAdjMatrix();
    size_t n = G.getVertices();
    for (size_t k = 0; k < n; k++) {
        for (size_t i = 0; i < n; i++) {
            if (i != k && A[i][k]) {
                for (size_t j = 0; j < n; j++) 
                    A[i][j] = A[i][j] || A[k][j];
            }
        }
    }

    return DiGraph(A);
}

DiGraph Warren(DiGraph G) {
    std::vector<std::vector<size_t>> A = G.getAdjMatrix();
    size_t n = G.getVertices();
    for (size_t i = 3; i < n; i++) {
        for (size_t k = 2; k < i-1; k++) {
            if (A[i][k]) {
                for (size_t j = 0; j < n; j++) 
                    A[i][j] = A[i][j] || A[k][j];
            }
        }
    }

    for (size_t i = 2; i < n-1; i++) {
        for (size_t k = i+1; k < n; k++) {
            if (A[i][k]) {
                for (size_t j = 2; j < n; j++) 
                    A[i][j] = A[i][j] || A[k][j];
            }
        }
    }

    return DiGraph(A);
}