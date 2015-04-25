#ifndef WEIGHT_INFO_H
#define WEIGHT_INFO_H

#include "Hour.h"

class WeightInfo{
public:
	double getWeight(Hour currentHour) const;
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
