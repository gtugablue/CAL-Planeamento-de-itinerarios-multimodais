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

Path* dijsktra(Graph* g, Vertex* ini, Vertex* f, GraphQueue<Vertex::DijsComp>* queue){

	vector<Vertex*> vertices = g->getVertexSet();
	queue->reset(vertices.size());
	for(int i= 0; i < vertices.size(); i++){
		cerr << vertices[i]->getIndex()  << " " << endl;
		vertices[i]->resetProcessed();
		vertices[i]->resetVisits();
		vertices[i]->setParent(NULL);
		vertices[i]->resetBestWeight();
	}
	cerr<<endl;
	ini->setBestWeight(0);
	ini->setParent(NULL);
	ini->incVisits();
	queue->push(ini);
	Vertex* current;
	while(queue->size() != 0){
		cerr << "queue size:" << queue->size() << endl;
		current = queue->pop();
		cerr << current;
		cerr << "indexcurrent " << current->getIndex() << endl;
		cerr << "update1" << endl;
		current->incProcessed();
		if(current == f)
			break;
		vector<Edge*> adjs  = current->getAdj();
		cerr << "update2" << endl;
		for(int i = 0; i < adjs.size(); i++){
			cerr << "update3" << endl;
			if(!adjs[i]->getDst()->getProcessed()){
				cerr << "index " << adjs[i]->getDst()->getIndex() << endl;
				cerr << "update4" << endl;
				double newWeight = current->getBestWeight() +adjs[i]->getWeight();
				cerr << "update5" << endl;
				if(newWeight < adjs[i]->getDst()->getBestWeight()){
					cerr << "update6" << endl;
					adjs[i]->getDst()->setBestWeight(newWeight);
					cerr << "update7" << endl;
					adjs[i]->getDst()->setParent(adjs[i]);
					cerr << "update8" << endl;
					if(adjs[i]->getDst()->getVisits())
					{
						cerr << "update9" << endl;
						queue->increase(adjs[i]->getDst());
						cerr << "update10" << endl;
					}else{
						cerr << "update11" << endl;
						queue->push(adjs[i]->getDst());
						cerr << "update12" << endl;
					}
					cerr << "update1" << endl;
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
