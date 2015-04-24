#ifndef GRAPH_QUEUE_FIB_H
#define GRAPH_QUEUE_FIB_H

#include <boost/heap/fibonacci_heap.hpp>
#include <vector>
#include "GraphQueue.h"
#include "../graph/Vertex.h"

template<class Comp>
class GraphQueueFib: public GraphQueue<Comp>{
	typedef typename boost::heap::fibonacci_heap<Vertex*,  boost::heap::compare<Comp> > fib_heap;
	typedef typename boost::heap::fibonacci_heap<Vertex*, boost::heap::compare<Comp> >::handle_type fib_handle;
public:
	GraphQueueFib(int numVertices);
	void push(Vertex * v);
	Vertex* top()const;
	Vertex* pop();
	void increase(Vertex * v);
	void reset(int numVertices);
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
	heap.increase(handles[v->getIndex()]);
}

template <class Comp>
void GraphQueueFib<Comp>::reset(int numVertices){
	heap.empty();
	handles.resize(numVertices);
}

template <class Comp>
int GraphQueueFib<Comp>::size(){
	return heap.size();
}

#endif
