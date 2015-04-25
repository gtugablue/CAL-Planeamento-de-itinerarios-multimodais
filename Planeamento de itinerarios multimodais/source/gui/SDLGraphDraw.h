#ifndef SDLGRAPHDRAW_H
#define SDLGRAPHDRAW_H


using namespace std;

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../graph/Path.h"
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
	static double minlat;
	static double maxlat;
	static double minlong;
	static double maxlong;
public:
	static void setRes(unsigned int h, unsigned int v){
		SDLGraphDraw::h_res = h;
		SDLGraphDraw::v_res = v;
	}
	static int getDrawX(double longi){
		return (longi - minlong) * h_res/(maxlong-minlong);
	}
	static int getDrawY(double lat){
			return (lat - minlat) * v_res/(maxlat-minlat);
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

	static double getMaxlat() {
		return maxlat;
	}

	static void setMaxlat( double value) {
		maxlat = value;
	}

	static double getMaxlong()  {
		return maxlong;
	}

	static void setMaxlong( double value) {
		maxlong = value;
	}

	static double getMinlat()  {
		return minlat;
	}

	static void setMinlat( double value) {
		minlat = value;
	}

	static double getMinlong()  {
		return minlong;
	}

	static void setMinlong( double value) {
		minlong = value;
	}
	static void setValues(double minx, double miny, double maxx, double maxy){
		minlat = miny;
		maxlat = maxy;
		minlong= minx;
		maxlong = maxx;
	}
};


#endif
