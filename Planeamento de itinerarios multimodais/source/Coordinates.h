/*
 * Coordinates.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_COORDINATES_H_
#define SOURCE_COORDINATES_H_

class Coordinates {
private:
	double latitude;
	double longitude;
public:
	Coordinates(double latitude, double longitude);
	double getLatitude() const;
	double getLongitude() const;
};

#endif /* SOURCE_COORDINATES_H_ */
