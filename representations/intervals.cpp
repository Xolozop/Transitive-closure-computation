#include "./intervals.h"

// Возвращает количество вершин в списке интервалов
const size_t Intervals::size() const {
    return intervals.size();
}

// Получает множество вершин, достижимых из вершины v
std::set<size_t> Intervals::getSuccessors(size_t v) const {
    std::set<size_t> list;
    for (auto j : intervals[v]) {
        if (j.first == j.second) {
            list.emplace(j.first); // Добавляем одиночную вершину
        } else {
            // Добавляем все вершины в интервале [j.first, j.second]
            for (size_t s = j.first; s <= j.second; s++)
                list.emplace(s);
        }
    }
    return list;
}

// Очищает список интервалов
void Intervals::clear() {
    for (auto& i : intervals)
        i.clear(); 
    intervals.clear(); 
}

// Вывод интервалов сильно связанных компонент
void Intervals::printSCC() const {
    std::cout << "Список интервалов SCC:" << std::endl;
    for (size_t i = 0; i < size(); i++) {
        std::cout << i << ": ";
        for (auto j : intervals[i]) {
            std::cout << "[" << j.first << "," << j.second << "] "; 
        }
        std::cout << std::endl;
    }
}

// Добавляет новую компоненту в список интервалов
void Intervals::update(std::set<size_t> component) {
    if (component.empty())
        return; // Пропускаем пустую компоненту

    // Создаём список интервалов для компоненты
    std::vector<std::pair<size_t, size_t>> interval_component(1);
    size_t ptr = 0;
    interval_component[ptr].first = *component.begin(); // Начало первого интервала
    interval_component[ptr].second = *component.begin(); // Конец первого интервала
    if (component.size() == 1) {
        intervals.push_back(interval_component); // Сохраняем одиночный интервал
        return;
    }

    // Формируем интервалы для остальных вершин
    for (auto i : component) {
        if (i == *component.begin())
            continue; // Пропускаем первую вершину

        if (interval_component[ptr].second + 1 == i) {
            interval_component[ptr].second = i; // Расширяем текущий интервал
        } else {
            ptr++;
            interval_component.push_back(std::pair<size_t, size_t>{i, i}); // Начинаем новый интервал
        }
    }

    intervals.push_back(interval_component); // Добавляем компоненту в список
}