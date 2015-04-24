#include "WeightInfo.h"

double WeightInfo::timeWeight = 0;
double WeightInfo::distanceWeight = 0;
double WeightInfo::switchWeight = 0;
double WeightInfo::costWeight = 0;

double WeightInfo::getWeight(Hour currentHour) const{
	return cost*costWeight + distance * distanceWeight + switchs * switchWeight + time * timeWeight;
}

double WeightInfo::getCost() const {
	return cost;
}

void WeightInfo::setCost(double cost) {
	this->cost = cost;
}

double WeightInfo::getCostWeight() {
	return costWeight;
}

void WeightInfo::setCostWeight(double costWeight) {
	WeightInfo::costWeight = costWeight;
}

double WeightInfo::getDistance() const {
	return distance;
}

void WeightInfo::setDistance(double distance) {
	this->distance = distance;
}

double WeightInfo::getDistanceWeight() {
	return distanceWeight;
}

void WeightInfo::setDistanceWeight(double distanceWeight) {
	WeightInfo::distanceWeight = distanceWeight;
}

double WeightInfo::getSwitchs() const {
	return switchs;
}

void WeightInfo::setSwitchs(double switchs) {
	this->switchs = switchs;
}

double WeightInfo::getSwitchWeight() {
	return switchWeight;
}

void WeightInfo::setSwitchWeight(double switchWeight) {
	WeightInfo::switchWeight = switchWeight;
}

double WeightInfo::getTime() const {
	return time;
}

void WeightInfo::setTime(double time) {
	this->time = time;
}

double WeightInfo::getTimeWeight() {
	return timeWeight;
}

void WeightInfo::setTimeWeight(double timeWeight) {
	WeightInfo::timeWeight = timeWeight;
}
