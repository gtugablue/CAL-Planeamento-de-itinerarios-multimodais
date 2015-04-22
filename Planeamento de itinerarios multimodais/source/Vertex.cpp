#include "Vertex.h"

Vertex::Vertex(const Coordinates &coords):
x(coords.getLatitude()),
y(coords.getLongitude()),
coords(coords),
bestWeight(DBL_MAX),
parent(NULL),
visits(0),
processed(0),
index(-1),
storedH(DBL_MAX)
{}

std::vector<Edge*> Vertex::getAdj()const{
	return adj;
};

void Vertex::addAdj(Vertex* v, double weight){
	for(size_t i = 0; i < adj.size(); i++){
		if(adj[i]->getDst() == v)
			return;
	}
	Edge * e = new Edge(this, v, weight);
	adj.push_back(e);
}

void Vertex::addEdge(Edge *edge)
{
	adj.push_back(edge);
}

Coordinates Vertex::getCoords() const {
	return coords;
}

double Vertex::getRenderX() const {
	return coords.getLongitude();
}

double Vertex::getRenderY() const {
	return coords.getLatitude();
}

unsigned int Vertex::getIndex() const {
	return index;
}

unsigned int Vertex::getRenderX() {
	return x;
}

unsigned int Vertex::getRenderY() {
	return y;
}
Vertex::~Vertex()
{	}

void Vertex::setIndex(unsigned int index){
	this->index = index;
}

double Vertex::getBestWeight() const {
	return bestWeight;
}

void Vertex::setBestWeight(double bestWeight) {
	this->bestWeight = bestWeight;
}

void Vertex::resetBestWeight(){
	setBestWeight(DBL_MAX);
}

Edge* Vertex::getParent() const {
	return parent;
}

void Vertex::setParent( Edge* parent) {
	this->parent = parent;
}

void Vertex::resetProcessed(){
	processed = 0;
}

int Vertex::getProcessed() const {
	return processed;
}

void Vertex::incProcessed() {
	processed++;
}

int Vertex::getVisits() const {
	return visits;
}

void Vertex::resetVisits(){
	visits = 0;
}

void Vertex::incVisits(){
	visits++;
}

double Vertex::calculateH(Vertex* v){
	if(storedH == -1)
		storedH = sqrt((x - v->x) *(x - v->x)+(y - v->y)*(y - v->y) );
	return storedH;
}

double Vertex::getStoredH() const {
	return storedH;
}

void Vertex::resetStoredH(){
	storedH = -1;
}

bool  Vertex::AStarComp::operator()(const Vertex* v1, const Vertex* v2)const {
	double f1 = v1->getBestWeight() + v1->getStoredH();
	double f2 = v2->getBestWeight() + v2->getStoredH();
	if(f1 == f2)
		return v1->getStoredH() > v2->getStoredH();
	else
		return f1>f2;
}
bool Vertex::DijsComp::operator()(const Vertex* v1, const Vertex* v2)const {
	return v1->getBestWeight() > v2->getBestWeight();
}


