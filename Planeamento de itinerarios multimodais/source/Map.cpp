/*
 * Map.cpp
 *
 *  Created on: 09/03/2015
 *      Author: Gustavo
 */

#include "Map.h"

using namespace std;

Map::Map() {
	// TODO Auto-generated constructor stub

}

const std::vector<BusRoute>& Map::getBusRoutes() const {
	return busRoutes;
}

void Map::load()
{
	ifstream infile("data/linedraw/201-0.txt");
	stringstream ss;
	ss << infile.rdbuf();
	rapidjson::Document d;
	d.Parse(ss.str().c_str());
	infile.close();

	vector<BusStop> busStops;
	for (size_t i = 0; i < d["locations"].Size(); ++i)
	{
		rapidjson::Value &location = d["locations"][i];
		string geomdesc = location["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		busStops.push_back(BusStop(location["code"].GetString(), location["name"].GetString(), Coordinates(coords[0].GetDouble(), coords[1].GetDouble())));
	}

	vector<BusLine> busLines;
	for (size_t i = 0; i < d["route"].Size(); ++i)
	{
		rapidjson::Value &line = d["route"][i];
		string geomdesc = line["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		BusLine busLine;
		for (size_t j = 0; j < coords.Size(); ++j)
		{
			Coordinates coord(coords[j][0].GetDouble(), coords[j][1].GetDouble());
			busLine.addPoint(coord);
		}
		busLines.push_back(busLine);
	}

	ifstream infile2("data/horarios_tab/201-0-1-1.xml");
	stringstream ss2;
	ss2 << infile2.rdbuf();
	infile2.close();


	rapidxml::xml_document<> d2;
	char xmlText[ss2.str().size() + 1];
	strcpy(xmlText, ss2.str().c_str());
	d2.parse<0>(xmlText);

	rapidxml::xml_node<> *node = d2.first_node("table");
	node = node->first_node("tr");
	node = node->first_node("th");
	cout << "XML Test: " << node->value() << endl;

	busRoutes.push_back(BusRoute(busStops, busLines));
	busRoutes[0].print();
}
