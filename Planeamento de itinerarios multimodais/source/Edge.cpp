#include "Edge.h"

double Edge::getWeight() const{
    	//return sqrt((src->getRenderX()-dst->getRenderX()) * (src->getRenderX()-dst->getRenderX()) + (src->getRenderY()-dst->getRenderY()) * (src->getRenderY()-dst->getRenderY()));
	return storedWeight;
};
