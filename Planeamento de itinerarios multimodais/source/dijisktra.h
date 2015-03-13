#ifndef DJISKTRA_H
#define DJISKTRA_H

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Path.h"
#include <cfloat>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;
Path* dijisktra(Graph* g, Vertex* ini, Vertex* f);

#endif
