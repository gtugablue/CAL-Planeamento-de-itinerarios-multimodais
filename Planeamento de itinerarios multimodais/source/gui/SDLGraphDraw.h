#ifndef SDLGRAPHDRAW_H
#define SDLGRAPHDRAW_H


using namespace std;

#include "../graph/Edge.h"
#include "../graph/Graph.h"
#include "../graph/Path.h"
#include "../transport/TransportEdge.h"
#include "../transport/MetroEdge.h"
#include "SDLRGB.h"
#include "Camera.h"
#include "Slider.h"

#include <SDL2/SDL.h>

class Graph;
class Edge;

/**
 * @brief Implements an interface to draw a graph using SDL
 */
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
	/*static void drawMapGraph(SDL_Renderer *renderer, Camera* c, Graph* g){
		SDLRGB color = SDLRGB(0xFF,0,0);
		SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
		vector<Vertex* >verts = g->getVertexSet();
		Coordinates c1(0,0);
		Coordinates c2(0,0);
		int srcscreenx;
		int srcsreeny;
		int dstscreenx;
		int dstscreeny;
		vector<Coordinates> line;
		for(size_t i = 0; i < verts.size(); i++){
			vector<Edge*> eds =  verts[i]->getAdj();
			for(size_t j = 0; j < eds.size(); j++){
				if(!((TransportEdge*)eds[j])->getVisible())
					continue;
				c1 = eds[j]->getSrc()->getCoords();
				c2 =  eds[j]->getDst()->getCoords();
				if((c1.getLongitude()< c->getX() || c1.getLongitude() > c->getFinalX()) && (c1.getLatitude()< c->getY() || c1.getLatitude() > c->getFinalY()))
					continue;
				//if(c->getZoomScaleX() > 50){
					srcscreenx =c->getRenderX(h_res, c1.getLongitude());
					srcsreeny = c->getRenderY(v_res, c1.getLatitude());
					dstscreenx = c->getRenderX(h_res,c2.getLongitude());
					dstscreeny =  c->getRenderY(v_res, c2.getLatitude());
					SDL_RenderDrawLine(renderer,srcscreenx , srcsreeny , dstscreenx,dstscreeny );
//				}
//				else{
//					line = ((TransportEdge*)(eds[j]))->getLine();
//					for(size_t k = 0; k < line.size()-1; k++){
//						//c1 = eds[j]->getSrc()->getCoords();
//						//c2 = eds[j]->getDst()->getCoords();
//						c1 = line[k];
//						c2 = line[k+1];
//						if((c1.getLongitude()< c->getX() || c1.getLongitude() > c->getFinalX()) && (c1.getLatitude()< c->getY() || c1.getLatitude() > c->getFinalY()))
//							continue;
//						srcscreenx =c->getRenderX(h_res, c1.getLongitude());
//						srcsreeny = c->getRenderY(v_res, c1.getLatitude());
//						dstscreenx = c->getRenderX(h_res,c2.getLongitude());
//						dstscreeny =  c->getRenderY(v_res, c2.getLatitude());
//						SDL_RenderDrawLine(renderer,srcscreenx , srcsreeny , dstscreenx,dstscreeny );
//					}
//				//}
			}
		}
		for(size_t i = 0; i < verts.size(); i++){
			int offset = (float) 5 / 2 +.5;
			int renderx = c->getRenderX(h_res,verts[i]->getCoords().getLongitude());
			int rendery =  c->getRenderY(v_res,verts[i]->getCoords().getLatitude());
			for(size_t i = renderx-offset; i <  renderx + offset ; i++){
				for(size_t j = rendery-offset; j <  rendery + offset ; j++){
					SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
					SDL_RenderDrawPoint(renderer, i, j);
				}
			}
		}
	}*/
	static void drawMapEdge(SDL_Renderer *renderer, Camera* c, Edge* e, bool debug){
//		if(debug){
//			Coordinates c1 = e->getSrc()->getCoords();
//			Coordinates c2 =  e->getDst()->getCoords();
//			if((c1.getLongitude()< c->getX() || c1.getLongitude() > c->getFinalX()) && (c2.getLatitude()< c->getY() || c2.getLatitude() > c->getFinalY()))
//				return;
//			//if(c->getZoomScaleX() > 50){
//			int srcscreenx =c->getRenderX(h_res, c1.getLongitude());
//			int srcsreeny = c->getRenderY(v_res, c1.getLatitude());
//			int dstscreenx = c->getRenderX(h_res,c2.getLongitude());
//			int dstscreeny =  c->getRenderY(v_res, c2.getLatitude());
//
//			SDL_RenderDrawLine(renderer,srcscreenx , srcsreeny , dstscreenx,dstscreeny );
//		}
//		else {
			int num = ((TransportEdge*)e)->getLine().size();
			//SDL_Point points[num];
			SDL_Point* points = (SDL_Point*)malloc(sizeof(SDL_Point) * num);
			for(int i = 0; i < num; i++){
				points[i].x = c->getRenderX(h_res, ((TransportEdge*)e)->getLine()[i].getLongitude());
				points[i].y = c->getRenderY(v_res, ((TransportEdge*)e)->getLine()[i].getLatitude());
				if(debug && (i == 0 || i == num-1))
					drawMapVertexPos(renderer,c, points[i].x,  points[i].y, SDLRGB (0,0, 0xFF));
				//if(debug) cerr << ((TransportEdge*)e)->getLine()[i].getLongitude() << ", " <<  ((TransportEdge*)e)->getLine()[i].getLatitude() << endl;
			}
			SDL_RenderDrawLines(renderer, points, num);
			delete points;
		//}
	}
		static void drawMapVertex(SDL_Renderer *renderer, Camera* c, Vertex* e, SDLRGB color){
			int offset = (float) 5 / 2 +.5;
			int renderx = c->getRenderX(h_res,e->getCoords().getLongitude());
			int rendery =  c->getRenderY(v_res,e->getCoords().getLatitude());
			SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
			for(size_t i = renderx-offset; i <  renderx + offset ; i++){
				for(size_t j = rendery-offset; j <  rendery + offset ; j++){
					SDL_RenderDrawPoint(renderer, i, j);
				}
			}
		}
		static void drawMapVertexPos(SDL_Renderer *renderer, Camera* c,int renderx, int rendery, SDLRGB color){
					int offset = (float) 5 / 2 +.5;
					//int offset = 1;
					SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
					for(size_t i = renderx-offset; i <  renderx + offset ; i++){
						for(size_t j = rendery-offset; j <  rendery + offset ; j++){
							SDL_RenderDrawPoint(renderer, i, j);
						}
					}
				}
		static void drawMapGraph(SDL_Renderer *renderer, Camera* c, Graph* g, Vertex* src, Vertex* dst, Path* p){
				SDLRGB color = SDLRGB(0xFF,0,0);
				SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
				vector<Vertex* >verts = g->getVertexSet();
				Coordinates c1(0,0);
				Coordinates c2(0,0);
				int srcscreenx;
				int srcsreeny;
				int dstscreenx;
				int dstscreeny;
				vector<Coordinates> line;
				for(size_t i = 0; i < verts.size(); i++){
					vector<Edge*> eds =  verts[i]->getAdj();
					for(size_t j = 0; j < eds.size(); j++){
						if(!((TransportEdge*)eds[j])->getVisible())
							continue;
							//SDL_SetRenderDrawColor(renderer,175,238,238, 0xFF);
						else{
							if(dynamic_cast<MetroEdge*>(eds[j]) == NULL)
							SDL_SetRenderDrawColor(renderer,0xFF,0, 0, 0xFF);
						else SDL_SetRenderDrawColor(renderer,0,0, 0xFF, 0xFF);
						}
						drawMapEdge(renderer,c,eds[j], false);
					}
				}
				/*for(size_t i = 0; i < verts.size(); i++){
					int offset = (float) 5 / 2 +.5;
					int renderx = c->getRenderX(h_res,verts[i]->getCoords().getLongitude());
					int rendery =  c->getRenderY(v_res,verts[i]->getCoords().getLatitude());
					for(size_t i = renderx-offset; i <  renderx + offset ; i++){
						for(size_t j = rendery-offset; j <  rendery + offset ; j++){
							SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
							SDL_RenderDrawPoint(renderer, i, j);
						}
					}
				}*/
				if(src != NULL){
					drawMapVertex(renderer, c, src, SDLRGB (0,0xFF,0));
				}
				if(dst != NULL){
					drawMapVertex(renderer,c, dst, SDLRGB (0,0xFF,0));
				}
				if(p != NULL){
					for(size_t i = 0 ; i < p->getEdges().size(); i++){
						//if(!((TransportEdge*)p->getEdges()[i])->getVisible())
							//continue;
						//SDL_SetRenderDrawColor(renderer,175,238,238, 0xFF);
						//drawMapEdge(renderer,c, p->getEdges()[i], true);
						SDL_SetRenderDrawColor(renderer,0,0xFF, 0, 0xFF);
						drawMapEdge(renderer,c, p->getEdges()[i], false);
						drawMapVertex(renderer, c, p->getEdges()[i]->getSrc(), SDLRGB(0, 0xFF,0));
						drawMapVertex(renderer, c, p->getEdges()[i]->getDst(), SDLRGB(0, 0xFF,0));
					}
				}
			}

		static void drawMapGraphPerformance(SDL_Renderer *renderer, Camera* c, Graph* g, Vertex* src, Vertex* dst, Path* p){
			vector<Vertex* >verts = g->getVertexSet();
			for(size_t i = 0; i < verts.size(); i++){
				if(verts[i]->getProcessed()){
					drawMapVertex(renderer, c, verts[i], SDLRGB(0xFF, 0xFF,0));
				}
			}
			drawMapGraph(renderer, c, g, src, dst, p);
		}
};



#endif
