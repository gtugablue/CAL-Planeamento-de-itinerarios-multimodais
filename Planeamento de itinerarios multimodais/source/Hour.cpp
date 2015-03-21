/*
 * Hour.cpp
 *
 *  Created on: 21/03/2015
 *      Author: Gustavo
 */

#include "Hour.h"

bool Hour::operator<(const Hour &hour)
{
	if (hours < hour.hours)
		return true;
	if (hours > hour.hours)
		return false;
	if (minutes < hour.minutes)
		return true;
	return false;
}
