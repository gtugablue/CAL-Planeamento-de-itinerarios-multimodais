#ifndef VERTEX_H
#define VERTEX_H

#include "SDLGraphDraw.h"
#include <vector>
#include <list>
#include "Edge.h"
#include "Coordinates.h"

class Vertex{
private:
	std::vector<Edge*> adj;
protected:
	Coordinates coords;
public:
	Vertex(const Coordinates &coords): coords(coords) { }
	std::vector<Edge*> getAdj()const{return adj;};
	void addAdj(Vertex* v, double weight =0);
	Coordinates getCoords() const { return coords; }
	double getRenderX() const { return coords.getLongitude(); }
	double getRenderY() const { return coords.getLatitude(); }
};


#endif

