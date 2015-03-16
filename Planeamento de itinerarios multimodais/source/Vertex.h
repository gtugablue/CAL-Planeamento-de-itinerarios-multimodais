#ifndef VERTEX_H
#define VERTEX_H

#include "SDLGraphDraw.h"
#include <vector>
#include <list>

using namespace std;

class Edge;

class Vertex{
	static unsigned int lastID;
	unsigned int index;
	unsigned int x;
	unsigned int y;
	vector<Edge*> adj;
public:
	Vertex() { } // TODO: Delete
	Vertex(unsigned int index, unsigned int x,	unsigned int y){
		this->x = x;
		this->y = y;
		this->index = index;
	}

	vector<Edge*> getAdj()const{return adj;};
	void addAdj(Vertex* v, double weight =0);

	unsigned int getIndex() const {
		return index;
	}

	virtual unsigned int getRenderX() {
		return x;
	}

	;

	virtual unsigned int getRenderY() {
		return y;
	}

	;
};


#endif

