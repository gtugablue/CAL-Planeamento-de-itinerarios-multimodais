#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include <vector>

using namespace std;

class Vertex;

class Graph{
	static unsigned int lastID;
	const unsigned int id;
	vector<Vertex*> vertexSet;
public:
	Graph(): id(0){};
	vector<Vertex*> getVertexSet() const{return vertexSet;};
	void addVertex(Vertex* v){
		for(size_t i = 0; i < vertexSet.size(); i++){
			if(vertexSet[i] == v)
				return;
		}
		vertexSet.push_back(v);
	}
	unsigned int getNumEdges() const;
};

#endif
