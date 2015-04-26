/*
 * MetroRoute.cpp
 *
 *  Created on: 05/04/2015
 *      Author: Gustavo
 */

#include "MetroRoute.h"
#include "TransportSpeeds.h"

MetroRoute::MetroRoute(const std::string code, bool direction):
	TransportRoute(code, direction)
{
}

double MetroRoute::getSpeed() const
{
	return TransportSpeeds::getMetroSpeed();
}

MetroRoute::~MetroRoute() {
}
