/*
 * BusEdge.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "BusEdge.h"

using namespace std;

BusEdge::BusEdge(Vertex *src, Vertex *dst, const vector<Coordinates> &line):
		TransportEdge(src, dst, line)
{
}
