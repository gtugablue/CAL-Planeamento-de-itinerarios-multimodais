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

class MetroRoute: public TransportRoute {
public:
	static const double speed = 1;
	MetroRoute(const std::string code, bool direction);
	double getSpeed();
	virtual ~MetroRoute();
};

#endif /* SOURCE_METROROUTE_H_ */
