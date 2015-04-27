#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include <vector>

using namespace std;

class Vertex;

/**
 * @brief Generic Graph interface
 */
class Graph{
	vector<Vertex*> vertexSet;
public:
	/**
	 * @brief graph constructor
	 */
	Graph(){};

	/**
	 * @brief get the list of vertices in the graph
	 * @return list of vertices
	 */
	vector<Vertex*> getVertexSet() const;

	/**
	 * @brief add vertex to graph, setting its index appropriately
	 * @param v vertex to add
	 */
	void addVertex(Vertex* v);

	/**
	 * @brief count the total number of edges in graph
	 * @return number of edges in graph
	 */
	unsigned int getNumEdges() const;

	/**
	 * @brief remove the last vertex from the graph
	 */
	void removeLast();
};

#endif
