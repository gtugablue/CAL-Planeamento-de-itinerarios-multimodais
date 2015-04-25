#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include <vector>

using namespace std;

class Vertex;

class Graph{
	vector<Vertex*> vertexSet;
public:
	Graph(){};
	vector<Vertex*> getVertexSet() const;
	void addVertex(Vertex* v);
	unsigned int getNumEdges() const;
	void removeLast();
};

#endif
