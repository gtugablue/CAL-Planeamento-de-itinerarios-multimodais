/*
 * TransportEdge.cpp
 *
 *  Created on: 03/04/2015
 *      Author: Gustavo
 */

#include "TransportEdge.h"
#include "TransportStop.h"

using namespace std;

TransportEdge::TransportEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
	Edge(src, dst), line(line)
{
	double distance = 0;
	for (size_t i = 1; i < line.size(); ++i)
	{
		distance += line[i - 1].calcDist(line[i]);
	}
	weight.setCost(0.20);
	weight.setDistance(distance);
	weight.setSwitchs(0);
	weight.setTime(calculateTime(distance));
}

const vector<Coordinates> &TransportEdge::getLine() const
{
	return line;
}


void TransportEdge::addPoint(const Coordinates &coords)
{
	if (line.size() > 0)
		storedWeight += line[line.size() - 1].calcDist(coords);
	line.push_back(coords);
}

double TransportEdge::getWeight() const
{
	return weight.getWeight(((TransportStop *)getSrc())->getArrivalTime());
}
