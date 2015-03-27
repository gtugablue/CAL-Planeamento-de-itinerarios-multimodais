/*
 * Hour.h
 *
 *  Created on: 21/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_HOUR_H_
#define SOURCE_HOUR_H_

#include <string>

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
	Hour(const std::string &hour);
	Hour(unsigned hours, unsigned minutes): hours(hours), minutes(minutes) { }
	Hour& operator+=(const Hour &hour);
	Hour operator+(const Hour &hour) const;
	Hour& operator-=(const Hour &hour);
	Hour operator-(const Hour &hour) const;
	Hour& operator*=(unsigned factor);
	Hour operator*(unsigned factor) const;
	Hour& operator/=(unsigned quocient);
	Hour operator/(unsigned quocient) const;
	bool operator<(const Hour &hour) const;
};

#endif /* SOURCE_HOUR_H_ */
