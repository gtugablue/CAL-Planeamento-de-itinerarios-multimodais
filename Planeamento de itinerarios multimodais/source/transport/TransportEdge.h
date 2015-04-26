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
	TransportEdge(Vertex *src, Vertex *dst);
	TransportEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line);
	void addPoint(const Coordinates &coords);
	virtual double getWeight();
	WeightInfo getWeightInfo() { return weight; }
	const std::vector<Coordinates> &getLine() const;
	virtual double getSpeed() const { return TransportSpeeds::getWalkingSpeed(); }
	virtual double calculateTime() const { return weight.getDistance() / getSpeed(); }
	virtual ~TransportEdge() { }
	bool getVisible(){return visible;}
};

#endif /* SOURCE_TRANSPORTEDGE_H_ */
