#ifndef GRAPH_QUEUE_FIB_H
#define GRAPH_QUEUE_FIB_H

#include <boost/heap/fibonacci_heap.hpp>
#include <vector>
#include "GraphQueue.h"
#include "Vertex.h"

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


#endif
