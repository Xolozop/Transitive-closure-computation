#include <random>
#include <algorithm>

#include "utils.h"

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

double Timer::stop() {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start_time).count();
}

std::vector<std::pair<int, int>> generateGraph(int n, int m, GraphType type) {
    // n - кол-во вершин, m - кол-во рёбер
    std::vector<std::pair<int, int>> edges;
    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(0, n - 1);

    switch (type) {
        case RANDOM:
            for (int i = 0; i < n+n/2; ++i)
                edges.emplace_back(dist(gen), dist(gen));
            break;
        case STRONGLY_CONNECTED:
            for (int i = 0; i < n; ++i)
                edges.emplace_back(i, (i + 1) % n);
            for (int i = 0; i < m - n; ++i)
                edges.emplace_back(dist(gen), dist(gen));
            break;
        case DISCONNECTED_COMPONENTS:
            for (int k = 0; k < n; k += 100)
                for (int i = 0; i < 99 && k + i + 1 < n; ++i)
                    edges.emplace_back(k + i, k + i + 1);
            break;
        case MANY_CYCLES:
            for (int k = 0; k < n; k += 10) {
                for (int i = 0; i < 9 && k + i + 1 < n; ++i)
                    edges.emplace_back(k + i, k + i + 1);
                if (k + 9 < n)
                    edges.emplace_back(k + 9, k);
            }
            break;
    }
    return edges;
}

std::string graphTypeToString(GraphType type) {
    switch (type) {
        case RANDOM: return "random";
        case STRONGLY_CONNECTED: return "strongly_connected";
        case DISCONNECTED_COMPONENTS: return "disconnected_components";
        case MANY_CYCLES: return "many_cycles";
    }
    return "unknown";
}


/*
Graph
    - generate
    - succ list + type
    - intervals
    - chains

*/