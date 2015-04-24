#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "../graph/Graph.h"
#include "../graph/Path.h"
#include <vector>

Path* brute_force(Graph* g, Vertex* ini, Vertex* f);

#endif
