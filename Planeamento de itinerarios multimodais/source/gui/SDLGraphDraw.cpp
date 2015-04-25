#include "SDLGraphDraw.h"

unsigned int SDLGraphDraw::h_res = 0;
unsigned int SDLGraphDraw::v_res = 0;
double  SDLGraphDraw::minlat = 0;
double  SDLGraphDraw::maxlat = 0;
double SDLGraphDraw::minlong = 0;
double  SDLGraphDraw::maxlong = 0;
 void SDLGraphDraw::drawEdge(SDL_Renderer *renderer,Edge* e, SDLRGB color){

		SDL_RenderDrawLine(renderer, getDrawX(e->getSrc()->getRenderX()), getDrawY(e->getSrc()->getRenderY()),getDrawX(e->getDst()->getRenderX()), getDrawY(e->getDst()->getRenderY()));
	}

 void SDLGraphDraw::drawGraph(SDL_Renderer *renderer, Graph* e){
	for(size_t i = 0; i < e->getVertexSet().size(); i++){
		/*if(i == 0)
			drawVertex(renderer,e->getVertexSet()[i], 5, SDLRGB(0, 0xFF,0));
		else if(i == 1)
			drawVertex(renderer,e->getVertexSet()[i], 5, SDLRGB(0xFF, 0xFF,0));
		else*/
		SDL_SetRenderDrawColor( renderer, 0xFF,0, 0, 0xFF);
		drawVertex(renderer,e->getVertexSet()[i], 5, SDLRGB(0xFF, 0,0));
		for(size_t j = 0; j < e->getVertexSet()[i]->getAdj().size(); j++){
			drawEdge(renderer, e->getVertexSet()[i]->getAdj()[j], e->getVertexSet()[i]->getAdj()[j]->getColor());
		}
	}
}

 void SDLGraphDraw::drawPath(SDL_Renderer *renderer, Path* e){
//	for(size_t i = 0; i < e->getEdges().size(); i++){
//		drawEdge(renderer, e->getEdges()[i], SDLRGB(0xFF, 0, 0));
//	}
	// if(e->getVertices().size() == 0)
		// return;
	 SDLRGB color(0xFF, 0, 0);
	/* for(size_t i = 0; i < e->getVertices().size()-1; i++){
		 SDL_SetRenderDrawColor( renderer, color.red,color.green, color.blue, 0xFF);
		 SDL_RenderDrawLine(renderer, e->getVertices()[i]->getRenderX(), e->getVertices()[i]->getRenderY(),e->getVertices()[i+1]->getRenderX(), e->getVertices()[i+1]->getRenderY());
	 }*/
	 for(size_t i = 0; i < e->getEdges().size(); i++){
			 SDL_SetRenderDrawColor( renderer, color.red,color.green, color.blue, 0xFF);
			 SDL_RenderDrawLine(renderer,e->getEdges()[i]->getSrc()->getRenderX(), e->getEdges()[i]->getSrc()->getRenderY(),e->getEdges()[i]->getDst()->getRenderX(),e->getEdges()[i]->getDst()->getRenderY());
		 }
}

 void SDLGraphDraw::drawVertex(SDL_Renderer *renderer, Vertex* v, int size, SDLRGB color){
	 int offset = (float) size / 2 +.5;
	for(size_t i = v->getRenderX()-offset; i <  v->getRenderX() + offset ; i++){
		for(size_t j = v->getRenderY()-offset; j <  v->getRenderY() + offset ; j++){
				SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
				SDL_RenderDrawPoint(renderer,i, j);
			}
	}
}
/////



void SDLGraphDraw::drawEdge(SDL_Renderer *renderer, Camera* c, Edge* e, SDLRGB color){
		SDL_RenderDrawLine(renderer, c->getRenderX(h_res, e->getSrc()->getRenderX()),  c->getRenderY(v_res, e->getSrc()->getRenderY()), c->getRenderX(h_res, e->getDst()->getRenderX()),  c->getRenderY(v_res, e->getDst()->getRenderY()));
	}
