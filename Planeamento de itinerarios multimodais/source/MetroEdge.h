/*
 * MetroEdge.h
 *
 *  Created on: 03/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_METROEDGE_H_
#define SOURCE_METROEDGE_H_

#include "TransportEdge.h"
#include <vector>

class MetroEdge: public TransportEdge {
public:
	MetroEdge(Vertex *src, Vertex *dst, const std::vector<Coordinates> &line);
};

#endif /* SOURCE_METROEDGE_H_ */
