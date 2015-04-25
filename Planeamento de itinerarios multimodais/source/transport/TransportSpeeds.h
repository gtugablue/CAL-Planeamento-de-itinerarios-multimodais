/*
 * TransportSpeeds.h
 *
 */

#ifndef TRANSPORT_SPEEDS
#define TRANSPORT_SPEEDS

#include <stdlib.h>
#include <algorithm>

class TransportSpeeds {
private:
	TransportSpeeds() {}
	static double busSpeed ;
	static double metroSpeed ;
	static double walkingSpeed;
public:
	static double getBusSpeed()  { return busSpeed; }
	static double getMetroSpeed()  { return metroSpeed; }
	static double getWalkingSpeed()  { return walkingSpeed; }
	static double getMaxSpeed(){
		return std::min(busSpeed, std::min(metroSpeed, walkingSpeed));
	}
};

#endif
