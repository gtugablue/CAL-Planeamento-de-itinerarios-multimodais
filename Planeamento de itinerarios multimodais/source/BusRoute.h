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

class BusRoute {
private:
	std::vector<BusStop *> busStops;
	std::vector<BusEdge> BusEdges;
public:
	BusRoute(const std::vector<BusStop *> &busStops, const std::vector<BusEdge> &BusEdges);
	void print() const;
	const std::vector<BusEdge>& getBusEdges() const;
	const std::vector<BusStop *>& getBusStops() const;
};

#endif /* SOURCE_BUSROUTE_H_ */
