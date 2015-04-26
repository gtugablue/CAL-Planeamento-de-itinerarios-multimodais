/*
 * BusEdge.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusEdge.h"
#include "TransportSpeeds.h"

using namespace std;

BusEdge::BusEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
	TransportEdge(src, dst, line)
{
	weight.setCost(0.2);
	weight.setTime(calculateTime());
	weight.setSwitchs(0);
	this->visible = true;
}

double BusEdge::getSpeed() const
{
	return TransportSpeeds::getBusSpeed();
}
