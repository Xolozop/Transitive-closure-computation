#ifndef SCHMITZ_H
#define SCHMITZ_H

#include <climits>
#include <queue>
#include <stack>

#include "../graph.h"
#include "../representations/representation.h"
#include "../representations/succ_list.h"

Graph findSCCs_Schmitz(Graph g, Representation& components);

#endif
