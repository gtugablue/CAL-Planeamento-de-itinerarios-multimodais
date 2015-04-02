#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"
#include "Coordinates.h"
#include <iostream>

class Vertex{
private:
	static unsigned int lastID;
	const unsigned int id;
	unsigned int x;
	unsigned int y;
	std::vector<Edge*> adj;
protected:
	Coordinates coords;
public:
	Vertex(const Coordinates &coords): coords(coords), id(lastID++) { }
	std::vector<Edge*> getAdj()const{return adj;};
	void addAdj(Vertex* v, double weight =0);
	Coordinates getCoords() const { return coords; }
	double getRenderX() const { return coords.getLongitude(); }
	double getRenderY() const { return coords.getLatitude(); }
	unsigned int getIndex() const {
		return id;
	}
	virtual unsigned int getRenderX() {
		return x;
	};
	virtual unsigned int getRenderY() {
		return y;
	};
	virtual ~Vertex()
	{

	}
};


#endif

