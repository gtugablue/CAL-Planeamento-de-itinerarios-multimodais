#ifndef GRAPH_QUEUE_LIST_H
#define GRAPH_QUEUE_LIST_H

#include "GraphQueue.h"
#include "Vertex.h"
#include <list>

template<class Comp>
class GraphQueueList: public GraphQueue<Comp>{
public:
	GraphQueueList(int numVertices);
	void push(Vertex * v);
	Vertex* top() const;
	Vertex* pop();
	void increase(Vertex * v);
	virtual ~GraphQueueList();
	void reset(int numVertices);
	int size();
private:
	list<Vertex *> vList;
};


#endif
