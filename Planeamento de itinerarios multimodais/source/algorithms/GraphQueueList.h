#ifndef GRAPH_QUEUE_LIST_H
#define GRAPH_QUEUE_LIST_H

#include "GraphQueue.h"
#include "../graph/Vertex.h"
#include <list>
#include <algorithm>

template<class Comp>
class GraphQueueList: public GraphQueue<Comp>{
public:
	/**
	 * @brief queue constructor
	 * @param numVertices number of vertices of grah the structure will be used on
	 */
	GraphQueueList(int numVertices);

	/**
	 * @brief add vertex to the queue
	 * @param v vertex to add
	 */
	void push(Vertex * v);

	/**
	 * @brief get the highest priority vertex in queue
	 * @return highest priority vertex in queue
	 */
	Vertex* top()const;

	/**
	 * @brief remove highest priority vertex in queu
	 * @return highest priority vertex in queue
	 */
	Vertex* pop();

	/**
	 * @brief increase priority of vertex in queue
	 * @param v vertex to increase
	 */
	void increase(Vertex * v);

	/**
	 * @brief reset the queue
	 * @param numVertices number of vertices of grah the structure will be used on
	 */
	void reset(int numVertices);

	/**
	 * @brief get the size of the queue
	 * @return number of elements in queue
	 */
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
