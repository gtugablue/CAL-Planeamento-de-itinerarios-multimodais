/*
 * TransportStop.h
 *
 *  Created on: 02/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_TRANSPORTSTOP_H_
#define SOURCE_TRANSPORTSTOP_H_

#include "Vertex.h"
#include "Coordinates.h"
#include <string>
#include "Hour.h"

class TransportStop: public Vertex {
protected:
	std::string name;
	std::vector<Hour> schedule;
	Hour arrival;
public:
	TransportStop(const std::string &name, const Coordinates &coords);
	std::string getName() const { return name; }
	void addHour(const Hour &hour);
	const std::vector<Hour> &getSchedule() const;
	bool hasSchedule() const { return schedule.size() > 0; }
	virtual bool operator==(const TransportStop &transportStop) const;
	virtual ~TransportStop();
};

#endif /* SOURCE_TRANSPORTSTOP_H_ */
