/*
 * MetroRoute.cpp
 *
 *  Created on: 05/04/2015
 *      Author: Gustavo
 */

#include "MetroRoute.h"

MetroRoute::MetroRoute(const std::string code, bool direction, const std::vector<MetroStop *> &metroStops):
	code(code), direction(direction), metroStops(metroStops)
{
}

MetroRoute::~MetroRoute() {
}

