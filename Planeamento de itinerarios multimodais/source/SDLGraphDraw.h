#ifndef SDLGRAPHDRAW_H
#define SDLGRAPHDRAW_H


using namespace std;

#include "Edge.h"
#include "Graph.h"
#include "Path.h"
#include "SDLRGB.h"
#include <SDL2/SDL.h>

class Graph;
class Edge;

class SDLGRAPHDRAW{
private:
	static unsigned int h_res;
	static unsigned int v_res;


public:
	static void setRes(unsigned int h, unsigned int v){
		h_res = h;
		v_res = v;
	}
	static void drawEdge(SDL_Renderer *renderer, Edge* e, SDLRGB color);
	static void drawGraph(SDL_Renderer *renderer, Graph* e);
	static void drawPath(SDL_Renderer *renderer, Path* e);
	static void drawVertex(SDL_Renderer *renderer, Vertex* v, int size, SDLRGB color);

    static unsigned int getHRes()
    {
        return h_res;
    }

    static unsigned int getVRes()
    {
        return v_res;
    }
};


#endif
