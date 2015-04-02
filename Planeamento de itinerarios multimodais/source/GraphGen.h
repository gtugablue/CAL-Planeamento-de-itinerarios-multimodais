#ifndef GRAPHGEN_H
#define GRAPHGEN_H

#include "Graph.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;


class GraphGen{
public:
	static Graph* randGraph(unsigned int numVertices, unsigned int numEdges, unsigned int minx, unsigned int maxx ,unsigned int miny,unsigned int maxy){
		Graph* out = new Graph();
		while(out->getVertexSet().size() < numVertices){
			Vertex* v = new Vertex(Coordinates(rand() % (maxx-minx) + minx, rand() % (maxy-miny) + miny));
			out->addVertex(v);
		}
		while(out->getNumEdges() < numEdges*2){
			unsigned int index_src = rand()% out->getVertexSet().size();
			unsigned int index_dst;
			do{
				index_dst = rand()% out->getVertexSet().size();
			}while(index_src == index_dst);
			out->getVertexSet()[index_src]->addAdj(out->getVertexSet()[index_dst]);
			out->getVertexSet()[index_dst]->addAdj(out->getVertexSet()[index_src]);
		}
		return out;
	}
};

#endif
