#ifndef INTERVALS_H
#define INTERVALS_H

#include "./representation.h"

// Класс для представления КСС в виде интервалов
class Intervals : public Representation {
public:
    Intervals() = default;
    const size_t size() const; //Количество вершин
    std::set<size_t> getSuccessors(size_t v) const override; // Получение множество достижимых вершин из v
    virtual void printSCC() const override; // Выводит интервалы компонент
    void clear() override; // Очищает список интервалов
    void update(std::set<size_t> component) override; // Добавление новой компоненты
private:
    std::vector<std::vector<std::pair<size_t, size_t>>> intervals; // Хранение интервалов для каждой вершины
};

#endif