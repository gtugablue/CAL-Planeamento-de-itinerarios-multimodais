/*
 * MetroRoute.cpp
 *
 *  Created on: 05/04/2015
 *      Author: Gustavo
 */

#include "MetroRoute.h"
#include "Metro.h"

MetroRoute::MetroRoute(const std::string code, bool direction):
	TransportRoute(code, direction)
{
}

double MetroRoute::getSpeed() const
{
	return Metro::getInstance().getSpeed();
}

MetroRoute::~MetroRoute() {
}
