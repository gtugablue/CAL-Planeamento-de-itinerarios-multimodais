/*
 * MetroStop.h
 *
 *  Created on: 02/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_METROSTOP_H_
#define SOURCE_METROSTOP_H_

#include "TransportStop.h"
#include "../graph/Vertex.h"
#include <string>
#include "Coordinates.h"

class MetroStop: public TransportStop {
public:
	static const double speed = 1;

	/**
	 * @brief class constructor
	 * @param name Stop's name
	 * @param coords Coordinates of the Stop
	 */
	MetroStop(const std::string name, const Coordinates &coords);

	/**
	 * @brief returns the stop's name and type (e.x. Metro: IPO)
	 * @return string with stop name and type
	 */
	virtual std::string getNameAndType() const { return "Metro: " + name; }
};

#endif /* SOURCE_METROSTOP_H_ */
