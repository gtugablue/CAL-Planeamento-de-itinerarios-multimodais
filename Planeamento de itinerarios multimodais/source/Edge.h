#ifndef EDGE_H
#define EDGE_H


using namespace std;

#include "SDLRGB.h"
#include "math.h"

class Vertex;

class Edge{

public:
    Edge(Vertex* src, Vertex* dst, double storedWeight = 0);
    virtual double getWeight() const;
    void setStoredWeight(double storedWeight);
    Vertex* getDst() const;
    void setDst(Vertex* dst);
    Vertex* getSrc() const;
    void setSrc(Vertex* src);
    void storeWeight();
    double getStoredWeight() const;
    virtual SDLRGB getColor();
    virtual ~Edge();

protected:
	double storedWeight;

private:
	Vertex* src;
	Vertex* dst;
};


#endif
