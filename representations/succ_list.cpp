#include "./succ_list.h"

SuccessorsList::SuccessorsList(listType t) : type(t) { }

const size_t SuccessorsList::size() const {
    return list.size();
}

std::set<size_t> SuccessorsList::getSuccessors(size_t v) const {
    return list[v];
}

void SuccessorsList::clear() {
    for (auto i : list)
        i.clear();
    list.clear();
}

void SuccessorsList::printSCC() const {
    const char* name = ((type == listType::CV) ? "c*v" : (type == listType::VV ? "v*v" : "c*c"));
    std::cout << "SCC " << name << " list:" << std::endl;
    for (size_t i = 0; i < size(); i++) {
        if (type == listType::VV)
            std::cout << "\tRoot vertex ";
        else 
            std::cout << "\tCSS component ";
        std::cout <<  i << ": ";
        for (auto j : list[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

void SuccessorsList::update(std::set<size_t> component) {
    list.push_back(std::move(component));
}

