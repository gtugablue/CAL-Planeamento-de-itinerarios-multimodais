/*
 * MetroStop.h
 *
 *  Created on: 02/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_METROSTOP_H_
#define SOURCE_METROSTOP_H_

#include "TransportStop.h"
#include "Vertex.h"
#include <string>
#include "Coordinates.h"

class MetroStop: public TransportStop {
public:
	MetroStop(const std::string name, const Coordinates &coords);
};

#endif /* SOURCE_METROSTOP_H_ */
