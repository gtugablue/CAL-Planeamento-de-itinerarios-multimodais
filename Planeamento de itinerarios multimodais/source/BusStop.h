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
#include "Vertex.h"

class BusStop : public Vertex {
	std::string code;
	std::string name;
	std::set<Hour> schedule;
public:
	BusStop(const std::string &code, const std::string &name, const Coordinates &coords);
	std::string getName() const { return name; }
	void print() const;
	void addHour(const Hour &hour);
	const std::set<Hour> &getSchedule() const;
	bool hasSchedule() const { return schedule.size() > 0; }
	bool operator==(const BusStop &busStop) const;
};

#endif /* SOURCE_BUSSTOP_H_ */
