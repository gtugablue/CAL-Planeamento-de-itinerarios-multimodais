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

class BusEdge: public TransportEdge {
public:
	BusEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line);
	void print() const;
	virtual double calculateTime(double distance) const { return 0; }
	virtual ~BusEdge() { }
};

#endif /* SOURCE_BUSEDGE_H_ */
