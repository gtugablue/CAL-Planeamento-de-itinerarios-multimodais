#ifndef EDGE_H
#define EDGE_H


using namespace std;

#include "../gui/SDLRGB.h"
#include "math.h"

class Vertex;

/**
 * @brief Generic Edge interface
 */
class Edge{

public:
	/**
	 * @brief edge construtor
	 * @param src source vertex for edge
	 * @param dst source vertex for edge
	 * @param storedWeight source vertex for edge
	 */
	Edge(Vertex* src, Vertex* dst, double storedWeight = 0);

	/**
	 * @brief get the weight of this edge
	 * @return weight of edge
	 */
	virtual double getWeight();

	/**
	 * @brief store a weight value in edge
	 * @param value to store
	 */
	virtual void setStoredWeight(double storedWeight);

	/**
	 * @brief get the destination of this edge
	 * @return destination
	 */
	virtual Vertex* getDst() const;

	/**
	 * @brief set the destination of this edge
	 * @param dst new destination
	 */
	virtual void setDst(Vertex* dst);

	/**
	 * @brief get the source of this edge
	 * @return source
	 */
	virtual Vertex* getSrc() const;

	/**
	 * @brief set the source of this edge
	 * @param src new source
	 */
	virtual void setSrc(Vertex* src);

	/**
	 * @brief store weight in edge
	 */
	virtual void storeWeight();

	/**
	 * @brief retrived weight stored in edge
	 * @return stored value
	 */
	virtual double getStoredWeight() const;

	/**
	 * @brief get the vertex's color
	 * @return color of vertex
	 */
	virtual SDLRGB getColor();

	/**
	 * @brief edge destructor
	 */
	virtual ~Edge();

protected:
	double storedWeight;

private:
	Vertex* src;
	Vertex* dst;
};


#endif
