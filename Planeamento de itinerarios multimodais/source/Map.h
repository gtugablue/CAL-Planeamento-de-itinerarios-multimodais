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
#include "Vertex.h"
#include "MetroStop.h"
#include "MetroRoute.h"

class Map {
private:
	std::vector<BusRoute> busRoutes;
	std::vector<BusStop *> busStops;
public:
	Map();

	class Loader {
	private:
		static const std::string dataFolder;
		static const std::string BusEdgesFolder;
		static const std::string busStopsFolder;
		static const std::string timetablesFolder;
		std::vector<std::string> getFilesInFolder(const std::string &folder) const;
		void parseJsonFile(const std::string file, rapidjson::Document &d) const;
		void parseXMLFile(rapidxml::file<> &file, rapidxml::xml_document<> &d) const;
		std::vector<BusStop *> loadBusStops(const rapidjson::Document &d) const;
		std::vector<BusEdge> loadBusEdges(const rapidjson::Document &d) const;
		void loadSchedule(const BusRoute &busRoute) const;
		std::vector<std::pair<MetroStop *, std::string> > loadMetroStopNodes(rapidjson::Document &d) const;
		std::vector<MetroStop *> loadMetroStops(rapidjson::Document &d) const;
		MetroStop *findClosestMetroStop(const std::vector<MetroStop *> metroStops, const std::string metroStopCode) const;
		std::vector<MetroRoute> loadMetroRoutes() const;
		unsigned levenshteinDistance(const string &s1, const string &s2) const;
	public:
		Map load();
	};
	friend class Loader;
	const std::vector<BusRoute>& getBusRoutes() const;
	const std::vector<BusStop *>& getBusStops() const;
};

#endif /* SOURCE_MAP_H_ */
