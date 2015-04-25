#ifndef PATH_H
#define PATH_H

#include "Edge.h"
#include "Vertex.h"
#include "../transport/TransportStop.h"
#include <vector>
#include <string>

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

	friend ostream& operator<<(ostream& os, Path& p){
		size_t i;
		Vertex* v;

		for(i = 0; i < p.edges.size(); i++)
		{
			v = p.edges[i]->getSrc();

			TransportStop* ts = dynamic_cast<TransportStop*>(v);
			if(ts != NULL)
				os << ((TransportStop*)p.edges[i]->getSrc())->getName() + '\n';
		}

		if(p.edges.size() > 1)
		{
			v = p.edges[p.edges.size() - 1]->getDst();
			TransportStop* ts = dynamic_cast<TransportStop*>(v);
			if(ts != NULL)
				os << ((TransportStop*)p.edges[i]->getSrc())->getName() + '\n';
		}

		return os;
	}
};



#endif
