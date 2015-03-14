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
#include "BusEdge.h"
#include "BusRoute.h"

class Map {
private:
	std::vector<BusRoute> busRoutes;
public:
	Map();

	class Loader {
	private:
		static const std::string BusEdgesFolder;
		static const std::string busStopsFolder;
		static const std::string timetablesFolder;
		std::vector<std::string> getFilesInFolder(const std::string &folder) const;
		void parseJsonFile(const std::string file, rapidjson::Document &d) const;
		void parseXMLFile(const std::string file, rapidxml::xml_document<> &d) const;
		std::vector<BusStop> loadBusStops(const rapidjson::Document &d) const;
		std::vector<BusEdge> loadBusEdges(const rapidjson::Document &d) const;
	public:
		Map load();
	};
	friend class Loader;
	const std::vector<BusRoute>& getBusRoutes() const;
};

#endif /* SOURCE_MAP_H_ */
