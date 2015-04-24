#include "GraphQueueList.h"

template<class Comp>
GraphQueueList<Comp>::GraphQueueList(int numVertices){
	vList.resize(numVertices);
}

template<class Comp>
void GraphQueueList<Comp>::push(Vertex * v){
	vList.push_back(v);
}
template<class Comp>
Vertex* GraphQueueList<Comp>::top() const{
	list<Vertex*>::const_iterator it = vList.begin();
	list<Vertex*>::const_iterator ite = vList.end();
	for(list<Vertex*>::const_iterator it2 = ++it; it2 != ite; ++it2){
		if(Comp(*it , *it2))
			it = it2;
	}
	return *it;
}
template<class Comp>
Vertex* GraphQueueList<Comp>::pop(){
	list<Vertex*>::iterator it = vList.begin();
	list<Vertex*>::iterator ite = vList.end();
	for(list<Vertex*>::iterator it2 = ++it; it2 != ite; ++it2){
		if(Comp(*it , *it2))
			it = it2;
	}
	Vertex* out = *it;
	vList.erase(it);
	return out;
}
template<class Comp>
void GraphQueueList<Comp>::increase(Vertex * v){

}

template<class Comp>
GraphQueueList<Comp>::~GraphQueueList(){

}

template <class Comp>
void GraphQueueList<Comp>::reset(int numVertices){
	vList.empty();
}
template <class Comp>
int GraphQueueList<Comp>::size(){
	return vList.size();
}
