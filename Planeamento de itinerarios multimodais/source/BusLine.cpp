/*
 * BusEdge.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusLine.h"
#include <iostream>

using namespace std;

BusLine::BusLine():
		length(0.0)
{

}

void BusLine::addPoint(const Coordinates &coords)
{
	line.push_back(coords);
	length += line[line.size() - 2].calcDist(coords);
}

void BusLine::print() const
{
	cout << "Line length: " << length << endl;
	for (size_t i = 0; i < line.size(); ++i)
	{
		cout << line[i].getLatitude() << " - " << line[i].getLongitude() << endl;
	}
}
