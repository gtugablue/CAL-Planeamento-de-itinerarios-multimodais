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
	transportStops.push_back(transportStop);
}

const vector<TransportStop *> &TransportRoute::getStops() const
{
	return transportStops;
}
