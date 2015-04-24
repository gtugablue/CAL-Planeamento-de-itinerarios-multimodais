#ifndef DIJSKTRA_H
#define DIJSKTRA_H

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Path.h"
#include <cfloat>
#include <vector>
#include <iostream>
#include <climits>
#include <boost/heap/fibonacci_heap.hpp>
#include "GraphQueue.h"
#include "GraphQueueFib.h"
#include "GraphQueueList.h"

typedef boost::heap::fibonacci_heap<Vertex*,  boost::heap::compare<Vertex::DijsComp> > dij_heap;
typedef boost::heap::fibonacci_heap<Vertex*, boost::heap::compare<Vertex::DijsComp> >::handle_type dij_handle;

Path* dijsktra_fib(Graph* g, Vertex* ini, Vertex* f);
Path* dijsktra_list(Graph* g, Vertex* ini, Vertex* f);
Path* dijsktra(Graph* g, Vertex* ini, Vertex* f, GraphQueue<Vertex::DijsComp>* queue);

#endif
