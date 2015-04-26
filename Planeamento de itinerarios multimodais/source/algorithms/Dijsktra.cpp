#include "Dijsktra.h"

using namespace std;

/*Path* dijsktra(Graph* g, Vertex* ini, Vertex* f){
	vector<Vertex*> vertices = g->getVertexSet();
	for(int i= 0; i < vertices.size(); i++){
		vertices[i]->resetProcessed();
		vertices[i]->resetVisits();
		vertices[i]->setParent(NULL);
		vertices[i]->resetBestWeight();
	}
	dij_heap vHeap;
	dij_handle handles[vertices.size()];
	ini->setBestWeight(0);
	ini->setParent(NULL);
	ini->incVisits();
	handles[ini->getIndex()] = vHeap.push(ini);
	Vertex* current;
	while(vHeap.size() != 0){
		current = (Vertex*)vHeap.top();
		vHeap.pop();
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
						vHeap.increase(handles[adjs[i]->getDst()->getIndex()]);
					}else{
						handles[adjs[i]->getDst()->getIndex()] = vHeap.push(adjs[i]->getDst());
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
}*/

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
	if(reachable(0, ini, f))
		cerr << "Reachable" << endl;
	else cerr << "Not Reachable" << endl;
	for(int i= 0; i < vertices.size(); i++){
		for(int j= 0; j < vertices[i]->getAdj().size(); j++){
			if(vertices[i]->getAdj()[j]->getDst() == f)
			cerr << "found -> " << vertices[i]->getIndex() << "  " <<endl;
		}
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
		cerr << "current node: " << current->getIndex() << ", best weight: " << current->getBestWeight() << endl;
		cerr << "visiting: " << endl;
		for(int i = 0; i < adjs.size(); i++){
			cerr << "node: " << adjs[i]->getDst()->getIndex() << ", best weight: " << adjs[i]->getDst()->getBestWeight();
			if(!adjs[i]->getDst()->getProcessed()){
				double newWeight = current->getBestWeight() +adjs[i]->getWeight();
				cerr << ", newWeight: " << newWeight << endl;
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
		cerr <<endl<< endl;
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
