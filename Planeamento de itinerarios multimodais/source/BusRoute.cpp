/*
 * BusRoute.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusRoute.h"
#include <iostream>
#include "include/rapidxml/rapidxml.hpp"

using namespace std;

BusRoute::BusRoute(const vector<BusStop> &busStops, const vector<BusLine> &busLines):
				busStops(busStops), busLines(busLines)
{
}

const std::vector<BusLine>& BusRoute::getBusLines() const
{
	return busLines;
}

const std::vector<BusStop>& BusRoute::getBusStops() const
{
	return busStops;
}

void BusRoute::print() const
{
	for (size_t i = 0; i < busLines.size(); ++i)
	{
		busStops[i].print();
		busLines[i].print();
		cout << endl;
	}
	busStops[busLines.size()].print();
}
