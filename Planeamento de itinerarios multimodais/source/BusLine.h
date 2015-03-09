/*
 * BusLine.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_BUSLINE_H_
#define SOURCE_BUSLINE_H_

#include <vector>
#include "Coordinates.h"

class BusLine {
private:
	std::vector<Coordinates> route;
public:
	BusLine(const std::vector<Coordinates> &route);
};

#endif /* SOURCE_BUSLINE_H_ */
