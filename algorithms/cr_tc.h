#ifndef CRTC_ALGORITHM_H
#define CRTC_ALGORITHM_H

#include "../graph.h"
#include "../representations/representation.h"

Graph findSCCs_CRTC(const Graph& g, Representation& components);

#endif