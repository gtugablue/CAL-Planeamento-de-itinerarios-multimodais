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
#include <stdlib.h>
#include "BusRoute.h"
#include "MetroRoute.h"
#include "TransportEdge.h"
#include <queue>
#include "TransportStop.h"

using namespace std;

const string Map::Loader::dataFolder = "data/";
const string Map::Loader::BusEdgesFolder = Map::Loader::dataFolder + "linedraw/";
const string Map::Loader::busStopsFolder = Map::Loader::dataFolder + "linestops/";
const string Map::Loader::timetablesFolder = Map::Loader::dataFolder + "horarios_tab/";
const string Map::Loader::connectingEdgesPreProcessingFile = Map::Loader::dataFolder + "connectingEdges.txt";

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

vector<BusStop *> Map::Loader::loadBusStops(const rapidjson::Document &d, const std::string& route_code) const
{
	vector<BusStop *> busStops;
	for (int i = d["locations"].Size() - 1; i >= 0; --i)
	{
		const rapidjson::Value &location = d["locations"][i];
		string geomdesc = location["geomdesc"].GetString();
		rapidjson::Document geo;
		geo.Parse(geomdesc.c_str());
		rapidjson::Value &coords = geo["coordinates"];
		busStops.push_back(new BusStop(location["code"].GetString(), location["name"].GetString(), Coordinates(coords[1].GetDouble(), coords[0].GetDouble()), route_code));
	}
	return busStops;
}

vector<BusEdge> Map::Loader::loadBusEdges(const rapidjson::Document &d, vector<BusStop *> &busStops) const
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
		if (string(geo["type"].GetString()) == "LineString")
		{
			for (int j = coords.Size() - 1; j >= 0; --j)
			{
				Coordinates coord(coords[j][1].GetDouble(), coords[j][0].GetDouble());
				coordinates.push_back(coord);
			}
		}
		else if (string(geo["type"].GetString()) == "MultiLineString")
		{
			for (size_t j = 0; j < coords.Size(); ++j)
			{
				rapidjson::Value &coords2 = coords[j];
				for (size_t k = 0; k < coords2.Size(); ++k)
				{
					Coordinates coord(coords2[k][1].GetDouble(), coords2[k][0].GetDouble());
					coordinates.push_back(coord);
				}
			}
		}
		else throw InvalidInputException("Unknown line type.");
		busEdges.push_back(BusEdge(busStops[i], busStops[i + 1], coordinates));
	}
	return busEdges;
}

void Map::Loader::loadBusRoutes(std::vector<BusRoute> &busRoutes) const
{
	// Loop through all Bus Routes
	vector<string> fileNames = getFilesInFolder(BusEdgesFolder);
	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		try {
			// Load Bus Stops code, name and coordinates
			rapidjson::Document d;
			parseJsonFile(BusEdgesFolder + fileNames[i], d);

			if (d["route"].Size() == 0) throw InvalidInputException("File has no data to be read.");
			if (d["route"].Size() != d["locations"].Size() - 1) throw InvalidInputException("File is corrupt.");

			/*vector<BusStop *> busStops = loadBusStops(d);

			// Load corresponding Bus Edges
			vector<BusEdge> busEdges = loadBusEdges(d, busStops);*/

			// Load Bus Route info
			bool direction;
			string code;
			findBusInfoFromFileName(fileNames[i], code, direction);
			BusRoute busRoute(code, direction);

			vector<BusStop *> busStops = loadBusStops(d, code);

			// Load corresponding Bus Edges
			vector<BusEdge> busEdges = loadBusEdges(d, busStops);

			// Add adjacent edges to each vertex and add everything to the Bus Route
			for (size_t i = 0; i < busStops.size() - 1; ++i)
			{
				busStops[i]->addEdge(new BusEdge(busEdges[i])); // TODO delete
				busRoute.addStop(busStops[i]);
			}

			// Add last Bus Stop
			busRoute.addStop(busStops[busStops.size() - 1]);

			// Generate a random schedule
			generateRandomTransportSchedule(rand() % 60 + 70, &busRoute);

			// Add Route to the Bus Routes vector
			busRoutes.push_back(busRoute);
		}
		catch (InvalidInputException &e)
		{
			// Do nothing
		}
	}
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

