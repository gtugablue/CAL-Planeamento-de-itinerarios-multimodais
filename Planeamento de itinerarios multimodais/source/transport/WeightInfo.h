#ifndef WEIGHT_INFO_H
#define WEIGHT_INFO_H

#include "Hour.h"
#include <ostream>

class WeightInfo{
public:

	/**
	 * @brief constructor
	 */
	WeightInfo(): time(0), cost(0), distance(0), switchs(0) {}

	/**
	 * @brief get the weight value
	 * @return weight value
	 */
	double getWeight() const;

	/**
	 * @brief get the monetary cost
	 * @return monetary cost
	 */
	double getCost() const;

	/**
	 * @brief set the monetary cost
	 * @param cost new monetary cost
	 */
	void setCost(double cost);

	/**
	 * @brief get weight given to a unit of monetary cost
	 * @return weight of monetary cost
	 */
	static double getCostWeight();

	/**
	 * @brief set weight given to a unit of monetary cost
	 * @param costWeight new weight of monetary cost
	 */
	static void setCostWeight(double costWeight);

	/**
	 * @brief get the distance
	 * @return distance
	 */
	double getDistance() const;

	/**
	 * @brief set the distance
	 * @param distance new distance
	 */
	void setDistance(double distance);

	/**
	 * @brief get weight given to a unit of distance
	 * @return weight of distance
	 */
	static double getDistanceWeight();

	/**
	 * @brief set weight given to a unit of distance
	 * @param distanceWeight new weight of distance
	 */
	static void setDistanceWeight(double distanceWeight);

	/**
	 * @brief get the number of switchs made
	 * @return number of switchs
	 */
	double getSwitchs() const;

	/**
	 * @brief set the number of switchs made
	 * @param switchs new number of switchs
	 */
	void setSwitchs(double switchs);

	/**
	 * @brief get weight given to a switch
	 * @return weight of switch
	 */
	static double getSwitchWeight();

	/**
	 * @brief set weight given to a switch
	 * @param switchWeight new weight of switch
	 */
	static void setSwitchWeight(double switchWeight);

	/**
	 * @brief get the amount of time
	 * @return amount of time
	 */
	double getTime() const;

	/**
	 * @brief set the amount of time
	 * @param time new amount of time
	 */
	void setTime(double time);

	/**
	 * @brief get weight given to a unit of time
	 * @return weight of time
	 */
	static double getTimeWeight();

	/**
	 * @brief set weight given to a unit of time
	 * @param timeWeight new weight of time
	 */
	static void setTimeWeight(double timeWeight);

	/**
	 * @brief add two WeightInfos by adding their components
	 * @param w other weightinfo object to add to
	 * @return new WeightInfo, result of addition
	 */
	WeightInfo operator+(const WeightInfo& w) const;

	/**
	 * @brief write weightInfo to output stream
	 * @param os output stream to write
	 * @param w used outputstream
	 */
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
