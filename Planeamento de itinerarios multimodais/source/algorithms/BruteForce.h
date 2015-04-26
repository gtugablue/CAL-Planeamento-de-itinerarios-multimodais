#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "../graph/Graph.h"
#include "../graph/Path.h"
#include <vector>

/**
 * @brief perform a brute force search for the lowest cost path between two vertices in graph
 * @param g graph on which to perform search
 * @param ini starting point of search
 * @param f goal of search
 * @return  lowest cost path from initial vertex to goal, if there is none, the path will have no edges
 */
Path* brute_force(Graph* g, Vertex* ini, Vertex* f);

#endif
