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

BusRoute::BusRoute(const string code, const vector<BusStop *> &busStops, const vector<BusEdge> &BusEdges):
				code(code), busStops(busStops), BusEdges(BusEdges)
{
}

const std::vector<BusEdge>& BusRoute::getBusEdges() const
{
	return BusEdges;
}

const std::vector<BusStop *>& BusRoute::getBusStops() const
{
	return busStops;
}

void BusRoute::print() const
{
	for (size_t i = 0; i < BusEdges.size(); ++i)
	{
		//busStops[i].print();
		//BusEdges[i].print();
		//cout << endl;
	}
	//busStops[BusEdges.size()].print();
}
