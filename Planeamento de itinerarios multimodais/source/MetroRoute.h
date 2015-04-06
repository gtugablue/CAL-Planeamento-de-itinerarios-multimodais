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
	MetroRoute(const std::string code, bool direction);
	virtual ~MetroRoute();
};

#endif /* SOURCE_METROROUTE_H_ */
