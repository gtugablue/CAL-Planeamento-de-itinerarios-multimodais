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

/**
 * @brief Connection between two metro stops
 */
class MetroEdge: public TransportEdge {
public:
	/**
	 * @brief metro edge constructor
	 * @param src source vertex of edge
	 * @param dst destination vertex of edge
	 */
	MetroEdge(Vertex *src, Vertex *dst);

	/**
	 * @brief metro edge constructor
	 * @param src source vertex of edge
	 * @param dst destination vertex of edge
	 * @param line set of points belongingto the edge
	 */
	MetroEdge(Vertex *src, Vertex *dst, const std::vector<Coordinates> &line);

	/**
	 * @brief get the weight of the edge
	 * @return edge weight
	 */
	double getWeight();

	/**
	 * @brief get the speed of the metro
	 * @return speed of metro
	 */
	double getSpeed() const;
};

#endif /* SOURCE_METROEDGE_H_ */
