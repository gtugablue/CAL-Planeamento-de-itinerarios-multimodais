/*
 * MetroEdge.cpp
 *
 *  Created on: 03/04/2015
 *      Author: Gustavo
 */

#include "MetroEdge.h"
#include "MetroRoute.h"
#include "Metro.h"

using namespace std;

MetroEdge::MetroEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
	TransportEdge(src, dst, line)
{
	weight.setTime(calculateTime(weight.getDistance()));
}

double MetroEdge::getSpeed() const
{
	return Metro::getInstance().getSpeed();
}
