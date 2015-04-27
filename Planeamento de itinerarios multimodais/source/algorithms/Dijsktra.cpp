#include "Dijsktra.h"

using namespace std;


bool reachable(int num, Vertex* ini, Vertex* f){
	cerr << num << endl;
	if(ini == f)
		return true;
	for(int i = 0; i < ini->getAdj().size(); i++){
		return reachable(num+1, ini->getAdj()[i]->getDst(), f);
	}
	return false;
}

Path* dijsktra(Graph* g, Vertex* ini, Vertex* f, GraphQueue<Vertex::DijsComp>* queue){

	vector<Vertex*> vertices = g->getVertexSet();
	queue->reset(vertices.size());

	for(int i= 0; i < vertices.size(); i++){
		vertices[i]->resetProcessed();
		vertices[i]->resetVisits();
		vertices[i]->setParent(NULL);
		vertices[i]->resetBestWeight();
	}
	ini->setBestWeight(0);
	ini->setParent(NULL);
	ini->incVisits();
	queue->push(ini);
	Vertex* current;
	while(queue->size() != 0){
		current = queue->pop();
		current->incProcessed();
		if(current == f)
			break;
		vector<Edge*> adjs  = current->getAdj();
		for(int i = 0; i < adjs.size(); i++){
			if(!adjs[i]->getDst()->getProcessed()){
				double newWeight = current->getBestWeight() +adjs[i]->getWeight();
				if(newWeight < adjs[i]->getDst()->getBestWeight()){
					adjs[i]->getDst()->setBestWeight(newWeight);
					adjs[i]->getDst()->setParent(adjs[i]);
					if(adjs[i]->getDst()->getVisits())
					{
						queue->increase(adjs[i]->getDst());
					}else{
						queue->push(adjs[i]->getDst());
					}
				}
			}
			adjs[i]->getDst()->incVisits();
		}
	}

	Path *p = new Path(f->getBestWeight());
	if(f != current) return p;
	while(current != ini)
	{
		p->addEdgeBeginning(current->getParent());
		current = current->getParent()->getSrc();
	}
	return p;
}

Path* dijsktra_fib(Graph* g, Vertex* ini, Vertex* f){
	GraphQueue<Vertex::DijsComp>* queue = new GraphQueueFib<Vertex::DijsComp>(g->getVertexSet().size());
	Path* p = dijsktra(g, ini, f, queue);
	delete queue;
	return p;
}
Path* dijsktra_list(Graph* g, Vertex* ini, Vertex* f){
	GraphQueue<Vertex::DijsComp>* queue = new GraphQueueList<Vertex::DijsComp>(g->getVertexSet().size());
	Path* p = dijsktra(g, ini, f, queue);
	delete queue;
	return p;
}
