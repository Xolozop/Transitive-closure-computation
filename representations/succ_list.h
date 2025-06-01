#ifndef SUCCESSORS_LIST_H
#define SUCCESSORS_LIST_H

#include "./representation.h"

// Типы списков: c*c (компонента-компонента), c*v (компонента-вершина), v*v (вершина-вершина)
enum listType {CC, CV, VV};

// Класс для представления КСС в виде списков
class SuccessorsList : public Representation {
public:
    SuccessorsList(listType t); // Конструктор с указанием типа списка
    const size_t size() const; // Возвращает количество вершин или компонент
    std::set<size_t> getSuccessors(size_t v) const override; // Получение достижимых вершины из v
    virtual void printSCC() const override; // Вывод компоненты связности
    void clear() override; // Очищение списка
    void update(std::set<size_t> component) override; // Добавление новой компоненты

private:
    std::vector<std::set<size_t>> list; // Список множеств вершин/компонент
    listType type; // Тип списка (CC, CV, VV)
};

#endif