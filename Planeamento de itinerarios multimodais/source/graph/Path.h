#ifndef PATH_H
#define PATH_H

#include "Edge.h"
#include "Vertex.h"
#include "../transport/TransportStop.h"
#include <vector>
#include <string>
#include "../transport/WeightInfo.h"

using namespace std;

class Edge;
class Vertex;

class Path{
	vector<Edge*> edges;
	double cost;
public:
	/**
	 * @brief constructor for path
	 * @param cost initial cost of path
	 */
	Path(double cost) {
		this->cost = cost;
	}

	/**
	 * @brief get edges that form this path
	 * @return edges of path
	 */
	vector<Edge*> getEdges() const{
		return edges;
	}

	/**
	 * @brief add edge to end of path
	 * @param e new edge to add
	 */
	void addEdgeEnd(Edge* e){
		edges.push_back(e);
	}

	/**
	 * @brief add edge to beginning of path
	 * @param e new edge to add
	 */
	void addEdgeBeginning(Edge* e){
		edges.insert(edges.begin(), e);
	}

	/**
	 * @brief equalitycomparison for paths
	 * @param p2 path to check for equality
	 * @return true if paths are equal
	 */
	bool operator==(const Path p2) const{
		if(edges.size() != p2.edges.size())
			return false;

		for(int i = 0; i < edges.size(); i++)
		{
			if(edges[i] != p2.edges[i])
				return false;
		}

		return true;
	}

	/**
	 * @brief remove the last edge from the path
	 */
	void removeEdgeEnd(){
		edges.pop_back();
	}

	/**
	 * @brief get the total weight of the path, assuming the it was correctly set
	 * @return total cost of path
	 */
	double getCost() const {
		return cost;
	}

	/**
	 * @brief set the total weight of the path
	 * @param cost new cost of path
	 */
	void setCost(double cost) {
		this->cost = cost;
	}

	/**
	 * @brief set this path to be equal to another
	 * @param p path
	 * @return this path
	 */
	Path& operator=(const Path& p){
		edges = p.edges;
		cost = p.cost;
		return *this;
	}

	/**
	 * @brief write path to outputstream
	 * @param os outputstream
	 * @param p path to write
	 * @return used outputstream
	 */
	friend ostream& operator<<(ostream& os, Path& p){

		WeightInfo w;

		size_t i;
		Vertex* v;
		for(i = 0; i < p.edges.size(); i++)
		{
			v = p.edges[i]->getSrc();

			TransportStop* ts = dynamic_cast<TransportStop*>(v);
			if(ts != NULL && i == 0)
				os << ts->getNameAndType() << " [" << ts->getArrivalTime() << "]" << endl;

			TransportEdge* te = dynamic_cast<TransportEdge*>(p.edges[i]);
			if(te != NULL)
			{
				w = w + te->getWeightInfo();
				if(te->getWeightInfo().getSwitchs() > 0)
				{
					if(p.edges.size() == 1)
						os << "=> Walk to:" << endl;
					else if(i == 0)
						os << "=> Enter transport:" << endl;
					else if(i == p.edges.size() - 1)
						os << "=> Walk to:" << endl;
					else
						os << "=> Switch to transport:" << endl;

					if(i != 0)
					{
						cerr << "0" << endl;
						os << "0" << endl;
						os << ts->getName() << endl;
						cerr << "1" << endl;
						os << "1" << endl;
						os << ts->getNameAndType();
						cerr << "2" << endl;
						os << "2" << endl;
						os << " [" << ts->getArrivalTime() << "]" << endl;
						cerr << "3" << endl;
						os << "3" << endl;
					}


						/*os << "==> Enter transport:" << endl;
					else if (i < p.edges.size() - 1)
						os << "==> Switch to transport:" << endl;
					else
						os << "==> Exit to:" << endl;*/
				}
			}
		}

		if(p.edges.size() > 0)
		{
			v = p.edges[p.edges.size() - 1]->getDst();
			TransportStop* ts = dynamic_cast<TransportStop*>(v);
			if(ts != NULL)
			{
				os << ts->getNameAndType() << " [" << ts->getArrivalTime() << "]" << endl;
			}
		}

		os << endl << "==> Total path cost:" << endl << w << endl;

		return os;
	}
};



#endif
