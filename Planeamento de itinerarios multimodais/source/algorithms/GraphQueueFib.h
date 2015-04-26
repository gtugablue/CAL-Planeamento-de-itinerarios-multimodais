#ifndef GRAPH_QUEUE_FIB_H
#define GRAPH_QUEUE_FIB_H

#include <boost/heap/fibonacci_heap.hpp>
#include <vector>
#include "GraphQueue.h"
#include "../graph/Vertex.h"
#include "../transport/TransportStop.h"

template<class Comp>
class GraphQueueFib: public GraphQueue<Comp>{
	typedef typename boost::heap::fibonacci_heap<Vertex*,  boost::heap::compare<Comp> > fib_heap;
	typedef typename boost::heap::fibonacci_heap<Vertex*, boost::heap::compare<Comp> >::handle_type fib_handle;
public:
	/**
	 * @brief queue constructor
	 * @param numVertices number of vertices of grah the structure will be used on
	 */
	GraphQueueFib(int numVertices);

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
	fib_heap heap;
	std::vector<fib_handle> handles;
};

template <class Comp>
GraphQueueFib<Comp>::GraphQueueFib(int numVertices){
	handles.resize(numVertices);
}

template <class Comp>
void GraphQueueFib<Comp>::push(Vertex * v){
	handles[v->getIndex()] = heap.push(v);
}

template <class Comp>
Vertex* GraphQueueFib<Comp>::top()const{
	return heap.top();
}

template <class Comp>
Vertex* GraphQueueFib<Comp>::pop(){
	Vertex* v = heap.top();
	heap.pop();
	return v;
}

template <class Comp>
void GraphQueueFib<Comp>::increase(Vertex * v){
	cerr << "entered" << endl;
	cerr << "increase: " << v->getIndex()  << ", "  << v->getVisits() << ", " << v->getProcessed()<< handles.size() << endl;
	TransportStop* ts = dynamic_cast<TransportStop*>(v);
	if(ts == NULL)
		cerr << "oops";
	//cerr << "increase: " << v->getIndex() << "name-" << ((TransportStop*)v)->getName() << "- " << ", " << handles.size() << endl;
	cerr << "done printing" << endl;
	heap.increase(handles[v->getIndex()]);
	cerr << "out of increase" << endl;
}

template <class Comp>
void GraphQueueFib<Comp>::reset(int numVertices){
	heap.clear();
	handles.resize(numVertices);
}

template <class Comp>
int GraphQueueFib<Comp>::size(){
	return heap.size();
}

#endif
