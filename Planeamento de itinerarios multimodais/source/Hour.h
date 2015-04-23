/*
 * Hour.h
 *
 *  Created on: 21/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_HOUR_H_
#define SOURCE_HOUR_H_

#include <string>
#include <iostream>

class Hour {
private:
	static unsigned minutesPerHour;
	static unsigned hoursPerDay;
	static unsigned minutesPerDay;
	unsigned getHourstamp() const;
	void setHourstamp(unsigned hourstamp);
public:
	unsigned hours;
	unsigned minutes;
	Hour(): hours(0), minutes(0) {}
	Hour(const std::string &hour);
	Hour(unsigned hours, unsigned minutes): hours(hours), minutes(minutes) { }
	Hour& operator+=(const Hour &hour);
	Hour operator+(const Hour &hour) const;
	Hour& operator-=(const Hour &hour);
	Hour operator-(const Hour &hour) const;
	//Hour& operator*=(const Hour &hour);
	//Hour operator*(const Hour &hour) const;
	//Hour& operator*=(double factor);
	//Hour operator*(double factor) const;
	Hour& operator/=(double quocient);
	Hour operator/(double quocient) const;
	bool operator<(const Hour &hour) const;
	friend Hour operator*(const Hour &hour, double factor);
	friend Hour operator+(const Hour &hour, double x);
	friend std::ostream &operator<<(std::ostream &os, const Hour &hour);
};

#endif /* SOURCE_HOUR_H_ */
