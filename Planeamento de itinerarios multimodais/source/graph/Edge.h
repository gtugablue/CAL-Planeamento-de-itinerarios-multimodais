#ifndef EDGE_H
#define EDGE_H


using namespace std;

#include "../gui/SDLRGB.h"
#include "math.h"

class Vertex;

class Edge{

public:
    Edge(Vertex* src, Vertex* dst, double storedWeight = 0);
    virtual double getWeight() const;
    virtual void setStoredWeight(double storedWeight);
    virtual Vertex* getDst() const;
    virtual void setDst(Vertex* dst);
    virtual Vertex* getSrc() const;
    virtual void setSrc(Vertex* src);
    virtual void storeWeight();
    virtual double getStoredWeight() const;
    virtual SDLRGB getColor();
    virtual ~Edge();

protected:
	double storedWeight;

private:
	Vertex* src;
	Vertex* dst;
};


#endif
