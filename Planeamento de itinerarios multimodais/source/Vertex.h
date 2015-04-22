#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"
#include "Coordinates.h"
#include <iostream>

class Vertex{
private:
	//static unsigned int lastID;
	unsigned int index;
	unsigned int x;
	unsigned int y;
	std::vector<Edge*> adj;
	double bestWeight;
	Vertex* parent;
	int visits;
	int processed;

protected:
	Coordinates coords;
public:
	Vertex(const Coordinates &coords): coords(coords), x(coords.getLatitude()), y(coords.getLongitude()) { }
	std::vector<Edge*> getAdj()const{return adj;};
	void addAdj(Vertex* v, double weight =0);
	void addEdge(Edge *edge);
	Coordinates getCoords() const { return coords; }
	double getRenderX() const { return coords.getLongitude(); }
	double getRenderY() const { return coords.getLatitude(); }
	unsigned int getIndex() const {
		return index;
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
	void setIndex(unsigned int index){
		this->index = index;
	}

	double getBestWeight() const {
		return bestWeight;
	}

	void setBestWeight(double bestWeight) {
		this->bestWeight = bestWeight;
	}

	const Vertex* getParent() const {
		return parent;
	}

	void setParent( Vertex* parent) {
		this->parent = parent;
	}

	void resetProcessed(){
		processed = 0;
	}

	int getProcessed() const {
		return processed;
	}

	void incProcessed(){
		processed++;
	}

	int getVisits() const {
		return visits;
	}

	void resetVisits(){
		visits = 0;
	}

	void incVisits(){
		visits++;
	}

};


#endif

