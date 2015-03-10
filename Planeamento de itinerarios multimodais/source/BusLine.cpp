/*
 * BusEdge.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusLine.h"
#include <iostream>

using namespace std;

BusLine::BusLine()
{

}

void BusLine::addPoint(const Coordinates &coords)
{
	line.push_back(coords);
}

void BusLine::print() const
{
	for (size_t i = 0; i < line.size(); ++i)
	{
		cout << line[i].getLatitude() << " - " << line[i].getLongitude() << endl;
	}
}
