/*
 * Metro.h
 *
 *  Created on: 25/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_TRANSPORT_METRO_H_
#define SOURCE_TRANSPORT_METRO_H_

#include <stdlib.h>

class Metro { // Singleton
private:
	static Metro *instance;
	Metro() {}

	static const double speed = 15;
public:
	static Metro& getInstance()
	{
		if (!instance) instance = new Metro();
		return *instance;
	}

	double getSpeed() const { return speed; }
};

#endif /* SOURCE_TRANSPORT_METRO_H_ */
