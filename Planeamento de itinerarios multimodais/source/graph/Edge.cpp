#include "Edge.h"

#include <iostream>

using namespace std;

Edge::Edge(Vertex* src, Vertex* dst, double storedWeight){
	this->src = src;
	this->dst = dst;
	this->storedWeight = storedWeight;
}

double Edge::getWeight()
{
	cout << "Calling Edge's getWeight()" << endl;
	return storedWeight;
}

void Edge::setStoredWeight(double storedWeight){
	this->storedWeight = storedWeight;
}

Vertex* Edge::getDst() const{
	return dst;
}

void Edge::setDst(Vertex* dst){
	this->dst = dst;
}

Vertex* Edge::getSrc() const{
	return src;
}

void Edge::setSrc(Vertex* src){
	this->src = src;
}

void Edge::storeWeight(){
	storedWeight = getWeight();
}

double Edge::getStoredWeight() const{
	return storedWeight;
}

SDLRGB Edge::getColor(){
	return SDLRGB(0, 0xFF, 0);
}
Edge::~Edge() {

}
