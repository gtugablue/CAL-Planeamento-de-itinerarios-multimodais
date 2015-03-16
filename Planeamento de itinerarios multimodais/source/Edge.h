#ifndef EDGE_H
#define EDGE_H


using namespace std;

#include "Vertex.h"
#include "SDLRGB.h"
#include "math.h"

class Edge{
private:
	static unsigned int lastID;
	const unsigned int id;
protected:
	double storedWeight;
	Vertex* src;
	Vertex* dst;
public:
    Edge(Vertex* src, Vertex* dst, double storedWeight = 0): id(0)
    {
        this->src = src;
        this->dst = dst;
        this->storedWeight = storedWeight;
    }

    virtual double getWeight() const;

    void setStoredWeight(double storedWeight)
    {
        this->storedWeight = storedWeight;
    }

    Vertex* getDst() const
    {
        return dst;
    }

    void setDst(Vertex* dst)
    {
        this->dst = dst;
    }

    Vertex* getSrc() const
    {
        return src;
    }

    void setSrc(Vertex* src)
    {
        this->src = src;
    }

    void storeWeight()
    {
        storedWeight = getWeight();
    };

    double getStoredWeight() const
    {
        return storedWeight;
    };

    SDLRGB getColor()
    {
        return SDLRGB(0, 0xFF, 0);
    }
};


#endif
