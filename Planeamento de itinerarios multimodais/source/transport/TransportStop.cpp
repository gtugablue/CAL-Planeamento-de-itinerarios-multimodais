/*
 * TransportStop.cpp
 *
 *  Created on: 02/04/2015
 *      Author: Gustavo
 */

#include "TransportStop.h"

using namespace std;

TransportStop::TransportStop(const std::string &name, const Coordinates &coords):
	Vertex(coords), name(name)
{
}

void TransportStop::addHour(const Hour &hour)
{
	schedule.push_back(hour);
}

const vector<Hour> &TransportStop::getSchedule() const
{
	return schedule;
}

bool TransportStop::operator==(const TransportStop &transportStop) const
{
	return name == transportStop.name;
}

TransportStop::~TransportStop()
{

}
double TransportStop::calculateH(Vertex * v){
	TransportStop* ts = dynamic_cast<TransportStop*>(v);
	if(ts == NULL)
		return 0;
	double dist = this->getCoords().calcDist(v->getCoords());
	//TODO alterar!!!
	double maxv = 1;
	//
	return dist / maxv * WeightInfo::getTimeWeight() + dist*WeightInfo::getDistanceWeight();
}
