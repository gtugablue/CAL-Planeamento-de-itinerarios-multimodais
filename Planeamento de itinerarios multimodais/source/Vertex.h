#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"
#include "Coordinates.h"
#include <iostream>
#include <cfloat>

class Vertex{
private:
	//static unsigned int lastID;
	unsigned int index;
	unsigned int x;
	unsigned int y;
	std::vector<Edge*> adj;
	double bestWeight;
	Edge* parent;
	int visits;
	int processed;
	double storedH;

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
	void resetBestWeight(){
		setBestWeight(DBL_MAX);
	}
	Edge* getParent() const {
		return parent;
	}

	void setParent( Edge* parent) {
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
	virtual double calculateH(Vertex* v){
		if(storedH == -1)
			storedH = sqrt((x - v->x) *(x - v->x)+(y - v->y)*(y - v->y) );
		return storedH;
	}
	double getStoredH() const {
		return storedH;
	}
	void resetStoredH(){
		storedH = -1;
	}
	struct DijsComp{
		bool operator()(const Vertex* v1, const Vertex* v2)const {
			return v1->getBestWeight() > v2->getBestWeight();
		}
	};
	struct AStarComp{
		bool operator()(const Vertex* v1, const Vertex* v2)const {
			double f1 = v1->getBestWeight() + v1->getStoredH();
			double f2 = v2->getBestWeight() + v2->getStoredH();
			if(f1 == f2){
				return v1->getStoredH() > v2->getStoredH();
			}else {
				return f1>f2;
			}
		}
	};

};


#endif

