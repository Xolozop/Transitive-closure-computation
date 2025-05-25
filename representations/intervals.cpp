#include "./intervals.h"

const size_t Intervals::size() const {
    return intervals.size();
}

std::set<size_t> Intervals::getSuccessors(size_t v) const {
    std::set<size_t> list;
    for (auto j : intervals[v]) {
        if (j.first == j.second) {
            list.emplace(j.first);
        } else {
            for (size_t s = j.first; s <= j.second; s++)
            list.emplace(s);
        }
    }
    return list;
}

void Intervals::clear() {
    for (auto i : intervals)
        i.clear();
    intervals.clear();
}

void Intervals::printSCC() const {
    std::cout << "SCC interval list:" << std::endl;
    for (size_t i = 0; i < size(); i++) {
        std::cout <<  i << ": ";
        for (auto j : intervals[i]) {
            std::cout << "[" << j.first << "," << j.second << "] ";
        }
        std::cout << std::endl;
    }
}

void Intervals::update(std::set<size_t> component) {
    if (component.empty())
        return;

    std::vector<std::pair<size_t, size_t>> interval_component(1);
    size_t ptr = 0;
    interval_component[ptr].first = *component.begin();
    interval_component[ptr].second = *component.begin();
    if (component.size() == 1) {
        intervals.push_back(interval_component);
        return;
    }

    for (auto i : component) {
        if (i == *component.begin())
            continue;

        if (interval_component[ptr].second+1 == i) {
            interval_component[ptr].second = i;
        } else {
            ptr++;
            interval_component.push_back(std::pair<size_t, size_t>{i, i});
        }
    }

    intervals.push_back(interval_component);
}

