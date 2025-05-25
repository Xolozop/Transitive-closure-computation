#include "./succ_list.h"

// Конструктор с типом списка (c*v, v*v или c*c)
SuccessorsList::SuccessorsList(listType t) : type(t) { }

// Возвращение количества вершин/компонент в списке
const size_t SuccessorsList::size() const {
    return list.size();
}

// Получение множества вершин, достижимых из v
std::set<size_t> SuccessorsList::getSuccessors(size_t v) const {
    return list[v];
}

// Очищение списка
void SuccessorsList::clear() {
    for (auto& i : list)
        i.clear(); // Очищение множества
    list.clear(); // Очищение списка
}

// Вывод сильно связанных компонент
void SuccessorsList::printSCC() const {
    const char* name = ((type == listType::CV) ? "c*v" : (type == listType::VV ? "v*v" : "c*c"));
    std::cout << "Список SCC " << name << ":" << std::endl;
    for (size_t i = 0; i < size(); i++) {
        if (type == listType::VV)
            std::cout << "\tКорневая вершина ";
        else 
            std::cout << "\tКомпонента SCC ";
        std::cout << i << ": ";
        for (auto j : list[i]) {
            std::cout << j << " "; 
        }
        std::cout << std::endl;
    }
}

// Добавление новой компоненты в список
void SuccessorsList::update(std::set<size_t> component) {
    list.push_back(std::move(component));
}