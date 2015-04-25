/*
 * Bus.h
 *
 *  Created on: 25/04/2015
 *      Author: Gustavo
 */

#ifndef SOURCE_TRANSPORT_BUS_H_
#define SOURCE_TRANSPORT_BUS_H_

#include <stdlib.h>

class Bus { // Singleton
private:
	static Bus *instance;
	Bus() {}

	static const double speed = 2;
public:
	static Bus& getInstance()
	{
		if (!instance) instance = new Bus();
		return *instance;
	}

	double getSpeed() const { return speed; }
};

#endif /* SOURCE_TRANSPORT_BUS_H_ */
