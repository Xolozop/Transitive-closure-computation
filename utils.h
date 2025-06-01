#pragma once
#include <vector>
#include <string>
#include <chrono>

#include "./graph.h"

class Timer {
    std::chrono::high_resolution_clock::time_point start_time;
public:
    void start();
    double stop();
};

std::vector<std::pair<int, int>> generateGraph(int n, int m, GraphType type);
std::string graphTypeToString(GraphType type);
