/*
 * BusEdge.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusEdge.h"

using namespace std;

BusEdge::BusEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
		Edge(src, dst),
		line(line)
{
	storedWeight = 0;
	for (size_t i = 1; i < line.size(); ++i)
	{
		storedWeight += line[i - 1].calcDist(line[i]);
	}
}

const std::vector<Coordinates>& BusEdge::getLine() const
{
	return line;
}

void BusEdge::addPoint(const Coordinates &coords)
{
	if (line.size() > 0)
		storedWeight += line[line.size() - 1].calcDist(coords);
	line.push_back(coords);
}

void BusEdge::print() const
{
	/*cout << "Line length: " << storedWeight << " km" << endl;
	for (size_t i = 0; i < line.size(); ++i)
	{
		cout << setprecision(10) << line[i].getLatitude() << " - " << line[i].getLongitude() << endl;
	}*/
}
