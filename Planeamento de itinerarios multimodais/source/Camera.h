#ifndef CAMERA_H
#define CAMERA_H

class Camera{

private:
	double x0, y0, x1, y1;
	double maxWidth, maxHeight;
	void setValues(double x0, double y0, double x1, double y1);
public:
	Camera(double x0, double y0, double x1, double y1, double limit);
	void moveAbs(double x, double y);
	void movePartialAbsCentered(double x, double y,  double h_res, double v_res, double extent = 1.0);
	void moveRel(double x, double y);
	void moveRelScaled(double x, double y, double h_res, double v_res);
	void moveRelScreen(double x, double y, double h_res, double v_res);
	void mulScale(double factorx, double factory);
	void uncenteredMulScale(double factorx, double factory, double x, double y, double h_res, double v_res);
	void addScale(double addx, double addy);
	void addScaleUniform(double add, bool onWidth = true);
	double getX() const;
	double getY() const;
	double getFinalX() const;
	double getFinalY() const;
	double getWidth() const;
	double getHeight() const;
	double getRenderX(double h_res, double worldX) const;
	double getRenderY(double v_res, double worldY) const;
	double getWorldX(double h_res, double renderX) const;
	double getWorldY(double v_res, double renderY) const;
	double getZoomScaleX(double h_res)const;
	double getZoomScaleY(double v_res)const;

};

#endif
