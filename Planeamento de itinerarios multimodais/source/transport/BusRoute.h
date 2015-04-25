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

class BusRoute: public TransportRoute {
private:
public:
	static const double speed = 1;
	BusRoute(const std::string code, bool direction);
	double getSpeed() const;
};

#endif /* SOURCE_BUSROUTE_H_ */
