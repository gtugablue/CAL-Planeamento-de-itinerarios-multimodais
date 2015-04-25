/*
 * MetroRoute.cpp
 *
 *  Created on: 05/04/2015
 *      Author: Gustavo
 */

#include "MetroRoute.h"

MetroRoute::MetroRoute(const std::string code, bool direction):
	TransportRoute(code, direction)
{
}

MetroRoute::~MetroRoute() {
}
