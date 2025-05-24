#ifndef SUCCESSORS_LIST_H
#define SUCCESSORS_LIST_H

#include "../graph.h"
#include "./representation.h"

enum listType {CC, CV, VV};

class SuccessorsList : public Representation {
public:
    SuccessorsList(listType t);
    const size_t size() const;
    void addVertex(size_t u, size_t v) override;
    const std::vector<size_t>& getSuccessors(size_t v) const override;
    virtual void printSCC() const override;
    void update(std::vector<size_t> component) override;
private:
    std::vector<std::vector<size_t>> list;
    listType type;
};

#endif