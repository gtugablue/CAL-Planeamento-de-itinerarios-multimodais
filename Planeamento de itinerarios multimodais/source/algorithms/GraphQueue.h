#ifndef GRAPH_QUEUE_H
#define GRAPH_QUEUE_H

#include "../graph/Vertex.h"
template <class Comp>
class GraphQueue{
public:
	virtual void reset(int numVertices) = 0;
	virtual int size() = 0;
	virtual void push(Vertex * v) = 0;
	virtual Vertex* top() const = 0;
	virtual Vertex* pop() = 0;
	virtual void increase(Vertex * v) = 0;
};


#endif
