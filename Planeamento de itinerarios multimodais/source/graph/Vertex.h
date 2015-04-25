#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"
#include "../transport/Coordinates.h"
#include <iostream>
#include <cfloat>
#include <cmath>

class Vertex{
public:
	Vertex(const Coordinates &coords);
	std::vector<Edge*> getAdj()const;
	void addAdj(Vertex* v, double weight =0);
	void addEdge(Edge *edge);
	Coordinates getCoords() const;
	double getRenderX() const;
	double getRenderY() const;
	unsigned int getIndex() const;
	virtual unsigned int getRenderX();
	virtual unsigned int getRenderY();
	virtual ~Vertex();
	void setIndex(unsigned int index);
	double getBestWeight() const;
	void setBestWeight(double bestWeight);
	void resetBestWeight();
	Edge* getParent() const;
	virtual void setParent( Edge* parent);
	void resetProcessed();
	int getProcessed() const;
	void incProcessed();
	int getVisits() const;
	void resetVisits();
	void incVisits();
	virtual double calculateH(Vertex* v);
	double getStoredH() const;
	void resetStoredH();
	struct AStarComp{
		bool operator()(Vertex* v1, Vertex* v2)const {
			double f1 = v1->getBestWeight() + v1->getStoredH();
			double f2 = v2->getBestWeight() + v2->getStoredH();
			if(f1 == f2)
				return v1->getStoredH() > v2->getStoredH();
			else
				return f1 > f2;
		}
	};
	struct DijsComp{
		bool operator()(Vertex* v1, Vertex* v2) const{
			return v1->getBestWeight() > v2->getBestWeight();
		}
	};
protected:
	Coordinates coords;
private:
	unsigned int index;
	unsigned int x;
	unsigned int y;
	std::vector<Edge*> adj;
	double bestWeight;
	Edge* parent;
	int visits;
	int processed;
	double storedH;
};


#endif

