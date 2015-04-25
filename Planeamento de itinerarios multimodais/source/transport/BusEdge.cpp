/*
 * BusEdge.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusEdge.h"
#include "Bus.h"

using namespace std;

BusEdge::BusEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
	TransportEdge(src, dst, line)
{
	weight.setTime(calculateTime(weight.getDistance()));
}

double BusEdge::getSpeed() const
{
	return Bus::getInstance().getSpeed();
}
