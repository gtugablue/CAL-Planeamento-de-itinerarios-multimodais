#ifndef DIJSKTRA_H
#define DIJSKTRA_H

#include "../graph/Vertex.h"
#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../graph/Path.h"
#include <cfloat>
#include <vector>
#include <iostream>
#include <climits>
#include <boost/heap/fibonacci_heap.hpp>
#include "GraphQueue.h"
#include "GraphQueueFib.h"
#include "GraphQueueList.h"


Path* dijsktra_fib(Graph* g, Vertex* ini, Vertex* f);
Path* dijsktra_list(Graph* g, Vertex* ini, Vertex* f);
Path* dijsktra(Graph* g, Vertex* ini, Vertex* f, GraphQueue<Vertex::DijsComp>* queue);

#endif
