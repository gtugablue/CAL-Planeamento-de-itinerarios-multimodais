/*
 * TransportRoute.h
 *
 *  Created on: 05/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_TRANSPORTROUTE_H_
#define SOURCE_TRANSPORTROUTE_H_

#include <string>
#include <vector>
#include "TransportStop.h"

class TransportRoute {
protected:
	std::string code;
	bool direction;
	std::vector<TransportStop *> transportStops;
public:
	TransportRoute(const std::string code, bool direction): code(code), direction(direction) { }
	const std::string &getCode() const { return code; }
	virtual void addStop(TransportStop *transportStop);
	const std::vector<TransportStop *> &getStops() const;
	virtual ~TransportRoute() { };
};

#endif /* SOURCE_TRANSPORTROUTE_H_ */
