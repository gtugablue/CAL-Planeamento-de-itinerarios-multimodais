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
#include "Edge.h"
#include <iostream>
#include <iomanip>

class BusEdge: public Edge{
private:
	std::vector<Coordinates> line;
public:
	BusEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line);
	void addPoint(const Coordinates &coords);
	void print() const;
	double getDist() const { return storedWeight; }
	const std::vector<Coordinates>& getLine() const;
};

#endif /* SOURCE_BUSEDGE_H_ */
