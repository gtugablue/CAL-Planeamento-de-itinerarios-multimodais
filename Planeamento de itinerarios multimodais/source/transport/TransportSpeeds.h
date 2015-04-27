/*
 * TransportSpeeds.h
 *
 */

#ifndef TRANSPORT_SPEEDS
#define TRANSPORT_SPEEDS

#include <stdlib.h>
#include <algorithm>

/**
 * @brief generic inteface to preserve the speeds of the different means of transport
 */
class TransportSpeeds {
private:
	TransportSpeeds() {}
	static double busSpeed ;
	static double metroSpeed ;
	static double walkingSpeed;
public:
	/**
	 * @brief Returns the estimated bus speed
	 */
	static double getBusSpeed()  { return busSpeed; }

	/**
	 * @brief Returns the estimated metro speed
	 */
	static double getMetroSpeed()  { return metroSpeed; }

	/**
	 * @brief Returns the estimated walking speed
	 */
	static double getWalkingSpeed()  { return walkingSpeed; }

	/**
	 * @brief Returns the maximum of the transport's speed
	 */
	static double getMaxSpeed() { return std::max(busSpeed, std::max(metroSpeed, walkingSpeed)); }
};

#endif
