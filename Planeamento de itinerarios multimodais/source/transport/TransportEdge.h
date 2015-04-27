/*
 * TransportEdge.h
 *
 *  Created on: 03/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_TRANSPORTEDGE_H_
#define SOURCE_TRANSPORTEDGE_H_

#include "../graph/Edge.h"
#include "Coordinates.h"
#include <vector>
#include "WeightInfo.h"
#include "TransportSpeeds.h"

class TransportEdge: public Edge {
protected:
	std::vector<Coordinates> line;
	WeightInfo weight;
	bool visible;
public:

	/**
	 * @brief class constructor
	 * @param src Edge's source vertex
	 * @param dst Edge's destination vertex
	 */
	TransportEdge(Vertex *src, Vertex *dst);

	/**
	 * @brief class constructor
	 * @param src Edge's source vertex
	 * @param dst Edge's destination vertex
	 * @param line set of points representing the edge's path (so that it might not be a straight line)
	 */
	TransportEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line);

	/**
	 * @brief adds a geographical point to the edge's set of points
	 * @param coords point to be added
	 */
	void addPoint(const Coordinates &coords);

	/**
	 * @brief calculates the edge's weight (using WightInfo)
	 * @return edge's weighted cost
	 */
	virtual double getWeight();

	/**
	 * @brief returns the WeightInfo of the edge (thus separating the different weights of crossing the edge)
	 * @return WeightInfo object representing edge
	 */
	WeightInfo getWeightInfo() { return weight; }

	/**
	 * @brief returns the set of points that represent the edge
	 * @return vector of points (Coordinates)
	 */
	const std::vector<Coordinates> &getLine() const;

	/**
	 * @brief calculates the speed of the edge's transport
	 * @return speed of the transport
	 */
	virtual double getSpeed() const { return TransportSpeeds::getWalkingSpeed(); }

	/**
	 * @brief calculates the time it takes to cross the edge
	 * @return time in seconds
	 */
	double calculateTime() const { return weight.getDistance() / getSpeed(); }

	/**
	 * @brief class destructor
	 */
	virtual ~TransportEdge() { }

	/**
	 * @brief returns a boolean that represents wether the edge must be drawn or not
	 * @return true if the edge must be drawn, false otherwise
	 */
	bool getVisible(){return visible;}
};

#endif /* SOURCE_TRANSPORTEDGE_H_ */
