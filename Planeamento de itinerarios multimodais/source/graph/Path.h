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

	ostream& operator<<(ostream& os) const
	{
		int i;
		Vertex* v;
		cerr << edges.size() << endl;

		for(i = 0; i < edges.size(); i++)
		{
			cerr << i << endl;
			v = edges[i]->getSrc();
			TransportStop* ts = dynamic_cast<TransportStop*>(v);
			if(ts == NULL)
				cerr << "NOPE" << endl;
			else
				os << ((TransportStop*)edges[i]->getSrc())->getName() + '\n';
		}

		v = edges[edges.size() - 1]->getDst();
		TransportStop* ts = dynamic_cast<TransportStop*>(v);
		if(ts == NULL)
			cerr << "NOPE" << endl;
		else
			os << ((TransportStop*)edges[i]->getSrc())->getName() + '\n';

		return os;
	}

};



#endif
