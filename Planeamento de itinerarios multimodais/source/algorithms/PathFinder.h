#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "../ProgramConfig.h"
#include "../graph/Graph.h"
#include "../graph/Path.h"
#include "../graph/Vertex.h"
#include "AStar.h"
#include "Dijsktra.h"
#include "BruteForce.h"

/**
 * @brief Interface to read user configurations and select algorithms and data structures to use
 */
class PathFinder{

public:
	/**
	 * @brief search for lowest cost path in graph from one vertex to another using the specified data structure and specified algorithm
	 * @param g graph on which to perform search
	 * @param ini initial vertex
	 * @param f goal vertex
	 * @param conf configuration of program specifying chosen options
	 * @return path from initial vertex to goal of lowest cost, if there is none, the path will have no edges
	 */
	static Path* find_path(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf);

private:
	static Path* find_path_normal(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf);
	static Path* find_path_advanced(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf);
	static Path* find_path_all(Graph *g, Vertex* ini, Vertex* f, ProgramConfig conf);
};


#endif
