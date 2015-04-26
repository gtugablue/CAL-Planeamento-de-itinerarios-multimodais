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

MetroEdge::MetroEdge(Vertex *src, Vertex *dst):
	TransportEdge(src, dst)
{
	this->visible = true;
	weight.setCost(0.2);
	weight.setTime(calculateTime());
	weight.setSwitchs(0);
}

MetroEdge::MetroEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
	TransportEdge(src, dst, line)
{
	this->visible = true;
	weight.setCost(0.2);
	weight.setTime(calculateTime());
	weight.setSwitchs(0);
}

double MetroEdge::getWeight()
{
	weight.setTime(
					calculateTime()
	);
	return weight.getWeight();
}

double MetroEdge::getSpeed() const
{
	return TransportSpeeds::getMetroSpeed();
}
