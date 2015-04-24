#include "GraphQueueFib.h"

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

