/*
 * BusStop.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_BUSSTOP_H_
#define SOURCE_BUSSTOP_H_

#include <string>
#include "Coordinates.h"
#include <set>
#include "Hour.h"

class BusStop{
	std::string code;
	std::string name;
	Coordinates coords;
	std::set<Hour> schedule;
public:
	BusStop(const std::string &code, const std::string &name, const Coordinates &coords);
	const Coordinates& getCoords() const;
	void print() const;
	bool operator==(const BusStop &busStop) const;
};

#endif /* SOURCE_BUSSTOP_H_ */
