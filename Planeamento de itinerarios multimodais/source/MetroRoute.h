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
#include "MetroStop.h"

class MetroRoute {
private:
	std::string code;
	bool direction;
	std::vector<MetroStop *> metroStops;
public:
	MetroRoute(const std::string code, bool direction, const std::vector<MetroStop *> &metroStops);
	const std::string &getCode() const { return code; }
	virtual ~MetroRoute();
};

#endif /* SOURCE_METROROUTE_H_ */
