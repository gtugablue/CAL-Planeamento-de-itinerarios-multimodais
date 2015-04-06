#include "Vertex.h"


void Vertex::addAdj(Vertex* v, double weight){
		for(size_t i = 0; i < adj.size(); i++){
			if(adj[i]->getDst() == v)
				return;
		}
		Edge * e = new Edge(this, v, weight);
		adj.push_back(e);
	}

void Vertex::addEdge(Edge *edge)
{
	adj.push_back(edge);
}
