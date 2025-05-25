#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <vector>
#include <set>
#include <iostream>

class Representation {
public:
    Representation() = default;
    virtual const size_t size() const = 0;
    virtual std::set<size_t> getSuccessors(size_t v) const = 0;
    virtual void update(std::set<size_t> component) = 0;
    virtual void printSCC() const = 0;
    virtual void clear() = 0;
};

#endif