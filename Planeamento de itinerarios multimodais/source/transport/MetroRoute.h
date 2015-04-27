/*
 * MetroRoute.h
 *
 *  Created on: 05/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_METROROUTE_H_
#define SOURCE_METROROUTE_H_

#include <string>
#include <vector>
#include "TransportRoute.h"
#include "MetroStop.h"

/**
 * @brief Represents a Metro Route - set of metro stops ordered in a certain way
 */
class MetroRoute: public TransportRoute {
public:
	/**
	 * @brief class constructor
	 * @param code Route's code
	 * @param directior specifies the direction of the route (true and false are opposite route directions, for the same route)
	 */
	MetroRoute(const std::string code, bool direction);

	/**
	 * @brief returns the Metro's speed
	 */
	double getSpeed() const;

	/**
	 * @brief class destructor
	 */
	virtual ~MetroRoute();
};

#endif /* SOURCE_METROROUTE_H_ */
