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
#include "TransportStop.h"

class BusStop : public TransportStop {
	std::string code;
public:
	BusStop(const std::string &code, const std::string &name, const Coordinates &coords);
	const string &getCode() const { return code; }
	void print() const;
};

#endif /* SOURCE_BUSSTOP_H_ */
