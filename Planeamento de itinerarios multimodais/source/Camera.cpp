#include "Camera.h"

#include <stdlib.h>
#define min(a,b) ((a<=b)? a : b)

//void Camera::setValues(double x0, double y0, double x1, double y1){
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
//Camera::Camera(double x0, double y0, double x1, double y1){
//	this->x0 = x0;
//	this->y0 = y0;
//	this->x1 = x1;
//	this->y1 = y1;
//}
//
//void Camera::moveAbs(double x, double y){
//	double deltax = x - x0;
//	double deltay = y - y0;
//	x0 += deltax;
//	x1 += deltax;
//	y0 += deltay;
//	y0 += deltay;
//}
//
//void Camera::moveRel(double x, double y){
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
//void Camera::addScale(double addx, double addy){
//	x0-= addx/2;
//	y0 -= addy/2;
//	x1 += addx/2;
//	y1 += addy/2;
//}
//
//void Camera::addScaleUniform(double add, bool onWidth){
//	if(onWidth)
//		addScale(add, add * (y1-y0)/(x1-x0));
//	else
//		addScale(add* (x1-x0)/(y1-y0), add);
//}
//
//double Camera::getX() const {return x0;}
//
//double Camera::getY() const {return y0;}
//
//double Camera::getFinalX() const {return x1;}
//
//double Camera::getFinalY() const {return y1;}
//
//double Camera::getWidth() const {return x1-x0;}
//
//double Camera::getHeight() const {return y1- y0;}
//
//double Camera::getRenderX(double h_res, double worldX) const{
//	return (worldX-x0)*h_res/(x1-x0);
//}
//double Camera::getRenderY(double v_res, double worldY) const{
//	return (worldY-y0)*v_res/(y1-y0);
//}
//
//double Camera::getWorldX(double h_res, double renderX) const{
//	return x0+renderX*(x1-x0)/h_res;
//}
//double Camera::getWorldY(double v_res, double renderY) const{
//	return y0+renderY*(y1-y0)/v_res;
//}
//
//double Camera::getZoomScaleX(double h_res)const{
//	return ((double)(x1-x0))/h_res;
//}
//double Camera::getZoomScaleY(double v_res)const{
//	return ((double)(y1-y0))/v_res;
//}
//void Camera::moveRelScaled(double x, double y, double h_res, double v_res){
//	double movex = x*getZoomScaleX(h_res);
//	double movey = y*getZoomScaleY(v_res);
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

void Camera::setValues(double x0, double y0, double x1, double y1){
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

Camera::Camera(double x0, double y0, double x1, double y1, double limit){
	this->maxWidth = (x1 - x0) * limit;
	this->maxHeight = (y1 - y0) * limit;
	setValues(x0, y0, x1, y1);
}

void Camera::moveAbs(double x, double y){
	double deltax = x - x0;
	double deltay = y - y0;
	setValues(x0+deltax,  y0+deltay,x1+deltax, y1+deltay);
}

void Camera::moveRel(double x, double y){
	setValues(x0+x, y0+y,  x1+x, y1+y);
}
void  Camera::moveRelScreen(double x, double y, double h_res, double v_res){
	moveAbs(getWorldX(h_res, getRenderX(h_res,x0) + x), getWorldY(v_res, getRenderY(v_res, y0) + y));
	//getWorldX(x, h_res);
}
void Camera::movePartialAbsCentered(double x, double y,  double h_res, double v_res, double extent){
	moveRel((x-(x1+x0)/2)*extent * min(getZoomScaleX(h_res), 1),(y-(y1+y0)/2)*extent * min(getZoomScaleY(v_res), 1));
}

void Camera::mulScale(double factorx, double factory){
	if(factorx == 0 || factory == 0)
		return;
	if(factorx < 0)
		factorx = -factorx;
	if(factory < 0)
		factory = -factory;
	double xmul = (x1-x0)* factorx;
	double ymul = (y1-y0)* factory;
	setValues(((x1+x0) - xmul)/2, ((y1+y0) - ymul)/2, ((x1+x0) +xmul)/2,((y1+y0) + ymul)/2);
}

void Camera::uncenteredMulScale(double factorx, double factory, double x, double y, double h_res, double v_res){
	x = getWorldX(h_res, x);
	y = getWorldY(v_res, y);
	double posx = factorx*x0+(1-factorx)*x;
	double posy = factory*y0+(1-factory)*y;
	mulScale(factorx, factory);
	moveAbs(posx, posy);
}


void Camera::addScale(double addx, double addy){
	setValues(x0 - addx/2, y0 - addy/2, x1 + addx/2, y1 + addx/2);
}

void Camera::addScaleUniform(double add, bool onWidth){
	if(onWidth)
		addScale(add, add * (y1-y0)/(x1-x0));
	else
		addScale(add* (x1-x0)/(y1-y0), add);
}

double Camera::getX() const {return x0;}

double Camera::getY() const {return y0;}

double Camera::getFinalX() const {return x1;}

double Camera::getFinalY() const {return y1;}

double Camera::getWidth() const {return x1-x0;}

double Camera::getHeight() const {return y1- y0;}

double Camera::getRenderX(double h_res, double worldX) const{
	return (worldX-x0)*h_res/(x1-x0);
}
double Camera::getRenderY(double v_res, double worldY) const{
	return (worldY-y0)*v_res/(y1-y0);
}

double Camera::getWorldX(double h_res, double renderX) const{
	return x0+renderX*(x1-x0)/h_res;
}
double Camera::getWorldY(double v_res, double renderY) const{
	return y0+renderY*(y1-y0)/v_res;
}

double Camera::getZoomScaleX(double h_res)const{
	return ((double)(x1-x0))/h_res;
}
double Camera::getZoomScaleY(double v_res)const{
	return ((double)(y1-y0))/v_res;
}
void Camera::moveRelScaled(double x, double y, double h_res, double v_res){
	double movex = x*getZoomScaleX(h_res);
	double movey = y*getZoomScaleY(v_res);
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
