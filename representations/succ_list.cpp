#include "./succ_list.h"

SuccessorsList::SuccessorsList(listType t) : type(t) { }

void SuccessorsList::addVertex(size_t u, size_t v) {
    list[u].push_back(v);
}

const size_t SuccessorsList::size() const {
    return list.size();
}

const std::vector<size_t>& SuccessorsList::getSuccessors(size_t v) const {
    return list[v];
}

void SuccessorsList::printSCC() const {
    std::cout << "SCC list:" << std::endl;
    for (size_t i = 0; i < list.size(); i++) {
        std::cout <<  i << ": ";
        for (size_t j = 0; j < list[i].size(); j++) {
            std::cout << list[i][j];
            if (j != list[i].size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

void SuccessorsList::update(std::vector<size_t> component) {
    list.push_back(std::move(component));
}

