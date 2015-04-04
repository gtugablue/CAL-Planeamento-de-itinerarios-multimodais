/*
 * Map.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "Map.h"
#include <dirent/dirent.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;

const string Map::Loader::BusEdgesFolder = "data/linedraw/";
const string Map::Loader::busStopsFolder = "data/linestops/";
const string Map::Loader::timetablesFolder = "data/horarios_tab/";

Map::Map() {
}

const std::vector<BusRoute>& Map::getBusRoutes() const {
	return busRoutes;
}

const std::vector<BusStop *>& Map::getBusStops() const
{
	return busStops;
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

void Map::Loader::parseXMLFile(rapidxml::file<> &file, rapidxml::xml_document<> &d) const
{
	d.parse<rapidxml::parse_full|rapidxml::parse_trim_whitespace>(file.data());
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

vector<BusStop *> Map::Loader::loadBusStops(const rapidjson::Document &d) const
{
	vector<BusStop *> busStops;
	for (size_t i = 0; i < d["locations"].Size(); ++i)
	{
		const rapidjson::Value &location = d["locations"][i];
		string geomdesc = location["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		busStops.push_back(new BusStop(location["code"].GetString(), location["name"].GetString(), Coordinates(coords[1].GetDouble(), coords[0].GetDouble())));
	}
	return busStops;
}

vector<BusEdge> Map::Loader::loadBusEdges(const rapidjson::Document &d) const
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

void Map::Loader::loadSchedule(const BusRoute &busRoute) const
{
	rapidxml::xml_document<> d;
	rapidxml::file<> xmlFile((timetablesFolder + busRoute.getCode() + "-0-1-1").c_str());
	parseXMLFile(xmlFile, d);
	rapidxml::xml_node<> *table = d.first_node("table");
	rapidxml::xml_node<> *header = table->first_node("tr");

	vector<BusStop *> keyBusStops;
	for (rapidxml::xml_node<> *child = header->first_node(); child; child = child->next_sibling())
	{
		unsigned minDistance = -1;
		unsigned minIndex;
		for (size_t i = 0; i < busRoute.getBusStops().size(); ++i)
		{
			unsigned distance = levenshteinDistance(busRoute.getBusStops()[i]->getName(), child->value());
			if (distance < minDistance)
			{
				minDistance = distance;
				minIndex = i;
			}
		}
		//cout << "route: " << busRoute.getCode() << " score: " << minDistance << " name1: " << busRoute.getBusStops()[minIndex]->getName() << " name2: " << child->value() << endl;
		keyBusStops.push_back(busRoute.getBusStops()[minIndex]);
	}

	for (rapidxml::xml_node<> *body = header->next_sibling("tr"); body; body = body->next_sibling("tr"))
	{
		size_t i = 0;
		for (rapidxml::xml_node<> *td = body->first_node("td"); td; td = td->next_sibling(), ++i)
		{
			assert(i < keyBusStops.size());
			keyBusStops[i]->addHour(Hour(td->value()));
		}
	}
	busRoute.interpolateSchedules();
}

vector<MetroStop *> Map::Loader::loadMetro(rapidjson::Document &d) const
{
	vector<pair<Coordinates, string> > nodes;

	const rapidjson::Value &elements = d["elements"];
	for (size_t i = 0; i < elements.Size(); ++i)
	{
		if (elements[i]["type"] == "node")
		{
			Coordinates coords(elements[i]["lat"].GetDouble(), elements[i]["lon"].GetDouble());
			nodes.push_back(make_pair(coords, elements[i].GetString()));
		}
	}

	// TODO
}

unsigned Map::Loader::levenshteinDistance(const string &s1, const string &s2) const
{
	// http://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance

	const size_t len1 = s1.size(), len2 = s2.size();
	vector<unsigned int> col(len2+1), prevCol(len2+1);

	for (unsigned int i = 0; i < prevCol.size(); i++)
		prevCol[i] = i;
	for (unsigned int i = 0; i < len1; i++) {
		col[0] = i+1;
		for (unsigned int j = 0; j < len2; j++)
			col[j+1] = std::min( std::min(prevCol[1 + j] + 1, col[j] + 1),
					prevCol[j] + (s1[i]==s2[j] ? 0 : 1) );
		col.swap(prevCol);
	}
	return prevCol[len2];
}

Map Map::Loader::load()
{
	Map map;
	vector<string> fileNames = getFilesInFolder(BusEdgesFolder);
	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		//cout << "Progress: " <<( unsigned)(100 * ((double)i/fileNames.size())) << "%" << endl;
		rapidjson::Document d;
		parseJsonFile(BusEdgesFolder + fileNames[i], d);
		vector<BusStop *> loadedBusStops = loadBusStops(d);
		map.busStops.insert(map.busStops.end(), loadedBusStops.begin(), loadedBusStops.end());
		vector<BusEdge> busEdges = loadBusEdges(d);
		char temp[fileNames[i].length() + 1];
		strcpy(temp, fileNames[i].c_str());
		string code = string(strtok(temp, "-."));
		bool direction = string(strtok(NULL, "-.")) == "0" ? false : true;
		BusRoute busRoute(code, direction, loadedBusStops, busEdges);
		loadSchedule(busRoute);
		map.busRoutes.push_back(busRoute);
		//map.busRoutes[i].print();
	}
	/*// Road test
	rapidxml::xml_document<> d;
	rapidxml::file<> xmlFile("data/map.xml");
	cout << "Parsing map..." << endl;
	parseXMLFile(xmlFile, d);
	cout << "Map parsed! Transversing it..." << endl;

	rapidxml::xml_node<> *node = d.first_node("osm");
	for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
		if (string(child->name()) != "node")
			continue;
		Coordinates coords(strtod(child->first_attribute("lat")->value(), NULL),
				strtod(child->first_attribute("lon")->value(), NULL));
		Vertex vertex(coords);
		map.vertices.push_back(new Vertex(vertex));
	}
	cout << "Map transversed!" << endl;*/

	return map;
}
