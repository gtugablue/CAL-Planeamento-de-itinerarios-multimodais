#ifndef VERTEX_H
#define VERTEX_H

#include "SDLGraphDraw.h"
#include <vector>
#include <list>
#include "Edge.h"

using namespace std;

class Vertex{
	unsigned int x;
	unsigned int y;
	vector<Edge*> adj;
public:
	Vertex(unsigned int x,	unsigned int y){
		this->x = x;
		this->y = y;
	}

	vector<Edge*> getAdj()const{return adj;};
	void addAdj(Vertex* v, double weight =0);

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

