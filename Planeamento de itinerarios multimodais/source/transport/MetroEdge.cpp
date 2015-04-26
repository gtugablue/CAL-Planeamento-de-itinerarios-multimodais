/*
 * MetroEdge.cpp
 *
 *  Created on: 03/04/2015
 *      Author: Gustavo
 */

#include "MetroEdge.h"
#include "MetroRoute.h"
#include "TransportSpeeds.h"

using namespace std;

MetroEdge::MetroEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
	TransportEdge(src, dst, line)
{
	this->visible = true;
	weight.setCost(0);
	weight.setTime(calculateTime(weight.getDistance()));
	weight.setSwitchs(0);
}

double MetroEdge::getSpeed() const
{
	return TransportSpeeds::getMetroSpeed();
}
