#include "AStar.h"

Path* astar(Graph* g, Vertex* ini, Vertex* f){
	vector<Vertex*> vertices = g->getVertexSet();
	for(size_t i= 0; i < vertices.size(); i++){
		vertices[i]->resetProcessed();
		vertices[i]->resetVisits();
		vertices[i]->setParent(NULL);
		vertices[i]->resetBestWeight();
	}
	astar_heap vHeap;
	astar_handle handles[vertices.size()];
	ini->setBestWeight(0);
	ini->setParent(NULL);
	ini->incVisits();
	ini->calculateH(f);
	handles[ini->getIndex()] = vHeap.push(ini);
	Vertex* current;
	while(vHeap.size() != 0)
	{
		current = (Vertex*)vHeap.top();
		vHeap.pop();
		current->incProcessed();
		if(current == f)
			break;
		vector<Edge*> adjs  = current->getAdj();
		for(size_t i = 0; i < adjs.size(); i++)
		{
			if(!adjs[i]->getDst()->getProcessed())
			{
				double newWeight = current->getBestWeight() +adjs[i]->getWeight();
				if(newWeight < adjs[i]->getDst()->getBestWeight())
				{
					adjs[i]->getDst()->setBestWeight(newWeight);
					adjs[i]->getDst()->setParent(adjs[i]);
					if(adjs[i]->getDst()->getVisits())
					{
						vHeap.increase(handles[adjs[i]->getDst()->getIndex()]);
					}
					else
					{
						adjs[i]->getDst()->calculateH(f);
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
}
