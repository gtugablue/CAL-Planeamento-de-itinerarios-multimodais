/*
 * BusEdge.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusLine.h"
#include <iostream>
#include <iomanip>

using namespace std;

BusLine::BusLine():
		length(0.0)
{

}

double BusLine::getLength() const
{
	return length;
}

const std::vector<Coordinates>& BusLine::getLine() const
{
	return line;
}

void BusLine::addPoint(const Coordinates &coords)
{
	if (line.size() > 0)
		length += line[line.size() - 1].calcDist(coords);
	line.push_back(coords);
}

void BusLine::print() const
{
	cout << "Line length: " << length << " km" << endl;
	for (size_t i = 0; i < line.size(); ++i)
	{
		cout << setprecision(10) << line[i].getLatitude() << " - " << line[i].getLongitude() << endl;
	}
}
