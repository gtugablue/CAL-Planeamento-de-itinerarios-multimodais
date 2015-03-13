#include "SDLGraphDraw.h"

 void SDLGRAPHDRAW::drawEdge(SDL_Renderer *renderer,Edge* e, SDLRGB color){
		SDL_SetRenderDrawColor( renderer, color.red,color.green, color.blue, 0xFF);
		SDL_RenderDrawLine(renderer, e->getSrc()->getRenderX(), e->getSrc()->getRenderY(),e->getDst()->getRenderX(), e->getDst()->getRenderY());
	}

 void SDLGRAPHDRAW::drawGraph(SDL_Renderer *renderer, Graph* e){
	for(size_t i = 0; i < e->getVertexSet().size(); i++){
		if(i == 0)
			drawVertex(renderer,e->getVertexSet()[i], 5, SDLRGB(0, 0xFF,0));
		else if(i == 1)
			drawVertex(renderer,e->getVertexSet()[i], 5, SDLRGB(0xFF, 0xFF,0));
		else
		drawVertex(renderer,e->getVertexSet()[i], 5, SDLRGB(0xFF, 0,0));
		for(size_t j = 0; j < e->getVertexSet()[i]->getAdj().size(); j++){
			drawEdge(renderer, e->getVertexSet()[i]->getAdj()[j], e->getVertexSet()[i]->getAdj()[j]->getColor());
		}
	}
}

 void SDLGRAPHDRAW::drawPath(SDL_Renderer *renderer, Path* e){
//	for(size_t i = 0; i < e->getEdges().size(); i++){
//		drawEdge(renderer, e->getEdges()[i], SDLRGB(0xFF, 0, 0));
//	}
	 if(e->getVertices().size() == 0)
		 return;
	 SDLRGB color(0xFF, 0, 0);
	 for(size_t i = 0; i < e->getVertices().size()-1; i++){
		 SDL_SetRenderDrawColor( renderer, color.red,color.green, color.blue, 0xFF);
		 SDL_RenderDrawLine(renderer, e->getVertices()[i]->getRenderX(), e->getVertices()[i]->getRenderY(),e->getVertices()[i+1]->getRenderX(), e->getVertices()[i+1]->getRenderY());
	 }
}

 void SDLGRAPHDRAW::drawVertex(SDL_Renderer *renderer, Vertex* v, int size, SDLRGB color){
	 int offset = (float) size / 2 +.5;
	for(size_t i = v->getRenderX()-offset; i <  v->getRenderX() + offset ; i++){
		for(size_t j = v->getRenderY()-offset; j <  v->getRenderY() + offset ; j++){
				SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
				SDL_RenderDrawPoint(renderer,i, j);
			}
	}
}
