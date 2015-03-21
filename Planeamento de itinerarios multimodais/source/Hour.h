/*
 * Hour.h
 *
 *  Created on: 21/03/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_HOUR_H_
#define SOURCE_HOUR_H_

class Hour {
public:
	unsigned hours;
	unsigned minutes;
	Hour(unsigned hours, unsigned minutes): hours(hours), minutes(minutes) { }
	bool operator<(const Hour &hour);
};

#endif /* SOURCE_HOUR_H_ */
