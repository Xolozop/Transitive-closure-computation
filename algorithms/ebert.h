#ifndef EBERT_H
#define EBERT_H

#include "./algorithm.h"

class Ebert : public Algorithm {
public:
    Ebert(Graph g);
    void getTransitiveClosure(Graph& g, Representation& components) override;

private:
    void DFS(size_t v, Representation& components);
    // Обновление достижимости для ребра v -> w
    void processEdge(size_t v, size_t w);
    // Обновление достижимости для дуги дерева v -> w
    void processTreeArc(size_t v, size_t w);
    // Обработка перекрестного ребра между компонентами
    void processIntercomponentCrossLink(size_t v, size_t w);
    // Обновление достижимости для вершины x в компоненте v
    void processVertexOfComponent(size_t x, size_t v);
};

#endif