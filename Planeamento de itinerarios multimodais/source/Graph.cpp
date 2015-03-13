#include "Graph.h"

unsigned int Graph::getNumEdges() const{
		unsigned int count = 0;
		for(size_t i = 0; i < vertexSet.size(); i++){
			count += vertexSet[i]->getAdj().size();
		}
		return count;
	}
