#include "Camera.h"

#include <stdlib.h>
#define min(a,b) ((a<=b)? a : b)

//void Camera::setValues(int x0, int y0, int x1, int y1){
//	if(x0 < x1){
//		this->x0 = x0;
//		this->x1 = x1;
//	}else if(x0 > x1){
//		this->x0 = x1;
//		this->x1 = x0;
//	}
//	else{
//		this->x0 = x0;
//		this->x1 = x0+1;
//	}
//	if(y0 < y1){
//		this->y0 = y0;
//		this->y1 = y1;
//	}else if(y0 > y1){
//		this->y0 = y1;
//		this->y1 = y0;
//	}
//	else{
//		this->y0 = y0;
//		this->y1 = y0+1;
//	}
//}
//
//Camera::Camera(int x0, int y0, int x1, int y1){
//	this->x0 = x0;
//	this->y0 = y0;
//	this->x1 = x1;
//	this->y1 = y1;
//}
//
//void Camera::moveAbs(int x, int y){
//	int deltax = x - x0;
//	int deltay = y - y0;
//	x0 += deltax;
//	x1 += deltax;
//	y0 += deltay;
//	y0 += deltay;
//}
//
//void Camera::moveRel(int x, int y){
//	x0 += x;
//	x1 += x;
//	y0 += y;
//	y1 += y;
//}
//
//void Camera::mulScale(double factorx, double factory){
//	if(factorx == 0 || factory == 0)
//		return;
//	if(factorx < 0)
//		factorx = -factorx;
//	if(factory < 0)
//		factory = -factory;
//	x0 = ((x1+x0) - (x1-x0)* factorx)/2;
//	y0 = ((y1+y0) - (y1-y0)* factory)/2;
//	x1 = ((x1+x0) + (x1-x0)* factorx)/2;
//	y1 = ((y1+y0) + (y1-y0)* factory)/2;
//}
//void Camera::addScale(int addx, int addy){
//	x0-= addx/2;
//	y0 -= addy/2;
//	x1 += addx/2;
//	y1 += addy/2;
//}
//
//void Camera::addScaleUniform(int add, bool onWidth){
//	if(onWidth)
//		addScale(add, add * (y1-y0)/(x1-x0));
//	else
//		addScale(add* (x1-x0)/(y1-y0), add);
//}
//
//int Camera::getX() const {return x0;}
//
//int Camera::getY() const {return y0;}
//
//int Camera::getFinalX() const {return x1;}
//
//int Camera::getFinalY() const {return y1;}
//
//int Camera::getWidth() const {return x1-x0;}
//
//int Camera::getHeight() const {return y1- y0;}
//
//int Camera::getRenderX(int h_res, int worldX) const{
//	return (worldX-x0)*h_res/(x1-x0);
//}
//int Camera::getRenderY(int v_res, int worldY) const{
//	return (worldY-y0)*v_res/(y1-y0);
//}
//
//int Camera::getWorldX(int h_res, int renderX) const{
//	return x0+renderX*(x1-x0)/h_res;
//}
//int Camera::getWorldY(int v_res, int renderY) const{
//	return y0+renderY*(y1-y0)/v_res;
//}
//
//double Camera::getZoomScaleX(int h_res)const{
//	return ((double)(x1-x0))/h_res;
//}
//double Camera::getZoomScaleY(int v_res)const{
//	return ((double)(y1-y0))/v_res;
//}
//void Camera::moveRelScaled(int x, int y, int h_res, int v_res){
//	int movex = x*getZoomScaleX(h_res);
//	int movey = y*getZoomScaleY(v_res);
//	if(movex == 0 && x != 0){
//		if(x < 0)
//			movex =-1;
//		else movex = 1;
//	}
//	if(movey == 0 && y != 0){
//		if(y < 0)
//			movey =-1;
//		else movey = 1;
//	}
//	moveRel(movex, movey);
//}

void Camera::setValues(int x0, int y0, int x1, int y1){
	if(abs(x1-x0) > maxWidth || abs(y1-y0) > maxHeight)
		return;
	if(x0 < x1){
		this->x0 = x0;
		this->x1 = x1;
	}
	if( y0 < y1){
		this->y0 = y0;
		this->y1 = y1;
	}
	return;
	if(x0 < x1){
		this->x0 = x0;
		this->x1 = x1;
	}else if(x0 > x1){
		this->x0 = x1;
		this->x1 = x0;
	}
	else{
		this->x0 = x0;
		this->x1 = x0+1;
	}
	if(y0 < y1){
		this->y0 = y0;
		this->y1 = y1;
	}else if(y0 > y1){
		this->y0 = y1;
		this->y1 = y0;
	}
	else{
		this->y0 = y0;
		this->y1 = y0+1;
	}

}

Camera::Camera(int x0, int y0, int x1, int y1, double limit){
	this->maxWidth = (x1 - x0) * limit;
	this->maxHeight = (y1 - y0) * limit;
	setValues(x0, y0, x1, y1);
}

void Camera::moveAbs(int x, int y){
	int deltax = x - x0;
	int deltay = y - y0;
	setValues(x0+deltax,  y0+deltay,x1+deltax, y1+deltay);
}

void Camera::moveRel(int x, int y){
	setValues(x0+x, y0+y,  x1+x,y1+y);
}

void Camera::movePartialAbsCentered(int x, int y,  int h_res, int v_res, double extent){
	moveRel((x-(x1+x0)/2)*extent * min(getZoomScaleX(h_res), 1),(y-(y1+y0)/2)*extent * min(getZoomScaleY(v_res), 1));
}

void Camera::mulScale(double factorx, double factory){
	if(factorx == 0 || factory == 0)
		return;
	if(factorx < 0)
		factorx = -factorx;
	if(factory < 0)
		factory = -factory;
	int xmul = (x1-x0)* factorx;
	int ymul = (y1-y0)* factory;
	setValues(((x1+x0) - xmul)/2, ((y1+y0) - ymul)/2, ((x1+x0) +xmul)/2,((y1+y0) + ymul)/2);
}

void Camera::uncenteredMulScale(double factorx, double factory, int x, int y, int h_res, int v_res){
	//int deltax = x - (x1 + x0) / 2;
	//int deltay = y - (y1 + y0) / 2;
	//mulScale(factorx, factory);
	//moveRel(deltax*factorx, deltay*factory);
	//moveAbs(-(((x1-x0)*factorx-x1+x0)*x-x0*h_res)/h_res , -(((y1-y0)*factory-y1+y0)*y-y0*v_res)/v_res );
	x = getWorldX(h_res, x);
	y = getWorldY(v_res, y);
	int posx = factorx*x0+(1-factorx)*x;
	int posy = factory*y0+(1-factory)*y;
	mulScale(factorx, factory);
	moveAbs(posx, posy);
}


void Camera::addScale(int addx, int addy){
	setValues(x0 - addx/2, y0 - addy/2, x1 + addx/2, y1 + addx/2);
}

void Camera::addScaleUniform(int add, bool onWidth){
	if(onWidth)
		addScale(add, add * (y1-y0)/(x1-x0));
	else
		addScale(add* (x1-x0)/(y1-y0), add);
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
