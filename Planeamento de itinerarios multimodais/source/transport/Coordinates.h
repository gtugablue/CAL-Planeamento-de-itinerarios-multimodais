/*
 * Coordinates.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_COORDINATES_H_
#define SOURCE_COORDINATES_H_

#include <math.h>

/**
 * @brief Interface to store latitude and longitude of points
 */
class Coordinates{
private:
	double latitude;
	double longitude;
public:
	/**
	 * @brief coordinate constructor
	 * @param latitude latitude of coordinate
	 * @param longitude longitude of coordinate
	 */
	Coordinates(double latitude, double longitude);

	/**
	 * @brief get latitude of coordinate
	 * @return latitude of coordinate
	 */
	double getLatitude() const;

	/**
	 * @brief get longitude of coordinate
	 * @return longitude of coordinate
	 */
	double getLongitude() const;
	/**
	 * @brief bus stop construtor
	 * @param code code of bus stop
	 * @param name name of bus stop
	 * @param coords coordinates of bus stop to create
	 */
	double calcDist(const Coordinates &coordinates) const;
	/**
	 * @brief bus stop construtor
	 * @param code code of bus stop
	 * @param name name of bus stop
	 * @param coords coordinates of bus stop to create
	 */
	double calcDirectDistSquare(const Coordinates &coordinates) const;
};

#endif /* SOURCE_COORDINATES_H_ */
