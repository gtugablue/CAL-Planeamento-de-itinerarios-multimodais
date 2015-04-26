#ifndef GRAPH_QUEUE_LIST_H
#define GRAPH_QUEUE_LIST_H

#include "GraphQueue.h"
#include "../graph/Vertex.h"
#include <list>
#include <algorithm>

template<class Comp>
class GraphQueueList: public GraphQueue<Comp>{
public:
	GraphQueueList(int numVertices);
	void push(Vertex * v);
	Vertex* top() const;
	Vertex* pop();
	void increase(Vertex * v);
	void reset(int numVertices);
	int size();
private:
	list<Vertex *> vList;
};

template<class Comp>
GraphQueueList<Comp>::GraphQueueList(int numVertices){
}

template<class Comp>
void GraphQueueList<Comp>::push(Vertex * v){
	vList.push_back(v);
}
template<class Comp>
Vertex* GraphQueueList<Comp>::top() const{
	return *max_element(vList.begin(), vList.end(), Comp());
}
template<class Comp>
Vertex* GraphQueueList<Comp>::pop(){
	list<Vertex*>::iterator it = max_element(vList.begin(), vList.end(),Comp());
	Vertex* out = *it;
	vList.erase(it);
	return out;
}
template<class Comp>
void GraphQueueList<Comp>::increase(Vertex * v){

}

template <class Comp>
void GraphQueueList<Comp>::reset(int numVertices){
	vList.clear();
}
template <class Comp>
int GraphQueueList<Comp>::size(){
	return vList.size();
}

#endif
