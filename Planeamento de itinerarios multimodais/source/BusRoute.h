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
#include "BusLine.h"

class BusRoute {
private:
	std::vector<BusStop> busStops;
	std::vector<BusLine> busLines;
public:
	BusRoute(const std::vector<BusStop> &busStops, const std::vector<BusLine> &busLines);
	void print() const;
};

#endif /* SOURCE_BUSROUTE_H_ */
