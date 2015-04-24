#include "Graph.h"


vector<Vertex*> Graph::getVertexSet() const{
	return vertexSet;
};
unsigned int Graph::getNumEdges() const{
		unsigned int count = 0;
		for(size_t i = 0; i < vertexSet.size(); i++){
			count += vertexSet[i]->getAdj().size();
		}
		return count;
	}
void Graph::addVertex(Vertex* v){
	for(size_t i = 0; i < vertexSet.size(); i++){
		if(vertexSet[i] == v)
			return;
	}
	v->setIndex(vertexSet.size());
	vertexSet.push_back(v);
}
