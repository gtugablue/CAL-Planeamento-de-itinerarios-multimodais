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

	BusRoute busRoute(busStops, busLines);
	busRoute.print();
}
