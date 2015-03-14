/*
 * Map.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "Map.h"
#include <dirent/dirent.h>

using namespace std;

const string Map::Loader::BusEdgesFolder = "data/linedraw/";
const string Map::Loader::busStopsFolder = "data/linestops/";
const string Map::Loader::timetablesFolder = "data/horarios_tab/";

Map::Map() {
}

const std::vector<BusRoute>& Map::getBusRoutes() const {
	return busRoutes;
}

void Map::Loader::parseJsonFile(const std::string file, rapidjson::Document &d) const
{
	ifstream infile(file.c_str());
	infile.exceptions(ios::failbit | ios::badbit);
	stringstream ss;
	ss << infile.rdbuf();
	d.Parse(ss.str().c_str());
	infile.close();
}

void Map::Loader::parseXMLFile(const std::string file, rapidxml::xml_document<> &d) const
{
	ifstream infile(file.c_str());
	infile.exceptions(ios::failbit | ios::badbit);
	stringstream ss;
	ss << infile.rdbuf();
	infile.close();
	char xmlText[ss.str().size() + 1];
	strcpy(xmlText, ss.str().c_str());
	d.parse<0>(xmlText);
}

std::vector<std::string> Map::Loader::getFilesInFolder(const std::string &folder) const
{
	vector<string> fileNames;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (folder.c_str())) != NULL) {
		/* print all the files and directories within directory */
		readdir(dir); // Skip "."
		readdir(dir); // Skip ".."
		while ((ent = readdir (dir)) != NULL) {
			fileNames.push_back(ent->d_name);
		}
		closedir (dir);
	} else {
		/* could not open directory */
		perror ("");
		return fileNames;
	}

	return fileNames;
}

std::vector<BusStop> Map::Loader::loadBusStops(const rapidjson::Document &d) const
{
	vector<BusStop> busStops;
	for (size_t i = 0; i < d["locations"].Size(); ++i)
	{
		const rapidjson::Value &location = d["locations"][i];
		string geomdesc = location["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		busStops.push_back(BusStop(location["code"].GetString(), location["name"].GetString(), Coordinates(coords[1].GetDouble(), coords[0].GetDouble())));
	}
	return busStops;
}

std::vector<BusEdge> Map::Loader::loadBusEdges(const rapidjson::Document &d) const
{
	vector<BusEdge> BusEdges;
	for (size_t i = 0; i < d["route"].Size(); ++i)
	{
		const rapidjson::Value &line = d["route"][i];
		string geomdesc = line["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		BusEdge BusEdge;
		for (size_t j = 0; j < coords.Size(); ++j)
		{
			Coordinates coord(coords[j][1].GetDouble(), coords[j][0].GetDouble());
			BusEdge.addPoint(coord);
		}
		BusEdges.push_back(BusEdge);
	}
	return BusEdges;
}

Map Map::Loader::load()
{
	Map map;
	vector<string> fileNames = getFilesInFolder(BusEdgesFolder);
	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		rapidjson::Document d;
		parseJsonFile(BusEdgesFolder + fileNames[i], d);
		vector<BusStop> busStops = loadBusStops(d);
		vector<BusEdge> BusEdges = loadBusEdges(d);
		map.busRoutes.push_back(BusRoute(busStops, BusEdges));
		map.busRoutes[i].print();
	}

	fileNames = getFilesInFolder(timetablesFolder);
	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		rapidxml::xml_document<> d2;
		parseXMLFile(timetablesFolder + fileNames[i], d2);
		rapidxml::xml_node<> *node = d2.first_node("table");
		node = node->first_node("tr");
		node = node->first_node("th");
		cout << "XML Test: " << node->value() << endl;
	}
	return map;
}
