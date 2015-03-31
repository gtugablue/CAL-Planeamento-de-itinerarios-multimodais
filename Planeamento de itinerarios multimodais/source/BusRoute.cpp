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

void BusRoute::interpolateSchedules() const
{
	vector<unsigned> keyIDs;
	for (size_t i = 0; i < busStops.size(); ++i)
	{
		if (busStops[i]->hasSchedule())
			keyIDs.push_back(i);
	}
	if (keyIDs.size() < 2)
		return; // Not enough data to interpolate

	for (size_t i = 0; i + 1 < keyIDs.size(); ++i)
	{
		double dist = 0;
		for (size_t j = keyIDs[i]; j < keyIDs[i + 1]; ++j)
		{
			dist += BusEdges[j].getDist();
		}

		for (size_t j = keyIDs[i]; j < keyIDs[i + 1]; ++j)
		{
			unsigned scheduleSize = busStops[keyIDs[i]]->getSchedule().size();
			for (size_t k = 0; k < scheduleSize; ++k)
			{
				set<Hour>::iterator it = busStops[keyIDs[i]]->getSchedule().begin();
				advance(it, k);
				set<Hour>::iterator it2 = busStops[keyIDs[i + 1]]->getSchedule().begin();
				advance(it2, k);
				Hour h = *it2 - *it;
				for (size_t l = keyIDs[i]; l < keyIDs[i + 1]; ++l)
				{
					busStops[l + 1]->addHour(h * (BusEdges[l].getDist() / dist));
					cout << h * (BusEdges[l].getDist() / dist) << endl;
				}
			}
		}
	}
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
