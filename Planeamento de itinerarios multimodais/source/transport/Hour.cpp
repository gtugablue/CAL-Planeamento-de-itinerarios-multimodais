/*
 * Hour.cpp
 *
 *  Created on: 21/03/2015
 *      Author: Gustavo
 */

#include "Hour.h"
#include <cstdlib>
#include <cmath>

using namespace std;

const unsigned Hour::secondsPerMinute = 60;
const unsigned Hour::minutesPerHour = 60;
const unsigned Hour::hoursPerDay = 24;
const unsigned Hour::minutesPerDay = Hour::hoursPerDay * Hour::minutesPerHour;
const unsigned Hour::secondsPerDay = Hour::minutesPerDay * Hour::secondsPerMinute;

Hour::Hour(const string &hour)
{
	char temp[3] = {hour[0], hour[1], '\0'};
	hours = strtol(temp, NULL, 10);
	temp[0] = hour[3];
	temp[1] = hour[4];
	minutes = strtol(temp, NULL, 10);
}

Hour::Hour(double time)
{
	time = fmod(time, secondsPerDay);
	setHourstamp(round(time));
}

unsigned Hour::getHourstamp() const
{
	return hours * minutesPerHour * secondsPerMinute + minutes;
}

void Hour::setHourstamp(unsigned hourstamp)
{
	hourstamp /= secondsPerMinute;
	hours = hourstamp / minutesPerHour;
	minutes = hourstamp % minutesPerHour;
}

Hour& Hour::operator+=(const Hour &hour)
						{
	setHourstamp((getHourstamp() + hour.getHourstamp()) % secondsPerDay);
	return *this;
						}

Hour Hour::operator+(const Hour &hour) const
{
	return Hour(*this) += hour;
}

Hour& Hour::operator-=(const Hour &hour)
						{
	if (getHourstamp() < hour.getHourstamp())
	{
		setHourstamp(secondsPerDay - (hour.getHourstamp() - getHourstamp()));
	}
	else
	{
		setHourstamp(getHourstamp() - hour.getHourstamp());
	}
	return *this;
						}

Hour Hour::operator-(const Hour &hour) const
{
	return Hour(*this) -= hour;
}

/*Hour& Hour::operator*=(const Hour &hour)
{
	setHourstamp((getHourstamp() * hour.getHourstamp()) % minutesPerDay);
	return *this;
}*/
/*Hour Hour::operator*(const Hour &hour) const
{
	return Hour(*this) *= hour;
}*/

/*Hour& Hour::operator*=(double factor)
{
	setHourstamp((unsigned)(getHourstamp() * factor) % minutesPerDay);
	return *this;
}*/

/*Hour Hour::operator*(double factor) const
{
	return Hour(*this) *= factor;
}*/

Hour& Hour::operator/=(double quocient)
						{
	setHourstamp(getHourstamp() / quocient);
	return *this;
						}

Hour Hour::operator/(double quocient) const
{
	return Hour(*this) /= quocient;
}

bool Hour::operator<(const Hour &hour) const
{
	if (hours < hour.hours)
		return true;
	if (hours > hour.hours)
		return false;
	if (minutes < hour.minutes)
		return true;
	return false;
}

bool Hour::operator>(const Hour &hour) const
{
	if (hours > hour.hours)
		return true;
	if (hours < hour.hours)
		return false;
	if (minutes > hour.minutes)
		return true;
	return false;
}

Hour operator*(const Hour &hour, double factor)
{
	Hour hour2(hour);
	hour2.setHourstamp((unsigned)(hour2.getHourstamp() * factor) % hour2.secondsPerDay);
	return hour2;
}

Hour operator+(const Hour &hour, double x)
{

	cout << "Debug: " << hour << "+" << x << "=";
	Hour hour2(hour);
	cout << (hour2.getHourstamp() + x) << endl;
	hour2.setHourstamp((unsigned)(hour2.getHourstamp() + x) % hour2.secondsPerDay);
	return hour2;
}

ostream &operator<<(ostream &os, const Hour &hour)
{
	return os << hour.hours << ':' << hour.minutes;
}
