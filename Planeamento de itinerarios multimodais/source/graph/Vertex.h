#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"
#include "../transport/Coordinates.h"
#include <iostream>
#include <cfloat>
#include <cmath>

class Vertex{
public:
	/**
	 * @brief vertex constructor
	 * @param coords coordinates of vertex
	 */
	Vertex(const Coordinates &coords);

	/**
	 * @brief get the edges that exit this vertex
	 * @return adjacent vertices
	 */
	std::vector<Edge*> getAdj()const;

	/**
	 * @brief add vertex to list of adjacents
	 * @param v vertex to add
	 * @param weight weight of edge to create
	 */
	void addAdj(Vertex* v, double weight =0);

	/**
	 * @brief add edge to vertex
	 * @param edge edge to add
	 */
	void addEdge(Edge *edge);

	/**
	 * @brief get the coordinates of this vertex
	 * @return coordinate of vertex
	 */
	Coordinates getCoords() const;

	/**
	 * @brief get x position of vertex
	 * @return x postiton of vertex
	 */
	double getRenderX() const;

	/**
	 * @brief get y position of vertex
	 * @return y postiton of vertex
	 */
	double getRenderY() const;

	/**
	 * @brief get index of vertex, its position in vertexSet of its containing graph
	 * @return index of vertex
	 */
	unsigned int getIndex() const;

	/**
	 * @brief get x position of vertex
	 * @return x postiton of vertex
	 */
	virtual unsigned int getRenderX();

	/**
	 * @brief get x position of vertex
	 * @return x postiton of vertex
	 */
	virtual unsigned int getRenderY();

	/**
	 * @brief destructor for class
	 */
	virtual ~Vertex();

	/**
	 * @brief set index of vertex, its position in vertexSet of its containing graph
	 * @param new index in graph
	 */
	void setIndex(unsigned int index);

	/**
	 * @brief get the best value for edge weight obtained during the course of an algorithm
	 * @return best value for weight so far
	 */
	double getBestWeight() const;

	/**
	 * @brief set the best value for edge weight obtained during the course of an algorithm
	 * @param bestWeight best value for weight so far
	 */
	void setBestWeight(double bestWeight);

	/**
	 * @brief reset the best value for edge weight obtained during the course of an algorithm, positive infinity, vertex unreached
	 */
	void resetBestWeight();

	/**
	 * @brief get the last edge of the path that produced the lowest weight so far
	 * @return edge with this vertex as dst
	 */
	Edge* getParent() const;

	/**
	 * @brief set the last edge of the path that produced the lowest weight so far
	 * @return edge with this vertex as dst, to set as parent
	 */
	virtual void setParent( Edge* parent);

	/**
	 * @brief set the number of times the vertex has been processed to 0
	 */
	void resetProcessed();

	/**
	 * @brief get the number of times the vertex has been processed since the counter was reset
	 */
	int getProcessed() const;

	/**
	 * @brief increment the number of times the vertex has been processed since the counter was reset
	 */
	void incProcessed();

	/**
	 * @brief get the number of times the vertex has been visited since the counter was reset
	 */
	int getVisits() const;

	/**
	 * @brief reset the number of times the vertex has been visited
	 */
	void resetVisits();

	/**
	 * @brief increment the number of times the vertex has been visited
	 */
	void incVisits();

	/**
	 * @brief calculate and store heuristic value from this vertex to a destination vertex
	 * @param v goal vertex
	 * @return heuristic value
	 */
	virtual double calculateH(Vertex* v);

	/**
	 * @brief retrive stored heuristic value
	 * @return stored heuristic value
	 */
	double getStoredH() const;

	/**
	 * @brief retrive stored heuristic value
	 */
	void resetStoredH();
	/**
	 * @brief comparison struct for ordering of vertex pointers for use in A* algorithm
	 */
	struct AStarComp{
		/**
		 * @brief comparison operator
		 * @param v1 first vertex to compare
		 * @param v2 second vertex to compare
		 */
		bool operator()(Vertex* v1, Vertex* v2)const {
			double f1 = v1->getBestWeight() + v1->getStoredH();
			double f2 = v2->getBestWeight() + v2->getStoredH();
			if(f1 == f2)
				return v1->getStoredH() > v2->getStoredH();
			else
				return f1 > f2;
		}
	};
	/**
	 * @brief comparison struct for ordering of vertex pointers for use in Dijkstra's algorithm
	 */
	struct DijsComp{
		/**
		 * @brief comparison operator
		 * @param v1 first vertex to compare
		 * @param v2 second vertex to compare
		 */
		bool operator()(Vertex* v1, Vertex* v2) const{
			return v1->getBestWeight() > v2->getBestWeight();
		}
	};
	void removeEdge(int i);
protected:
	Coordinates coords;
private:
	unsigned int index;
	unsigned int x;
	unsigned int y;
	std::vector<Edge*> adj;
	double bestWeight;
	Edge* parent;
	int visits;
	int processed;
	double storedH;
};


#endif

