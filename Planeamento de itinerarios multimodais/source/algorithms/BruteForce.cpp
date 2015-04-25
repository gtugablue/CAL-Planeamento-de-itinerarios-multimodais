#include "BruteForce.h"

using namespace std;

bool brute_force_aux(Graph* g, Vertex* ini, Vertex* f, Path* current, Path* min){
	if(current->getCost() > min->getCost())
		return false;
	if(ini == f){
		*min = *current;
		return true;
	}
	for(int i = 0; i < ini->getAdj().size(); i++){
		if(!ini->getAdj()[i]->getDst()->getProcessed()){
			ini->getAdj()[i]->getDst()->incProcessed();
			current->addEdgeEnd(ini->getAdj()[i]);
			double savedCost = current->getCost();
			current->setCost(savedCost + ini->getAdj()[i]->getWeight());
			brute_force_aux(g, ini->getAdj()[i]->getDst(),  f, current, min);
			current->setCost(savedCost);
			current->removeEdgeEnd();
			ini->getAdj()[i]->getDst()->resetProcessed();
		}
	}
	return min->getCost() < DBL_MAX;
}
Path* brute_force(Graph* g, Vertex* ini, Vertex* f){
	for(int i = 0; i < g->getVertexSet().size(); i++){
		g->getVertexSet()[i]->resetProcessed();
	}
	Path* min = new Path(DBL_MAX);
	Path* current = new Path(0);
	brute_force_aux(g, ini, f, current, min);
	delete current;
	return min;
}


