/*
 * BusRoute.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_BUSROUTE_H_
#define SOURCE_BUSROUTE_H_

#include <vector>
#include "Coordinates.h"
#include "BusStop.h"
#include "BusEdge.h"
#include "Hour.h"
#include "TransportRoute.h"

/**
 * @brief Represents a BusRoute, having a set of BusStop 's ordered in a certain way
 */
class BusRoute: public TransportRoute {
private:
public:
	static const double speed = 1;
	/**
	 * @brief bus route construtor
	 * @param code code of busroute
	 * @param direction direction of route
	 */
	BusRoute(const std::string code, bool direction);

	/**
	 * @brief get speed of buses
	 * @return buss speed
	 */
	double getSpeed() const;
};

#endif /* SOURCE_BUSROUTE_H_ */
