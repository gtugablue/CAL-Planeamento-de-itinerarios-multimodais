/*#include "Map.h"
#include "include/SDL2/SDL.h"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

double resize(double x, double minX, double maxX, double minScreen, double maxScreen)
{
	return ((x - minX) / (maxX - minX)) * (maxScreen - minScreen) + minScreen;
}

int main(int argc, char *argv[])
{
	Map::Loader l;
	Map map;
	try
	{
		map = l.load();
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Window *win = SDL_CreateWindow("Autocarros STCP", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		SDL_Renderer *ren = SDL_CreateRenderer(win, (int)-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		// Draw background map
		SDL_Surface* background = SDL_LoadBMP("data/map.bmp");
		SDL_Texture* background_text = SDL_CreateTextureFromSurface(ren, background);
		SDL_RenderCopy(ren, background_text, NULL, NULL);

		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0xFF );

		// Position and scale map in window
		double minLat = 999, minLong = 999, maxLat = -999, maxLong = -999;
		for (size_t i = 0; i < map.getBusRoutes().size(); ++i)
		{
			BusRoute busRoute = map.getBusRoutes()[i];
			const vector<BusEdge> &BusEdges = busRoute.getBusEdges();
			for (size_t j = 0; j < BusEdges.size(); ++j)
			{
				for (size_t k = 0; k < BusEdges[j].getLine().size(); ++k)
				{
					if (minLat > BusEdges[j].getLine()[k].getLatitude())
						minLat = BusEdges[j].getLine()[k].getLatitude();
					if (minLong > BusEdges[j].getLine()[k].getLongitude())
						minLong = BusEdges[j].getLine()[k].getLongitude();
					if (maxLat < BusEdges[j].getLine()[k].getLatitude())
						maxLat = BusEdges[j].getLine()[k].getLatitude();
					if (maxLong < BusEdges[j].getLine()[k].getLongitude())
						maxLong = BusEdges[j].getLine()[k].getLongitude();
				}
			}
		}

		// Draw Bus Routes
		for (size_t i = 0; i < map.getBusRoutes().size(); ++i)
		{
			BusRoute busRoute = map.getBusRoutes()[i];
			const vector<BusEdge> &BusEdges = busRoute.getBusEdges();
			for (size_t j = 0; j < BusEdges.size(); ++j)
			{
				for (size_t k = 1; k < BusEdges[j].getLine().size(); ++k)
				{
					Coordinates coord = BusEdges[j].getLine()[k];
					Coordinates coord2 = BusEdges[j].getLine()[k - 1];
					SDL_RenderDrawLine(ren, resize(coord.getLongitude(), minLong, maxLong, 0, WIDTH),
							HEIGHT - resize(coord.getLatitude(), minLat, maxLat, 0, HEIGHT),
							resize(coord2.getLongitude(), minLong, maxLong, 0, WIDTH),
							HEIGHT - resize(coord2.getLatitude(), minLat, maxLat, 0, HEIGHT));
				}
			}
		}
		// Draw Bus Stops
		SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0xFF);
		for (size_t j = 0; j < map.getBusStops().size(); ++j)
		{
			Coordinates coords = map.getBusStops()[j]->getCoords();
			SDL_RenderDrawPoint(ren, resize(coords.getLongitude(), minLong, maxLong, 0, WIDTH),
					HEIGHT - resize(coords.getLatitude(), minLat, maxLat, 0, HEIGHT));
		}

		SDL_Event Events;    //The SDL event that we will poll to get events.
		SDL_RenderPresent(ren);
		while (true)
		{
			SDL_PollEvent(&Events);
			if( Events.type == SDL_QUIT )
			{
				//Quit the program
				break;
			}
		}

		SDL_Quit();
		return 0;
	}
	catch (std::fstream::failure &e)
	{
		cout << "derpou" << endl;
		std::cerr << e.what();
		return 1;
	}
}*/
/*
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "GraphGen.h"
#include "Graph.h"
#include "dijsktra.h"
#include <ctime>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static SDL_Window* window = NULL;

static SDL_Renderer* renderer = NULL;

bool init(){
	if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer))
		return false;
	SDLGraphDraw::setRes(SCREEN_WIDTH,SCREEN_HEIGHT);
	srand(time(NULL));
	return true;
}

void close(){
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow(window);
	SDL_Quit();
	renderer = NULL;
	window = NULL;
}

int main(int argc, char* argv[]) {
	if(! init() ){
		std::cout << "Failed to initialize!" << endl;
		exit(1);
	}
	Graph* g1 = GraphGen::randGraph(10,17,50, 750, 50, 550);
	Path* p = dijsktra(g1, g1->getVertexSet()[0], g1->getVertexSet()[1]);
	SDL_Event e;
	bool moving = false;
	SDL_RenderDrawPoint(renderer,50, 50);
	Camera* c = new Camera(0,0,SDLGraphDraw::getHRes(), SDLGraphDraw::getVRes());
	while( SDL_WaitEvent(&e) )
	{
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
			break;
		else if(e.type  ==  SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
			std::cout << "left pressed"<<endl;
			delete g1;
			delete p;
			g1 = GraphGen::randGraph(10,17,50, 750, 50, 550);
			p = dijsktra(g1, g1->getVertexSet()[0], g1->getVertexSet()[1]);
		}
		else if(e.type  ==  SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT){
			moving = true;
			continue;
		}
		else if(e.type  ==  SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT){
			moving = false;
			continue;
		}
		else if(e.type  ==  SDL_MOUSEMOTION && moving){
			cout << "moving " << e.motion.xrel << ", " <<e.motion.yrel<< endl;
			//c->moveRel(-c->getZoomScaleX(SDLGraphDraw::getHRes()) * e.motion.xrel, - c->getZoomScaleY(SDLGraphDraw::getVRes()) * e.motion.yrel);
			c->moveRelScaled(-e.motion.xrel, -e.motion.yrel, SDLGraphDraw::getHRes(), SDLGraphDraw::getVRes());
		}
		else if(e.type  ==  SDL_MOUSEWHEEL ){
			if( e.wheel.y > 0){
				c->mulScale(.75,.75);
			}
			else if( e.wheel.y < 0){
				c->mulScale(1.25,1.25);
			}
			std::cout << "mouse wheel "<< e.wheel.y <<endl;
		}
		else continue;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(renderer );
		SDLGraphDraw::drawGraph(renderer,c, g1);
		SDLGraphDraw::drawPath(renderer, c, p);
		SDL_RenderPresent(renderer);
	}

	close();

	return 0;
}
*/
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "GraphGen.h"
#include "Graph.h"
#include "dijsktra.h"
#include <ctime>
#include "Camera.h"
#include "SDLGraphDraw.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static SDL_Window* window = NULL;

