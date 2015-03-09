/*
 * Coordinates.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "Coordinates.h"

Coordinates::Coordinates(double latitude, double longitude): latitude(latitude), longitude(longitude)
{
}

double Coordinates::getLatitude() const
{
	return latitude;
}

double Coordinates::getLongitude() const
{
	return longitude;
}
