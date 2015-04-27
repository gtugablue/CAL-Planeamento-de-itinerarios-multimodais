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

/**
 * @brief A set of edges representing a path between two points
 */
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
		string prev_line = "";
		bool printTime = false;

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

				if(i == 0)
					os << "Walk to:" << endl;
				if(i != 0 && prev_line != ts->getRouteName())
				{
					if(i != 1)
					{
						Vertex * v2 = p.edges[i-1]->getSrc();
						TransportStop* ts2 = dynamic_cast<TransportStop*>(v2);
						if(ts2 != NULL)
						{
							os << "Switch from " << ts2->getName() << " to:" << endl;
							printTime = true;
						}
						else
							os << "Switch to:" << endl;
					}
					os << ts->getName() << " - Line " << ts->getRouteName() << " [" << ts->getArrivalTime() << "]";

					if(printTime || i == 1)
					{
						printTime = false;
						os << " (" << ts->calcWaitingTime(ts->getArrivalTime())/60 << " minutes of wait)";
					}

					os << endl;
				}
			}
			prev_line = ts->getRouteName();
		}

		if(p.edges.size() > 0)
		{
			v = p.edges[p.edges.size() - 1]->getDst();
			TransportStop* ts = dynamic_cast<TransportStop*>(v);
			if(ts != NULL)
			{
				if(p.edges.size() > 1)
				{
					Vertex * v2 = p.edges[p.edges.size() - 1]->getSrc();
					TransportStop* ts2 = dynamic_cast<TransportStop*>(v2);
					if(ts2 != NULL)
						os << "Leave at " << ts2->getName() << " and walk to:" << endl;
					else
						os << "Walk to:" << endl;
				}

				os << ts->getNameAndType() << " [" << ts->getArrivalTime() << "]" << endl;
			}
		}

		int temp = w.getSwitchs();
		temp -= 2;
		if(temp<0) temp = 0;
		w.setSwitchs(temp);

		os << endl << "==> Total path cost:" << endl;
		os << "Time: " << (((TransportStop*)p.edges[p.edges.size() - 1]->getDst())->getArrivalTime() - ((TransportStop*)p.edges[0]->getSrc())->getArrivalTime())/60 << " minutes" << endl;
		os << "Monetary cost: " << w.getCost() << " euros" << endl;
		os << "Distance: " << w.getDistance() / 1000 << "km" << endl;
		os << "Number of transport switches: " << w.getSwitchs() << endl << endl;

		return os;
	}
};



#endif
