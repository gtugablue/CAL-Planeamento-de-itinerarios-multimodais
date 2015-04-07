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
#include "MetroEdge.h"

using namespace std;

const string Map::Loader::dataFolder = "data/";
const string Map::Loader::BusEdgesFolder = Map::Loader::dataFolder + "linedraw/";
const string Map::Loader::busStopsFolder = Map::Loader::dataFolder + "linestops/";
const string Map::Loader::timetablesFolder = Map::Loader::dataFolder + "horarios_tab/";

Map::Map() {
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

void Map::Loader::findBusInfoFromFileName(const string &fileName, std::string &code, bool &direction) const
{
	char temp[fileName.length() + 1];
	strcpy(temp, fileName.c_str());
	code = string(strtok(temp, "-."));
	direction = string(strtok(NULL, "-.")) == "0" ? false : true;
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

vector<BusRoute> Map::Loader::loadBusRoutes() const
{
	vector<BusRoute> busRoutes;

	// Loop through all Bus Routes
	vector<string> fileNames = getFilesInFolder(BusEdgesFolder);
	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		// Load Bus Stops code, name and coordinates
		rapidjson::Document d;
		parseJsonFile(BusEdgesFolder + fileNames[i], d);
		vector<BusStop *> busStops = loadBusStops(d);

		// Load corresponding Bus Edges
		vector<BusEdge> busEdges = loadBusEdges(d);

		// Load Bus Route info
		bool direction;
		string code;
		findBusInfoFromFileName(fileNames[i], code, direction);
		BusRoute busRoute(code, direction);

		// Add adjacent edges to each vertex and add everything to the Bus Route
		for (size_t i = 0; i < busStops.size() - 1; ++i)
		{
			busStops[i]->addEdge(new BusEdge(busEdges[i])); // TODO delete
			busRoute.addStop(busStops[i]);
		}

		// Add last Bus Stop
		busRoute.addStop(busStops[busStops.size() - 1]);

		// Add Route to the Bus Routes vector
		busRoutes.push_back(busRoute);
	}
	return busRoutes;
}

void Map::Loader::loadSchedule(const BusRoute &busRoute) const
{
	/*
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
	busRoute.interpolateSchedules();*/
}

vector<MetroStop *> Map::Loader::loadMetroStops(rapidjson::Document &d) const
{
	vector<MetroStop *> metroStops;

	const rapidjson::Value &elements = d["elements"];
	for (size_t i = 0; i < elements.Size(); ++i)
	{
		if (elements[i]["type"] == "node")
		{
			Coordinates coords(elements[i]["lat"].GetDouble(), elements[i]["lon"].GetDouble());
			if (elements[i].HasMember("tags") && elements[i]["tags"].HasMember("name"))
			{
				const rapidjson::Value &tags = elements[i]["tags"];
				MetroStop *metroStop = new MetroStop(tags["name"].GetString(), coords); // TODO delete
				metroStops.push_back(metroStop);
			}
		}
	}
	return metroStops;
}

MetroStop *Map::Loader::findClosestMetroStop(const vector<MetroStop *> metroStops, const string metroStopCode) const
{
	MetroStop *closest;
	unsigned minScore = -1;
	for (size_t i = 0; i < metroStops.size(); ++i)
	{
		unsigned score = levenshteinDistance(metroStops[i]->getName(), metroStopCode);
		if (score < minScore)
		{
			closest = metroStops[i];
			minScore = score;
		}
	}
	if (minScore > 3)
	{
		cout << "Warning: Couldn't find a corresponding Metro Stop in json data. Info:" << endl;
		cout << "Score: " << minScore << " Searching: " << metroStopCode << " Found: " << closest->getName() << endl;
	}
	return closest;
}

vector<MetroRoute> Map::Loader::loadMetroRoutes() const
{
	vector<MetroRoute> metroRoutes;
	rapidjson::Document dStops;
	parseJsonFile(dataFolder + "metro.json", dStops);
	vector<MetroStop *> metroStops = loadMetroStops(dStops);

	rapidjson::Document dLines;
	parseJsonFile(dataFolder + "metroLines.json", dLines);

	// Loop through all lines
	for (size_t i = 0; i < dLines.Size(); ++i)
	{
		// Get line's name
		string code = dLines[i]["code"].GetString();

		// Create Metro Route
		MetroRoute metroRoute(code, true);

		// Add first stop
		MetroStop *metroStop = findClosestMetroStop(metroStops, dLines[i]["stops"][0].GetString());
		metroRoute.addStop(metroStop);

		// Loop through all other stops
		for (size_t j = 1; j < dLines[i]["stops"].Size(); ++j)
		{
			metroStop = findClosestMetroStop(metroStops, dLines[i]["stops"][j].GetString());
			metroRoute.addStop(metroStop);

			// Create Metro Edge
			vector<Coordinates> line;
			line.push_back(metroRoute.getStops()[j - 1]->getCoords());
			line.push_back(metroStop->getCoords());
			MetroEdge metroEdge(metroRoute.getStops()[j - 1], metroStop, line);

			// Add Metro Edge as adjacent to Metro Stop
			metroRoute.getStops()[j - 1]->addEdge(new MetroEdge(metroEdge)); // TODO delete
		}

		// Add the Route to the Metro Route vector
		metroRoutes.push_back(metroRoute);
	}

	return metroRoutes;
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
	map.busRoutes = loadBusRoutes();
	map.metroRoutes = loadMetroRoutes();
	return map;
}
