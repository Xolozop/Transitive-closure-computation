#ifndef EBERT_H
#define EBERT_H

#include <stack>
#include <algorithm>

#include "../graph.h"
#include "../representations/representation.h"
#include "../representations/succ_list.h"

void findSCCs_Ebert(Graph g, Representation& components);

#endif
