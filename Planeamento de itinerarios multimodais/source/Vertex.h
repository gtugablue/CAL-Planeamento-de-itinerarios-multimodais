#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"
#include "Coordinates.h"
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
	void setParent( Edge* parent);
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
		bool operator()(const Vertex* v1, const Vertex* v2) const;
	};
	struct DijsComp{
		bool operator()(const Vertex* v1, const Vertex* v2) const;
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

