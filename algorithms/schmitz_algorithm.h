#ifndef SCHMITZ_H
#define SCHMITZ_H

#include <climits>
#include <stack>

#include "../graph.h"
#include "../representations/representation.h"
#include "../representations/succ_list.h"

void findSCCs_Schmitz(Graph g, Representation& components);

#endif
