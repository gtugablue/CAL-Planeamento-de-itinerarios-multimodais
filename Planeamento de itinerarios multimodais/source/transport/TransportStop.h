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
#include "TransportSpeeds.h"
#include <queue>
#include "TransportRoute.h"

class TransportRoute;

class TransportStop: public Vertex {
protected:
	std::string name;
	std::string route_name;
	TransportRoute *transportRoute;
	std::vector<Hour> schedule;
	Hour arrival;
public:
	/**
	 * @brief Default class constructor
	 * @param name TransportStop's name (e.x. "AV. DOS ALIADOS")
	 * @param coords Coordinates of the stop
	 * @param route_name name for the Stop's route
	 */
	TransportStop(const std::string &name, const Coordinates &coords, const std::string &route_name);

	string getRouteName() const {return route_name;}

	/**
	 * @brief Get Stop name
	 * @return Name of the transport stop
	 */
	std::string getName() const { return name; }

	/**
	 * @brief set Stop name
	 * @return Name of the transport stop
	 */
	void setRouteName(std::string name) {route_name = name;}

	/**
	 * @brief Get Stop's route name
	 * @return Name of the transport stop route
	 */
	std::string getRoute() const {return route_name; }

	/**
	 * @brief Get arrival time at stop
	 * @return The Hour the path arrived at the stop during path calculation.
	 */
	const Hour &getArrivalTime() const { return arrival; }

	/**
	 * @brief Adds an hour to the Stop. Every Stop has several Hour's, representing all the moments when transports stop there
	 * @param hour Hour to be added
	 */
	void addHour(const Hour &hour);

	/**
	 * @brief Gets the route in which the TransportStop is located
	 * @return Stop's route
	 */
	TransportRoute *getTransportRoute() const;

	/**
	 * @brief Gets the set of times (Hour's) when transports stop at this stop
	 * @return vector of Hour objets representing the schedule
	 */
	const std::vector<Hour> &getSchedule() const;

	/**
	 * @brief Assign the Stop to a specific route
	 * @param transportRoute Route the stop is to be assigned to
	 */
	void setTransportRoute(TransportRoute *transportRoute);

	/**
	 * @brief Sets the Stop's schedule after a given one
	 * @param schedule Vector of Hours to be set as the stop's schedule
	 */
	void setSchedule(std::vector<Hour> schedule) { this->schedule = schedule; }

	/**
	 * @brief Determines if there is any schedule assigned to the stop
	 * @return true when the stop has a schedule, false otherwise
	 */
	bool hasSchedule() const { return schedule.size() > 0; }

	/**
	 * @brief Sets the stop's vertex's parent to the one specified
	 * @param parent Edge to be assigned as parent for the vertex
	 */
	virtual void setParent( Edge* parent);

	/**
	 * @brief Calculates the time between the arrival hour at the vertex and the next transport arriving
	 * @param currentHour time of arrival at the stop
	 * @return ammount of seconds between the currentHour and the next transport
	 */
	double calcWaitingTime(Hour currentHour) const;

	/**
	 * @brief Calculates the value of the heuristic (A* algorithm) to a certain destination vertex
	 * @param v destination vertex
	 * @return value of the heuristic
	 */
	double calculateH(Vertex * v);

	/**
	 * @brief Compares two TransportStop's
	 * @param transportStop Stop to compare to
	 * @return true if both are equal, false otherwise
	 */
	virtual bool operator==(const TransportStop &transportStop) const;

	/**
	 * @brief destructor for the class
	 */
	virtual ~TransportStop();

	/**
	 * @brief adds the Stop's vertex to the graph specified (used with user's click position)
	 * @param g Graph to be changed
	 */
	void userAddToGraph(Graph* g);

	/**
	 * @brief removes the user added Vertex from the graph
	 * @param g Graph to remove vertex from
	 */
	void userRemovefromGraph(Graph* g);

	/**
	 * @brief returns a string with the Stop's name and type (e.x. Bus: AV. DOS ALIADOS)
	 * @return string with the specified text
	 */
	virtual std::string getNameAndType() const { return name; }

	/**
	 * @brief sets the arrival time at the stop to the one specified
	 * @param newarrival Hour value to be set
	 */
	void setArrivalTime(Hour newarrival) {this->arrival = newarrival;}
};

class TransportStopDistCompare
{
public:
	static Coordinates reference;

	/**
	 * @brief compares the distance between the two transport stops and the reference point
	 * @param ts1 first transportstop
	 * @param ts2 second transportstop
	 * @return true if ts1 is closest to ts2
	 */
	bool operator() (const TransportStop *ts1, const TransportStop *ts2)
	{
		return reference.calcDirectDistSquare(ts1->getCoords()) > reference.calcDirectDistSquare(ts2->getCoords());
	}
};

#endif /* SOURCE_TRANSPORTSTOP_H_ */