void SDLGraphDraw::drawGraph(SDL_Renderer *renderer, Camera* c, Graph* e){
		for(size_t i = 0; i < e->getVertexSet().size(); i++){
			/*if(i == 0)
				drawVertex(renderer, c, e->getVertexSet()[i], 5, SDLRGB(0, 0xFF,0));
			else if(i == 1)
				drawVertex(renderer,c,e->getVertexSet()[i], 5, SDLRGB(0xFF, 0xFF,0));
			else
			drawVertex(renderer,c,e->getVertexSet()[i], 5, SDLRGB(0xFF, 0,0));*/
			//SDLRGB color = e->getVertexSet()[i]->getAdj()[j]->getColor();
			SDLRGB color = SDLRGB(0xFF,0,0);
			SDL_SetRenderDrawColor( renderer, color.red,color.green, color.blue, 0xFF);
			for(size_t j = 0; j < e->getVertexSet()[i]->getAdj().size(); j++){
				drawEdge(renderer,c, e->getVertexSet()[i]->getAdj()[j], color);
			}
		}
	}
void SDLGraphDraw::drawPath(SDL_Renderer *renderer, Camera* c, Path* e,SDLRGB color){
	 //	for(size_t i = 0; i < e->getEdges().size(); i++){
	 //		drawEdge(renderer, e->getEdges()[i], SDLRGB(0xFF, 0, 0));
	 //	}
	 	 /*if(e->getVertices().size() == 0)
	 		 return;
	 	 SDLRGB color(0xFF, 0, 0);
	 	 for(size_t i = 0; i < e->getVertices().size()-1; i++){
	 		 SDL_SetRenderDrawColor( renderer, color.red,color.green, color.blue, 0xFF);
	 		 SDL_RenderDrawLine(renderer,  c->getRenderX(h_res, e->getVertices()[i]->getRenderX()),  c->getRenderY(v_res, e->getVertices()[i]->getRenderY()), c->getRenderX(h_res, e->getVertices()[i+1]->getRenderX()),  c->getRenderY(v_res, e->getVertices()[i+1]->getRenderY()));
	 	 }*/
	for(size_t i = 0; i < e->getEdges().size(); i++){
		 SDL_SetRenderDrawColor( renderer, color.red,color.green, color.blue, 0xFF);
		 SDL_RenderDrawLine(renderer,  c->getRenderX(h_res, e->getEdges()[i]->getSrc()->getRenderX()),  c->getRenderY(v_res, e->getEdges()[i]->getSrc()->getRenderY()), c->getRenderX(h_res, e->getEdges()[i]->getDst()->getRenderX()),  c->getRenderY(v_res,e->getEdges()[i]->getDst()->getRenderY()));
	}

}




void SDLGraphDraw::drawVertex(SDL_Renderer *renderer, Camera* c, Vertex* v, int size, SDLRGB color){
	 int offset = (float) size / 2 +.5;
	int renderx = c->getRenderX(h_res,v->getRenderX());
	int rendery =  c->getRenderY(v_res,v->getRenderY());
	for(size_t i = renderx-offset; i <  renderx + offset ; i++){
		for(size_t j = rendery-offset; j <  rendery + offset ; j++){
				SDL_SetRenderDrawColor( renderer,color.red,color.blue, color.green, 0xFF);
				SDL_RenderDrawPoint(renderer, i, j);
			}
	}
}

void SDLGraphDraw::drawSlider(SDL_Renderer *renderer, Slider* slider, SDLRGB color1, SDLRGB color2){
	SDL_Rect body;
	SDL_Rect cursor;
	body.x = slider->getX();
	body.y = slider->getY();
	body.w = slider->getWidth();
	body.h = slider->getHeight();

	cursor.x = slider->getCursorX();
	cursor.y = slider->getCursorY();
	cursor.w = slider->getCursorWidth();
	cursor.h = slider->getCursorHeight();
	SDL_SetRenderDrawColor( renderer,color1.red,color1.blue, color1.green, 0xFF);
	SDL_RenderFillRect(renderer, &body);
	SDL_SetRenderDrawColor( renderer,color1.red,color1.blue, color1.green, 0xFF);
	SDL_RenderFillRect(renderer, &cursor);
}

