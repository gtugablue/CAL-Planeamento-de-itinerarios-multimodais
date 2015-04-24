#ifndef PATH_H
#define PATH_H

#include "Edge.h"
#include "Vertex.h"
#include <vector>

using namespace std;

class Edge;
class Vertex;

class Path{
	vector<Edge*> edges;
	double cost;
public:
	Path(double cost) {
		this->cost = cost;
	}
	vector<Edge*> getEdges() const{
		return edges;
	}
	void addEdgeEnd(Edge* e){
		edges.push_back(e);
	}
	void addEdgeBeginning(Edge* e){
		edges.insert(edges.begin(), e);
	}

	bool operator==(const Path p2) const{
		if(edges.size() != p2.edges.size())
			return false;

		for(int i = 0; i < edges.size(); i++)
		{
			if(edges[i] != p2.edges[i])
				return false;
		}

		return true;
	}
};



#endif
