/*
 * Hour.cpp
 *
 *  Created on: 21/03/2015
 *      Author: Gustavo
 */

#include "Hour.h"
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

const unsigned Hour::secondsPerMinute = 60;
const unsigned Hour::minutesPerHour = 60;
const unsigned Hour::hoursPerDay = 24;
const unsigned Hour::minutesPerDay = Hour::hoursPerDay * Hour::minutesPerHour;
const unsigned Hour::secondsPerDay = Hour::minutesPerDay * Hour::secondsPerMinute;
const unsigned Hour::secondsPerHour = Hour::minutesPerHour * Hour::secondsPerMinute;

Hour::Hour(const string &hour)
{
	char temp[3] = {hour[0], hour[1], '\0'};
	unsigned hours = strtol(temp, NULL, 10);
	temp[0] = hour[3];
	temp[1] = hour[4];
	unsigned minutes = strtol(temp, NULL, 10);
	seconds = hours * secondsPerHour + minutes * secondsPerMinute;
}

unsigned Hour::getHourstamp() const
{
	return seconds;
}

void Hour::setHourstamp(unsigned hourstamp)
{
	seconds = hourstamp % secondsPerDay;
}

Hour& Hour::operator+=(const Hour &hour)
{
	seconds += hour.seconds % secondsPerDay;
	return *this;
}

Hour Hour::operator+(const Hour &hour) const
{
	return Hour(*this) += hour;
}

Hour& Hour::operator-=(const Hour &hour)
{
	if (seconds < hour.seconds)
	{
		seconds = secondsPerDay - (hour.seconds - seconds);
	}
	else
	{
		seconds = seconds - hour.seconds;
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
	seconds /= quocient;
	return *this;
								}

Hour Hour::operator/(double quocient) const
{
	return Hour(*this) /= quocient;
}

bool Hour::operator<(const Hour &hour) const
{
	return seconds < hour.seconds;
}

bool Hour::operator>(const Hour &hour) const
{
	return seconds > hour.seconds;
}

Hour operator*(const Hour &hour, double factor)
{
	Hour hour2(hour);
	hour2.seconds = (unsigned)(hour2.seconds * factor) % hour2.secondsPerDay;
	return hour2;
}

Hour operator+(const Hour &hour, double x)
{
	Hour hour2(hour);
	hour2.seconds = (unsigned)(hour2.seconds + x) % hour2.secondsPerDay;
	return hour2;
}

ostream &operator<<(ostream &os, const Hour &hour)
{
	return os << setw(2) << setfill('0') << hour.seconds / Hour::secondsPerHour << ':' << setw(2) << setfill('0') << (hour.seconds / Hour::secondsPerMinute) % Hour::minutesPerHour;
}
