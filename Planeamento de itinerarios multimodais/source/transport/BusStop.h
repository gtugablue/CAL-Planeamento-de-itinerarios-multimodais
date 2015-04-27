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

/**
 * @brief Represents a bus stop
 */
class BusStop : public TransportStop {
	std::string code;
public:
	/**
	 * @brief bus stop construtor
	 * @param code code of bus stop
	 * @param name name of bus stop
	 * @param coords coordinates of bus stop to create
	 * @param route_name name of the stop's route
	 */
	BusStop(const std::string &code, const std::string &name, const Coordinates &coords, const std::string &route_name);

	/**
	 * @brief bus stop's code
	 * @return code of bus stop
	 */
	const string &getCode() const { return code; }

	/**
	 * @brief print the bus stop
	 */
	void print() const;

	/**
	 * @brief get a string containing the name of the stop and its type
	 * @return string containing the information
	 */
	virtual std::string getNameAndType() const {
		//return TransportStop::getNameAndType();
		if(this->getTransportRoute() != NULL)
			return "Bus: " + name + "[ Line " + this->getTransportRoute()->getCode() + " ]";
		return "Bus: " + name + "[ Line X ]";
	}
};

#endif /* SOURCE_BUSSTOP_H_ */
