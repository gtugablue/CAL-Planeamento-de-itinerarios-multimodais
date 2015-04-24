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
	void removeEdgeEnd(){
		edges.pop_back();
	}

	double getCost() const {
		return cost;
	}

	void setCost(double cost) {
		this->cost = cost;
	}
	Path& operator=(const Path& p){
		edges = p.edges;
		cost = p.cost;
		return *this;
	}
};



#endif
