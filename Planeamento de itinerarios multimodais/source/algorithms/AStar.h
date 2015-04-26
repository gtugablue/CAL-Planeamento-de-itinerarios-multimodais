#ifndef ASTAR_H
#define ASTAR_H

#include "../graph/Vertex.h"
#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../graph/Path.h"
#include "GraphQueue.h"
#include "GraphQueueFib.h"
#include "GraphQueueList.h"z
#include <cfloat>
#include <vector>
#include <iostream>
#include <climits>
#include <list>
#include <boost/heap/fibonacci_heap.hpp>

/**
 * @brief perform a* algorithm in graph from one vertex to another using the specified data structure
 * @param g graph on which to perform search
 * @param ini initial vertex
 * @param f goal vertex
 * @param queue data structure to use in algorithm
 * @return path from initial vertex to goal of lowest cost, if there is none, the path will have no edges
 */

Path* astar(Graph* g, Vertex* ini, Vertex* f, GraphQueue<Vertex::AStarComp>* queue);

/**
 * @brief perform a* algorithm in graph from one vertex to another using the fibonacci heap data structure
 * @param g graph on which to perform search
 * @param ini initial vertex
 * @param f goal vertex
 * @return path from initial vertex to goal of lowest cost, if there is none, the path will have no edges
 */
Path* astar_fib(Graph* g, Vertex* ini, Vertex* f);

/**
 * @brief perform a* algorithm in graph from one vertex to another using a list
 * @param g graph on which to perform search
 * @param ini initial vertex
 * @param f goal vertex
 * @param queue data structure to use in algorithm
 * @return path from initial vertex to goal of lowest cost, if there is none, the path will have no edges
 */
Path* astar_list(Graph* g, Vertex* ini, Vertex* f);

#endif
