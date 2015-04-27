/*
 * BusEdge.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_BUSEDGE_H_
#define SOURCE_BUSEDGE_H_

#include <vector>
#include "Coordinates.h"
#include "TransportEdge.h"
#include <iostream>
#include <iomanip>

/**
 * @brief represents a connection between two BusStop 's
 */
class BusEdge: public TransportEdge {
public:
	/**
	 * @brief bus edge constructor
	 * @param src source vertex for edge
	 * @param dst source vertex for edge
	 * @param line set of points for the line
	 */
	BusEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line);
	/**
	 * @brief print the busedge
	 */
	void print() const;

	/**
	 * @brief get the speed of a bus
	 * @return bus speed
	 */
	virtual double getSpeed() const;

	/**
	 * @brief get weight of edge
	 * @return  weight of edge
	 */
	double getWeight();

	/**
	 * @brief edge destructor
	 */
	virtual ~BusEdge() { }
};

#endif /* SOURCE_BUSEDGE_H_ */