static SDL_Renderer* renderer = NULL;

bool init(){
	if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer))
		return false;
	SDLGraphDraw::setRes(SCREEN_WIDTH,SCREEN_HEIGHT);
	srand(time(NULL));
	return true;
}

void close(){
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow(window);
	SDL_Quit();
	renderer = NULL;
	window = NULL;
}

int main(int argc, char* argv[]) {
	if(! init() ){
		std::cout << "Failed to initialize!" << endl;
		exit(1);
	}
	Graph* g1 = GraphGen::randGraph(10,17,50, 750, 50, 550);
	Path* p = dijsktra(g1, g1->getVertexSet()[0], g1->getVertexSet()[1]);
	SDL_Event e;
	bool moving = false;
	SDL_RenderDrawPoint(renderer,50, 50);
	Camera* c = new Camera(0,0,SDLGraphDraw::getHRes(), SDLGraphDraw::getVRes(), 1000);
	while( SDL_WaitEvent(&e) )
	{
		if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) || e.type == SDL_QUIT)
			break;
		else if(e.type  ==  SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
			std::cout << "left pressed"<<endl;
			delete g1;
			delete p;
			g1 = GraphGen::randGraph(10,17,50, 750, 50, 550);
			p = dijsktra(g1, g1->getVertexSet()[0], g1->getVertexSet()[1]);
		}
		else if(e.type  ==  SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT){
			moving = true;
			continue;
		}
		else if(e.type  ==  SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_MIDDLE){
			int x, y;
			SDL_GetMouseState(&x, &y);
			//c->movePartialAbsCentered(x, y , .5);
		}
		else if(e.type  ==  SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT){
			moving = false;
			continue;
		}
		else if(e.type  ==  SDL_MOUSEMOTION && moving){
			cout << "moving " << e.motion.xrel << ", " <<e.motion.yrel<< endl;
			//c->moveRel(-c->getZoomScaleX(SDLGraphDraw::getHRes()) * e.motion.xrel, - c->getZoomScaleY(SDLGraphDraw::getVRes()) * e.motion.yrel);
			//c->moveRelScaled(-e.motion.xrel, -e.motion.yrel, SDLGraphDraw::getHRes(), SDLGraphDraw::getVRes());
			c->moveRelScreen(-e.motion.xrel, -e.motion.yrel, SDLGraphDraw::getHRes(), SDLGraphDraw::getVRes());
		}
		else if(e.type  ==  SDL_MOUSEWHEEL ){
			if( e.wheel.y > 0){
				int x, y;
				SDL_GetMouseState(&x, &y);
				//c->movePartialAbsCentered(x, y , SDLGraphDraw::getHRes(),  SDLGraphDraw::getVRes(), 1);
				//c->mulScale(.5,.5);
				c->uncenteredMulScale(.75,.75,x,y,SDLGraphDraw::getHRes(),  SDLGraphDraw::getVRes() );
			}
			else if( e.wheel.y < 0){
				//c->mulScale(2,2);
				int x, y;
				SDL_GetMouseState(&x, &y);
				c->uncenteredMulScale(1.25,1.25,x,y,SDLGraphDraw::getHRes(),  SDLGraphDraw::getVRes() );
			}
			std::cout << "mouse wheel "<< e.wheel.y <<endl;
			std::cout << "x0 : "  << c->getX() << ", y0 : " << c->getY() <<  "; "<< "x1 : " <<  c->getFinalX() << ", y1 : "<< c->getFinalY() << endl;
		}
		else continue;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(renderer );
		SDLGraphDraw::drawGraph(renderer,c, g1);
		SDLGraphDraw::drawPath(renderer, c, p);
		SDL_RenderPresent(renderer);
	}
	close();
	return 0;
}
