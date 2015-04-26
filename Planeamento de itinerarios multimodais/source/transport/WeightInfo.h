#ifndef WEIGHT_INFO_H
#define WEIGHT_INFO_H

#include "Hour.h"
#include <ostream>

class WeightInfo{
public:
	WeightInfo(): time(0), cost(0), distance(0), switchs(0) {}
	double getWeight() const;
	double getCost() const;
	void setCost(double cost);
	static double getCostWeight();
	static void setCostWeight(double costWeight);
	double getDistance() const;
	void setDistance(double distance);
	static double getDistanceWeight();
	static void setDistanceWeight(double distanceWeight);
	double getSwitchs() const;
	void setSwitchs(double switchs);
	static double getSwitchWeight();
	static void setSwitchWeight(double switchWeight);
	double getTime() const;
	void setTime(double time);
	static double getTimeWeight();
	static void setTimeWeight(double timeWeight);
	WeightInfo operator+(const WeightInfo& w) const;
	friend std::ostream& operator<<(std::ostream& os, WeightInfo& w);

private:
	static double timeWeight;
	static double distanceWeight;
	static double switchWeight;
	static double costWeight;

	double time;
	double distance;
	double switchs;
	double cost;
};


#endif
