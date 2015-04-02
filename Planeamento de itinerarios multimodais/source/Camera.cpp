#include "Camera.h"

Camera::Camera(int x0, int y0, int x1, int y1){
	this->x0 = x0;
	this->y0 = y0;
	this->x1 = x1;
	this->y1 = y1;
}

void Camera::moveAbs(int x, int y){
	int deltax = x - x0;
	int deltay = y - y0;
	x0 += deltax;
	x1 += deltax;
	y0 += deltay;
	y0 += deltay;
}

void Camera::moveRel(int x, int y){
	x0 += x;
	x1 += x;
	y0 += y;
	y1 += y;
}

void Camera::mulScale(double factorx, double factory){
	if(factorx == 0 || factory == 0)
		return;
	if(factorx < 0)
		factorx = -factorx;
	if(factory < 0)
		factory = -factory;
	x0 = (x1+x0)/2 - (x1-x0)*factorx/2;
	y0 = (y1+y0)/2 -(y1-y0)*factory/2;
	x1 = (x1+x0)/2 +(x1-x0)*factorx/2;
	y1 = (y1+y0)/2 +(y1-y0)*factory/2;
}
void Camera::addScale(int addx, int addy){
	x0-= addx/2;
	y0 -= addy/2;
	x1 += addx/2;
	y1 += addy/2;
}
int Camera::getX() const {return x0;}

int Camera::getY() const {return y0;}

int Camera::getFinalX() const {return x1;}

int Camera::getFinalY() const {return y1;}

int Camera::getWidth() const {return x1-x0;}

int Camera::getHeight() const {return y1- y0;}


int Camera::getRenderX(int h_res, int worldX) const{
	return (worldX-x0)*h_res/(x1-x0);
}
int Camera::getRenderY(int v_res, int worldY) const{
	return (worldY-y0)*v_res/(y1-y0);
}

int Camera::getWorldX(int h_res, int renderX) const{
	return x0+renderX*(x1-x0)/h_res;
}
int Camera::getWorldY(int v_res, int renderY) const{
	return y0+renderY*(y1-y0)/v_res;
}

double Camera::getZoomScaleX(int h_res)const{
	return ((double)(x1-x0))/h_res;
}
double Camera::getZoomScaleY(int v_res)const{
	return ((double)(y1-y0))/v_res;
}
void Camera::moveRelScaled(int x, int y, int h_res, int v_res){
	int movex = x*getZoomScaleX(h_res);
	int movey = y*getZoomScaleY(v_res);
	if(movex == 0 && x != 0){
		if(x < 0)
			movex =-1;
		else movex = 1;
	}
	if(movey == 0 && y != 0){
		if(y < 0)
			movey =-1;
		else movey = 1;
	}
	moveRel(movex, movey);
}
