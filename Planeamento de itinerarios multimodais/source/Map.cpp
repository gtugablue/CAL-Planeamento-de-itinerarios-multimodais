/*
 * Map.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "Map.h"
#include <dirent/dirent.h>
#include <algorithm>

using namespace std;

const string Map::Loader::BusEdgesFolder = "data/linedraw/";
const string Map::Loader::busStopsFolder = "data/linestops/";
const string Map::Loader::timetablesFolder = "data/horarios_tab/";

Map::Map() {
}

const std::vector<BusRoute>& Map::getBusRoutes() const {
	return busRoutes;
}

const std::vector<Vertex *>& Map::getVertices() const
{
	return vertices;
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
	rapidxml::file<> xmlFile(file.c_str());
	d.parse<0>(xmlFile.data());
}

std::vector<std::string> Map::Loader::getFilesInFolder(const std::string &folder) const
{
	vector<string> fileNames;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (folder.c_str())) != NULL) {
		readdir(dir); // Skip "."
		readdir(dir); // Skip ".."
		while ((ent = readdir (dir)) != NULL) {
			fileNames.push_back(ent->d_name);
		}
		closedir (dir);
	} else {
		/* could not open directory */
		perror ("Couldn't open directory.");
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
	vector<BusEdge> busEdges;
	for (size_t i = 0; i < d["route"].Size(); ++i)
	{
		const rapidjson::Value &line = d["route"][i];
		string geomdesc = line["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		vector<Coordinates> coordinates;
		for (size_t j = 0; j < coords.Size(); ++j)
		{
			Coordinates coord(coords[j][1].GetDouble(), coords[j][0].GetDouble());
			coordinates.push_back(coord);
		}
		Vertex *src = new Vertex(coordinates[0]);
		Vertex *dst = new Vertex(coordinates[coordinates.size() - 1]);
		busEdges.push_back(BusEdge(src, dst, coordinates));
	}
	return busEdges;
}

Map Map::Loader::load()
{
	Map map;
	vector<string> fileNames = getFilesInFolder(BusEdgesFolder);
	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		rapidjson::Document d;
		parseJsonFile(BusEdgesFolder + fileNames[i], d);
		vector<BusStop> loadedBusStops = loadBusStops(d);
		vector<BusStop *> finalBusStops;
		for (size_t j = 0; j < loadedBusStops.size(); ++j)
		{
			finalBusStops.push_back(new BusStop(loadedBusStops[j])); // TODO: free
		}
		vector<BusEdge> BusEdges = loadBusEdges(d);
		map.busRoutes.push_back(BusRoute(finalBusStops, BusEdges));
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

	/*// Road test
	rapidxml::xml_document<> d;
	parseXMLFile("data/map.xml", d);
	rapidxml::xml_node <> *node = d.first_node("osm");
	for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
		//
	}*/

	return map;
}
