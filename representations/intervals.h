#pragma once
#include <vector>
#include <iostream>
#include <fstream>

#include "./representation.h"

template <typename T>
class Intervals : public Representation {
public:
    Intervals(); // <- сюда бы ещё передавать бин дерево или массив
    void addVertex(size_t u, size_t v) const override;
    const std::vector<size_t>& getSuccessors(size_t v) const override;
    virtual void printSuccessors() const override;
private:
    T intervals;
};
