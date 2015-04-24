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

double Coordinates::calcDist(const Coordinates &coordinates) const
{
	double d2r = M_PI / 180.0;
	double dlong = (coordinates.longitude - longitude) * d2r;
	double dlat = (coordinates.latitude - latitude) * d2r;
	double a = pow(sin(dlat/2.0), 2) + cos(latitude*d2r) * cos(coordinates.latitude*d2r) * pow(sin(dlong/2.0), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	double d = 6367 * c;

	return d;
}
