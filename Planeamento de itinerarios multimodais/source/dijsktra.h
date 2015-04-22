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


typedef boost::heap::fibonacci_heap<Vertex*,  boost::heap::compare<Vertex::DijsComp> > dij_heap;
typedef boost::heap::fibonacci_heap<Vertex*, boost::heap::compare<Vertex::DijsComp> >::handle_type dij_handle;

Path* dijsktra(Graph* g, Vertex* ini, Vertex* f);

#endif
