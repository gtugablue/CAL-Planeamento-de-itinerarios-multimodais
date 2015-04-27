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
	unsigned seconds;
public:
	static const unsigned secondsPerMinute;
	static const unsigned minutesPerHour;
	static const unsigned hoursPerDay;
	static const unsigned minutesPerDay;
	static const unsigned secondsPerDay;
	static const unsigned secondsPerHour;
	Hour(): seconds(0) {}
	Hour(const std::string &hour);
	Hour(unsigned hours, unsigned minutes, unsigned seconds = 0): seconds(hours * secondsPerHour + minutes * minutesPerHour + seconds) { }
	Hour(double time);
	unsigned getHourstamp() const;
	void setHourstamp(unsigned hourstamp);
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
	bool operator>(const Hour &hour) const;
	friend Hour operator*(const Hour &hour, double factor);
	friend Hour operator+(const Hour &hour, double x);
	friend std::ostream &operator<<(std::ostream &os, const Hour &hour);
};

#endif /* SOURCE_HOUR_H_ */
