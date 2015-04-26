#ifndef GRAPH_QUEUE_H
#define GRAPH_QUEUE_H

#include "../graph/Vertex.h"


/**
 * @brief generic inteface to be used in algorithms, allows the underlying data structure to switched dynamically
 */
template <class Comp>
class GraphQueue{
public:

	/**
	 * @brief reset the queue
	 * @param numVertices number of vertices of grah the structure will be used on
	 */
	virtual void reset(int numVertices) = 0;

	/**
	 * @brief get the size of the queue
	 * @return number of elements in queue
	 */
	virtual int size() = 0;

	/**
	 * @brief add vertex to the queue
	 * @param v vertex to add
	 */
	virtual void push(Vertex * v) = 0;

	/**
	 * @brief get the highest priority vertex in queue
	 * @return highest priority vertex in queue
	 */
	virtual Vertex* top() const = 0;

	/**
	 * @brief remove highest priority vertex in queu
	 * @return highest priority vertex in queue
	 */
	virtual Vertex* pop() = 0;

	/**
	 * @brief increase priority of vertex in queue
	 * @param v vertex to increase
	 */
	virtual void increase(Vertex * v) = 0;
};


#endif
