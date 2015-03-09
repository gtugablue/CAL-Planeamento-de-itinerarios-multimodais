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

	for (size_t i = 0; i < d["locations"].Size(); ++i)
	{
		rapidjson::Value &location = d["locations"][i];
		string geomdesc = location["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		BusStop(location["code"].GetString(), location["name"].GetString(), Coordinates(coords[0].GetDouble(), coords[1].GetDouble()));
	}
}
