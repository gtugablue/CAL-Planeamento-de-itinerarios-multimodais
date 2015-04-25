#ifndef ASTAR_H
#define ASTAR_H

#include "../graph/Vertex.h"
#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../graph/Path.h"
#include "GraphQueue.h"
#include "GraphQueueFib.h"
#include "GraphQueueList.h"
#include <cfloat>
#include <vector>
#include <iostream>
#include <climits>
#include <list>
#include <boost/heap/fibonacci_heap.hpp>


Path* astar(Graph* g, Vertex* ini, Vertex* f);
Path* astar_fib(Graph* g, Vertex* ini, Vertex* f);
Path* astar_list(Graph* g, Vertex* ini, Vertex* f);

#endif
