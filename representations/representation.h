#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include <vector>
#include <set>
#include <iostream>

// Абстрактный класс для представления КСС
class Representation {
public:
    Representation() = default;
    virtual const size_t size() const = 0; // Возвращает количество вершин
    virtual std::set<size_t> getSuccessors(size_t v) const = 0; // Получает множество вершин, достижимых из v
    virtual void update(std::set<size_t> component) = 0; // Добавляет новую компоненту связности
    virtual void printSCC() const = 0; // Выводит компоненты связности
    virtual void clear() = 0; // Очищает данные компонент
};

#endif