vector<MetroStop> Map::Loader::loadMetroStops(rapidjson::Document &d) const
{
	vector<MetroStop> metroStops;

	const rapidjson::Value &elements = d["elements"];
	for (size_t i = 0; i < elements.Size(); ++i)
	{
		if (elements[i]["type"] == "node")
		{
			Coordinates coords(elements[i]["lat"].GetDouble(), elements[i]["lon"].GetDouble());
			if (elements[i].HasMember("tags") && elements[i]["tags"].HasMember("name"))
			{
				const rapidjson::Value &tags = elements[i]["tags"];
				MetroStop metroStop = MetroStop(tags["name"].GetString(), coords, ""); // TODO delete
				metroStops.push_back(metroStop);
			}
		}
	}
	return metroStops;
}

MetroStop *Map::Loader::loadMetroStop(MetroStop &metroStop)
{
	return new MetroStop(metroStop.getName(), metroStop.getCoords(), "");
}

MetroStop *Map::Loader::findClosestMetroStop(vector<MetroStop> &metroStops, const string &metroStopCode) const
{
	MetroStop *closest;
	unsigned minScore = -1;
	for (size_t i = 0; i < metroStops.size(); ++i)
	{
		unsigned score = levenshteinDistance(metroStops[i].getName(), metroStopCode);
		if (score < minScore)
		{
			closest = &metroStops[i];
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

void Map::Loader::loadMetroRoutes(std::vector<MetroRoute> &metroRoutes) const
{
	rapidjson::Document dStops;
	parseJsonFile(dataFolder + "metro.json", dStops);
	vector<MetroStop> metroStops = loadMetroStops(dStops);

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
		MetroStop *metroStop = new MetroStop(*findClosestMetroStop(metroStops, dLines[i]["stops"][0].GetString())); // TODO delete
		metroStop->setRouteName(code);
		metroRoute.addStop(metroStop);

		// Loop through all other stops
		for (size_t j = 1; j < dLines[i]["stops"].Size(); ++j)
		{
			metroStop = new MetroStop(*findClosestMetroStop(metroStops, dLines[i]["stops"][j].GetString())); // TODO delete
			metroStop->setRouteName(code);
			metroRoute.addStop(metroStop);

			// Create Metro Edge
			vector<Coordinates> line;
			line.push_back(metroRoute.getStops()[j - 1]->getCoords());
			line.push_back(metroStop->getCoords());
			MetroEdge metroEdge(metroRoute.getStops()[j - 1], metroStop, line);

			// Add Metro Edge as adjacent to Metro Stop
			metroRoute.getStops()[j - 1]->addEdge(new MetroEdge(metroEdge)); // TODO delete
		}

		// Generate a random schedule
		generateRandomTransportSchedule(rand() % 50 + 250, &metroRoute);

		// Add the Route to the Metro Route vector
		metroRoutes.push_back(metroRoute);

		// Do the same but in the opposite order
		MetroRoute metroRoute2(code, true);
		MetroStop *last = new MetroStop(*findClosestMetroStop(metroStops, dLines[i]["stops"][dLines[i]["stops"].Size() - 1].GetString())); // TODO delete
		metroStop->setRouteName(code);
		metroRoute2.addStop(metroStop);
		for (int j = dLines[i]["stops"].Size() - 2; j >= 0; --j)
		{
			metroStop = new MetroStop(*findClosestMetroStop(metroStops, dLines[i]["stops"][j].GetString())); // TODO delete
			last->addEdge(new MetroEdge(last, metroStop));
			metroStop->setRouteName(code);
			metroRoute2.addStop(metroStop);
			last = metroStop;
		}
		generateRandomTransportSchedule(rand() % 50 + 250, &metroRoute2);
		metroRoutes.push_back(metroRoute2);
	}
}

Hour Map::Loader::generateRandomHour() const
{
	return Hour(rand() % 24, rand() % 60);
}

void Map::Loader::generateRandomTransportSchedule(unsigned dailyFrequency, TransportRoute *transportRoute) const
{
	vector<TransportStop *> transportStops = transportRoute->getStops();
	vector<Hour> linearSchedule;
	linearSchedule.push_back(generateRandomHour());
	for (size_t i = 0; i < transportStops.size(); ++i)
	{
		if (i == 0)
			linearSchedule.push_back(generateRandomHour());
		else
		{
			double dt = transportStops[i - 1]->getCoords().calcDist(transportStops[i]->getCoords()) * transportRoute->getSpeed();
			linearSchedule.push_back(linearSchedule[linearSchedule.size() - 1] + dt);
		}
		double period = 24 * 60 * 60 / dailyFrequency;
		vector<Hour> schedule;
		schedule.push_back(linearSchedule[i - 1]);
		for (size_t j = 0; j < dailyFrequency; ++j)
		{
			schedule.push_back(schedule[j] + period);
		}
		transportStops[i]->setSchedule(schedule);
	}
	transportRoute->setStops(transportStops);
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

void Map::Loader::createConnectingEdges(vector<BusRoute> &busRoutes, vector<MetroRoute> &metroRoutes) const
{
	for (size_t i = 0; i < busRoutes.size(); ++i)
	{
		for (size_t j = 0; j < busRoutes[i].getStops().size(); ++j)
		{
			connectToClosests(busRoutes, metroRoutes, busRoutes[i].getStops()[j]);
		}
	}
	for (size_t i = 0; i < metroRoutes.size(); ++i)
	{
		for (size_t j = 0; j < metroRoutes[i].getStops().size(); ++j)
		{
			connectToClosests(busRoutes, metroRoutes, metroRoutes[i].getStops()[j]);
		}
	}
}

void Map::Loader::connectToClosests(vector<BusRoute> &busRoutes, vector<MetroRoute> &metroRoutes, TransportStop *transportStop) const
{
	TransportStopDistCompare::reference = transportStop->getCoords();
	priority_queue<TransportStop *, vector<TransportStop *>, TransportStopDistCompare> transportStops;
	for (size_t i = 0; i < busRoutes.size(); ++i)
	{
		for (size_t j = 0; j < busRoutes[i].getStops().size(); ++j)
		{
			transportStops.push(busRoutes[i].getStops()[j]);
		}
	}
	for (size_t i = 0; i < metroRoutes.size(); ++i)
	{
		for (size_t j = 0; j < metroRoutes[i].getStops().size(); ++j)
		{
			transportStops.push(metroRoutes[i].getStops()[j]);
		}
	}
	size_t counter = 0;
	while (counter < 25 && !transportStops.empty())
	{
		TransportStop *closest = transportStops.top();
		transportStops.pop();
		//if (transportStop->getTransportRoute() == closest->getTransportRoute())
		//continue;
		if(transportStop == closest)
			continue;
		TransportEdge *edge1 = new TransportEdge(transportStop, closest); // TODO delete
		TransportEdge *edge2 = new TransportEdge(closest, transportStop); // TODO delete
		transportStop->addEdge(edge1);
		closest->addEdge(edge2);
		++counter;
	}
}

void Map::Loader::saveConnectingEdges(const vector<BusRoute> &busRoutes, const vector<MetroRoute> &metroRoutes) const
{
	vector<vector<pair <unsigned, unsigned> > > dests1;
	vector<vector<pair <unsigned, unsigned> > > dests2;
	for (size_t i = 0; i < busRoutes.size(); ++i)
	{
		for (size_t j = 0; j < busRoutes[i].getStops().size(); ++j)
		{
			vector<pair<unsigned, unsigned> > innerDests;
			TransportStop *transportStop = busRoutes[i].getStops()[j];
			for (size_t k = 0; k < transportStop->getAdj().size(); k++)
			{
				if (transportStop == transportStop->getAdj()[k]->getDst())
					continue;
				innerDests.push_back(make_pair(i, j));
			}
			dests1.push_back(innerDests);
		}
	}
	for (size_t i = 0; i < metroRoutes.size(); ++i)
	{
		for (size_t j = 0; j < metroRoutes[i].getStops().size(); ++j)
		{
			vector<pair<unsigned, unsigned> > innerDests;
			TransportStop *transportStop = metroRoutes[i].getStops()[j];
			for (size_t k = 0; k < transportStop->getAdj().size(); k++)
			{
				if (transportStop == transportStop->getAdj()[k]->getDst())
					continue;
				innerDests.push_back(make_pair(i, j));
			}
			dests2.push_back(innerDests);
		}
	}

	ofstream outfile(connectingEdgesPreProcessingFile.c_str());

	for (size_t i = 0; i < dests1.size(); ++i)
	{
		outfile << dests1[i].size() << endl;
		for (size_t j = 0; j < dests1[i].size(); ++j)
		{
			outfile << "1" << endl;
			outfile << dests1[i][j].first << endl;
			outfile << dests1[i][j].second << endl;
		}
	}
	for (size_t i = 0; i < dests2.size(); ++i)
	{
		outfile << dests2[i].size() << endl;
		for (size_t j = 0; j < dests2[i].size(); ++j)
		{
			outfile << "2" << endl;
			outfile << dests2[i][j].first << endl;
			outfile << dests2[i][j].second << endl;
		}
	}
	outfile.close();
}

void Map::Loader::loadConnectingEdges(const vector<BusRoute> &busRoutes, const vector<MetroRoute> &metroRoutes) const
{
	ifstream infile(connectingEdgesPreProcessingFile.c_str());

	// Bus src
	for (size_t i = 0; i < busRoutes.size(); ++i)
	{
		unsigned m;
		infile >> m;
		for (size_t j = 0; j < m; ++j)
		{
			unsigned o, p, q;
			infile >> o;
			if (o == 1) // Bus dst
			{
				infile >> p;
				infile >> q;
				TransportEdge *edge = new TransportEdge(busRoutes[i].getStops()[j], busRoutes[p].getStops()[q]);
				busRoutes[i].getStops()[j]->addEdge(edge);
			}
			else // Metro dst
			{
				infile >> p;
				infile >> q;
				TransportEdge *edge = new TransportEdge(busRoutes[i].getStops()[j], metroRoutes[p].getStops()[q]);
				busRoutes[i].getStops()[j]->addEdge(edge);
			}
		}
	}

	// Metro src
	for (size_t i = 0; i < metroRoutes.size(); ++i)
	{
		unsigned m;
		infile >> m;
		for (size_t j = 0; j < m; ++j)
		{
			unsigned o, p, q;
			infile >> o;
			if (o == 1) // Bus dst
			{
				infile >> p;
				infile >> q;
				TransportEdge *edge = new TransportEdge(metroRoutes[i].getStops()[j], busRoutes[p].getStops()[q]);
				metroRoutes[i].getStops()[j]->addEdge(edge);
			}
			else // Metro dst
			{
				infile >> p;
				infile >> q;
				TransportEdge *edge = new TransportEdge(metroRoutes[i].getStops()[j], metroRoutes[p].getStops()[q]);
				metroRoutes[i].getStops()[j]->addEdge(edge);
			}
		}
	}

	infile.close();
}

void Map::Loader::load(Map &map)
{
	cout << "Loading bus routes..." << endl;
	loadBusRoutes(map.busRoutes);
	cout << "Bus routes successfully loaded." << endl;
	cout << "Loading metro routes..." << endl;
	cout << "Metro routes successfully loaded." << endl;
	loadMetroRoutes(map.metroRoutes);
	cout << "Creating connecting edges.." << endl;
	createConnectingEdges(map.busRoutes, map.metroRoutes);
	cout << "Connecting edges successfully created." << endl;
	saveConnectingEdges(map.busRoutes, map.metroRoutes);
	//loadConnectingEdges(map.busRoutes, map.metroRoutes);
	//cout << "Loaded connecting edges." << endl;
}

Graph Map::generateGraph() const
{
	Graph graph;
	for (size_t i = 0; i < busRoutes.size(); ++i)
	{
		vector<TransportStop*> ts = busRoutes[i].getStops();
		for (size_t j = 0; j < ts.size(); ++j)
		{
			graph.addVertex(ts[j]);
			for (size_t k = 0; k < ts[j]->getAdj().size(); ++k)
			{
				graph.addVertex(ts[j]->getAdj()[k]->getDst());
			}
		}
	}
	for (size_t i = 0; i < metroRoutes.size(); ++i)
	{
		vector<TransportStop*> ts = metroRoutes[i].getStops();
		for (size_t j = 0; j < ts.size(); ++j)
		{
			graph.addVertex(ts[j]);
			for (size_t k = 0; k < ts[j]->getAdj().size(); ++k)
			{
				graph.addVertex(ts[j]->getAdj()[k]->getDst());
			}
		}
	}
	return graph;
}
