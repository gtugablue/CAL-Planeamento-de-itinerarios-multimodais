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
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidxml/rapidxml.hpp"
#include "include/rapidxml/rapidxml_utils.hpp"
#include "include/rapidxml/rapidxml_print.hpp"
#include "BusStop.h"
#include "BusLine.h"
#include "BusRoute.h"

class Map {
private:
	std::vector<BusRoute> busRoutes;
public:
	Map();
	void load();
	const std::vector<BusRoute>& getBusRoutes() const;
};

#endif /* SOURCE_MAP_H_ */
