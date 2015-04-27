/*
 * MetroStop.cpp
 *
 *  Created on: 02/04/2015
 *      Author: Gustavo
 */

#include "MetroStop.h"

using namespace std;

MetroStop::MetroStop(const string name, const Coordinates &coords, const std::string& route_name):
		TransportStop(name, coords, route_name)
{
}
