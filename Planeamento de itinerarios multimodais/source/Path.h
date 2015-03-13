#ifndef PATH_H
#define PATH_H

#include "Edge.h"
#include "Vertex.h"
#include <vector>

using namespace std;

class Edge;
class Vertex;

class Path{
	static unsigned int lastID;
	const unsigned int id;
	vector<Edge*> edges;
	vector<Vertex*> vertices;
	double cost;
public:
	Path(double cost): id(0){
		this->cost = cost;
	}
	vector<Edge*> getEdges() const{
		return edges;
	}
	void addEdge(Edge* e){
		edges.push_back(e);
	}
	vector<Vertex*> getVertices() const
	{
	    return vertices;
	}
	void addVertex(Vertex* v)
	{
	    vertices.push_back(v);
	}
};



#endif
