#ifndef SDLGRAPHDRAW_H
#define SDLGRAPHDRAW_H


using namespace std;

#include "Edge.h"
#include "Graph.h"
#include "Path.h"
#include "SDLRGB.h"
#include "Camera.h"
#include "Slider.h"

#include <SDL2/SDL.h>

class Graph;
class Edge;

class SDLGraphDraw{
private:
	static unsigned int h_res;
	static unsigned int v_res;

public:
	static void setRes(unsigned int h, unsigned int v){
		SDLGraphDraw::h_res = h;
		SDLGraphDraw::v_res = v;
	}
	static void drawEdge(SDL_Renderer *renderer, Edge* e, SDLRGB color);
	static void drawGraph(SDL_Renderer *renderer, Graph* e);
	static void drawPath(SDL_Renderer *renderer, Path* e);
	static void drawVertex(SDL_Renderer *renderer, Vertex* v, int size, SDLRGB color);

	static void drawEdge(SDL_Renderer *renderer, Camera* c, Edge* e, SDLRGB color);
	static void drawGraph(SDL_Renderer *renderer, Camera* c, Graph* e);
	static void drawPath(SDL_Renderer *renderer, Camera* c, Path* e, SDLRGB color);
	static void drawVertex(SDL_Renderer *renderer,Camera* c, Vertex* v, int size, SDLRGB color);
	static void drawSlider(SDL_Renderer *renderer, Slider* slider, SDLRGB color1, SDLRGB color2);

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
