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


Path* dijsktra(Graph* g, Vertex* ini, Vertex* f);

#endif
