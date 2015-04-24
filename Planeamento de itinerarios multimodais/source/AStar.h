#ifndef ASTAR_H
#define ASTAR_H

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Path.h"
#include "GraphQueue.h"
#include "GraphQueueFib.h"
#include "GraphQueueList.h"
#include <cfloat>
#include <vector>
#include <iostream>
#include <climits>
#include <list>
#include <boost/heap/fibonacci_heap.hpp>


typedef boost::heap::fibonacci_heap<Vertex*,  boost::heap::compare<Vertex::AStarComp> > astar_heap;
typedef boost::heap::fibonacci_heap<Vertex*, boost::heap::compare<Vertex::AStarComp> >::handle_type astar_handle;

Path* astar(Graph* g, Vertex* ini, Vertex* f);
Path* astar_fib(Graph* g, Vertex* ini, Vertex* f);
Path* astar_list(Graph* g, Vertex* ini, Vertex* f);

#endif
