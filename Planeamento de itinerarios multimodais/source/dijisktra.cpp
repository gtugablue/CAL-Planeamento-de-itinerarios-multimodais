#include "dijisktra.h"




/*Path* dijisktra(Graph* g, Vertex* ini, Vertex* f){
	vector<double> best(g->getVertexSet().size());
	vector<bool> completed(g->getVertexSet().size());
	vector<unsigned int> parent(g->getVertexSet().size());
	for(size_t i = 0; i < best.size(); i++){
		best[i] = DBL_MAX;
		completed[i] = false;
	}
	double costsofar = 0;
	double minnextcost=0;
	Path* out = new Path(0);
	Vertex* current = ini;
	Vertex* next = NULL;
	do{
		if(current == f)
			break;
		completed[current->getIndex()] = true;

		for(size_t i = 0; i < current->getAdj().size(); i++){
			if(completed[current->getAdj()[i]->getDst()->getIndex()])
				continue;
			double nextweight = costsofar + current->getAdj()[i]->getWeight();
			if(nextweight < best[current->getAdj()[i]->getDst()->getIndex()]){
				best[current->getAdj()[i]->getDst()->getIndex()] = nextweight;
				parent[current->getAdj()[i]->getDst()->getIndex()] = current->getIndex();
			}
		}
		minnextcost = DBL_MAX;
		for(size_t i = 0; i < best.size(); i++){
			if(!completed[i] && best[i] < minnextcost){
				minnextcost = best[i];
				next = g->getVertexSet()[i];
			}
		}
		costsofar = minnextcost;
		for(int i = 0; i < current->getAdj().size(); i++){
			if(current->getAdj()[i]->getDst() == next){
				out->addEdge(current->getAdj()[i]);
			}
		}
		current = next;
	}while(!dijisktradone(best, completed));
	cout << out->getEdges().size();
	return out;
}*/

bool dijisktradone(const vector<double>& best, const vector<bool>& completed){
	for(size_t i = 0; i < best.size(); i++){
		if(!(best[i] == DBL_MAX || completed[i]))
			return false;
	}
	return true;
}
Path* dijisktra(Graph* g, Vertex* ini, Vertex* f){
	vector<double> best(g->getVertexSet().size());
	vector<bool> completed(g->getVertexSet().size());
	vector<unsigned int> parent(g->getVertexSet().size());
	for(int i = 0; i < parent.size(); i++){
		parent[i] = -1;
	}
	for(size_t i = 0; i < best.size(); i++){
		best[i] = DBL_MAX;
		completed[i] = false;
	}

	cout << ini->getAdj().size()<< endl;
	double costsofar = 0;
	double minnextcost=0;
	Path* out = new Path(0);
	Vertex* current = ini;
	Vertex* next = NULL;
	int count = 0;
	do{
		//out->addVertex(current);
		completed[current->getIndex()] = true;
		if(current == f)
			break;

		for(size_t i = 0; i < current->getAdj().size(); i++){
			if(completed[current->getAdj()[i]->getDst()->getIndex()])
				continue;
			double nextweight = costsofar + current->getAdj()[i]->getWeight();
			if(nextweight < best[current->getAdj()[i]->getDst()->getIndex()]){
				best[current->getAdj()[i]->getDst()->getIndex()] = nextweight;
				parent[current->getAdj()[i]->getDst()->getIndex()] = current->getIndex();
			}
		}
		minnextcost = DBL_MAX;
		for(size_t i = 0; i < best.size(); i++){
			if(!completed[i] && best[i] < minnextcost){
				minnextcost = best[i];
				next = g->getVertexSet()[i];
			}
		}
		costsofar = minnextcost;
		//cout << current->getIndex() << "->" << next->getIndex() << endl;
		current = next;
		count++;
	}while(count < best.size());

	cout << endl;

	if(completed[f->getIndex()]){
		current = f;
		out->addVertex(current) ;
		cout << current->getIndex();
		while(parent[current->getIndex()] != -1){
			current = g->getVertexSet()[parent[current->getIndex()]];
			cout << "<- " << current->getIndex();
			out->addVertex(current);
		}
		return out;
	}
	else {
		delete out;
		return new Path(0);
	}
}
