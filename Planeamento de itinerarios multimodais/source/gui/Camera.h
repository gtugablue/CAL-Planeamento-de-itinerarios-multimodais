#ifndef CAMERA_H
#define CAMERA_H

class Camera{

private:
	double x0, y0, x1, y1;
	double maxWidth, maxHeight;
	double minWidth, minHeight;
	bool setValues(double x0, double y0, double x1, double y1);
public:
	Camera(double x0, double y0, double x1, double y1, double limit);
	void moveAbs(double x, double y);
	void movePartialAbsCentered(double x, double y,  int h_res, int v_res, double extent = 1.0);
	void moveRel(double x, double y);
	void moveRelScaled(double x, double y, int h_res, int v_res);
	void moveRelScreen(double x, double y, int h_res, int v_res);
	bool mulScale(double factorx, double factory);
	bool uncenteredMulScale(double factorx, double factory, double x, double y, int h_res, int v_res);
	void addScale(double addx, double addy);
	void addScaleUniform(double add, bool onWidth = true);
	double getX() const;
	double getY() const;
	double getFinalX() const;
	double getFinalY() const;
	double getWidth() const;
	double getHeight() const;
	double getRenderX(int h_res, double worldX) const;
	double getRenderY(int v_res, double worldY) const;
	double getWorldX(int h_res, double renderX) const;
	double getWorldY(int v_res, double renderY) const;
	double getZoomScaleX(int h_res)const;
	double getZoomScaleY(int v_res)const;

};

#endif
