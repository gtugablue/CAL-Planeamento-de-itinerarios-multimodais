/*
 * TransportStop.h
 *
 *  Created on: 02/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_TRANSPORTSTOP_H_
#define SOURCE_TRANSPORTSTOP_H_

#include "../graph/Vertex.h"
#include "../graph/Graph.h"
#include "Coordinates.h"
#include "TransportEdge.h"
#include <string>
#include "Hour.h"
#include <queue>

class TransportRoute;

class TransportStop: public Vertex {
protected:
	std::string name;
	TransportRoute *transportRoute;
	std::vector<Hour> schedule;
	Hour arrival;
public:
	TransportStop(const std::string &name, const Coordinates &coords);
	std::string getName() const { return name; }
	const Hour &getArrivalTime() const { return arrival; }
	void addHour(const Hour &hour);
	TransportRoute *getTransportRoute() const;
	const std::vector<Hour> &getSchedule() const;
	void setTransportRoute(TransportRoute *transportRoute);
	void setSchedule(std::vector<Hour> schedule) { this->schedule = schedule; }
	bool hasSchedule() const { return schedule.size() > 0; }
	double calculateH(Vertex * v) const;
	virtual bool operator==(const TransportStop &transportStop) const;
	virtual ~TransportStop();
	void userAddToGraph(Graph* g);
	void userRemovefromGraph(Graph* g);
};

class TransportStopDistCompare
{
public:
	static Coordinates reference;
    bool operator() (const TransportStop *ts1, const TransportStop *ts2)
    {
        return reference.calcDirectDistSquare(ts1->getCoords()) > reference.calcDirectDistSquare(ts2->getCoords());
    }
};

#endif /* SOURCE_TRANSPORTSTOP_H_ */
