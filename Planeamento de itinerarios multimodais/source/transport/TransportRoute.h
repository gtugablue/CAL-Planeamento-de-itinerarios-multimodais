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

class TransportStop;

/**
 * @brief represents a route, i.e., the set of stops that a "line" is made of
 */
class TransportRoute {
protected:
	std::string code;
	bool direction;
	std::vector<TransportStop *> transportStops;
public:
	/**
	 * @brief class constructor
	 * @param code Codename for the route (e.x. 603)
	 * @param direction each value represents a direction, each being the reverse of the other
	 */
	TransportRoute(const std::string code, bool direction): code(code), direction(direction) { }

	/**
	 * @brief returns the route's code
	 */
	const std::string &getCode() const { return code; }

	/**
	 * @brief adds a stop to the route
	 * @param transportStop Stop to be added
	 */
	virtual void addStop(TransportStop *transportStop);

	/**
	 * @brief sets the route's stops to a given vector
	 * @param stops vector with the new set of stops
	 */
	void setStops(std::vector<TransportStop *> stops);

	/**
	 * @brief gets the set of stops of the route
	 * @return vector of stops
	 */
	const std::vector<TransportStop *> &getStops() const;

	/**
	 * @brief returns the speed of the route's transport
	 */
	virtual double getSpeed() const = 0;

	/**
	 * @brief class destructor
	 */
	virtual ~TransportRoute() { };
};

#endif /* SOURCE_TRANSPORTROUTE_H_ */
