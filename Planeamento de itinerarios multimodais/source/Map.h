/*
 * Map.h
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_MAP_H_
#define SOURCE_MAP_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "BusStop.h"
#include "BusLine.h"
#include "BusRoute.h"

class Map {
public:
	Map();
	void load();
};

#endif /* SOURCE_MAP_H_ */
