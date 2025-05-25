#ifndef INTERVALS_H
#define INTERVALS_H

#include "./representation.h"

class Intervals : public Representation {
public:
    Intervals() = default;
    const size_t size() const;
    std::set<size_t> getSuccessors(size_t v) const override;
    virtual void printSCC() const override;
    void clear() override;
    void update(std::set<size_t> component) override;
private:
    std::vector<std::vector<std::pair<size_t, size_t>>> intervals;
};

#endif