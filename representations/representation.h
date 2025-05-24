#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <vector>

class Representation {
public:
    Representation() = default;
    virtual const size_t size() const = 0;
    virtual void addVertex(size_t u, size_t v) = 0;
    virtual const std::vector<size_t>& getSuccessors(size_t v) const = 0;
    virtual void update(std::vector<size_t> component) = 0;
    virtual void printSCC() const = 0;
};

#endif