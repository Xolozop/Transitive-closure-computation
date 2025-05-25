#ifndef SUCCESSORS_LIST_H
#define SUCCESSORS_LIST_H

#include "./representation.h"

enum listType {CC, CV, VV};

class SuccessorsList : public Representation {
public:
    SuccessorsList(listType t);
    const size_t size() const;
    std::set<size_t> getSuccessors(size_t v) const override;
    virtual void printSCC() const override;
    void clear() override;
    void update(std::set<size_t> component) override;
private:
    std::vector<std::set<size_t>> list;
    listType type;
};

#endif