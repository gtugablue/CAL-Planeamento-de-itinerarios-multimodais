/*
 * BusStop.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusStop.h"
#include <iostream>

BusStop::BusStop(const std::string &code, const std::string &name, const Coordinates &coords): code(code), name(name), coords(coords)
{
	std::cout << "code: " << code << std::endl;
	std::cout << "name: " << name << std::endl;
	std::cout << "coords: " << coords.getLatitude() << " - " << coords.getLongitude() << std::endl << std::endl;
}

const Coordinates& BusStop::getCoords() const {
	return coords;
}
