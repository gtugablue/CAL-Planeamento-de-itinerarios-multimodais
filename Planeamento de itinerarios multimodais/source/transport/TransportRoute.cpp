/*
 * TransportRoute.cpp
 *
 *  Created on: 05/04/2015
 *      Author: Gustavo
 */

#include "TransportRoute.h"

using namespace std;

void TransportRoute::addStop(TransportStop *transportStop)
{
	transportStop->setTransportRoute(this);
	transportStops.push_back(transportStop);
}

const vector<TransportStop *> &TransportRoute::getStops() const
{
	return transportStops;
}

void TransportRoute::setStops(std::vector<TransportStop *> stops)
{
	for (size_t i = 0; i < stops.size(); ++i)
	{
		stops[i]->setTransportRoute(this);
	}
	transportStops = stops;
}
