#ifndef CAMERA_H
#define CAMERA_H

class Camera{

private:
	int x0, y0, x1, y1;
public:
	Camera(int x0, int y0, int x1, int y1);
	void moveAbs(int x, int y);
	void moveRel(int x, int y);
	void moveRelScaled(int x, int y, int h_res, int v_res);
	void mulScale(double factorx, double factory);
	void addScale(int addx, int addy);
	int getX() const;
	int getY() const;
	int getFinalX() const;
	int getFinalY() const;
	int getWidth() const;
	int getHeight() const;
	int getRenderX(int h_res, int worldX) const;
	int getRenderY(int v_res, int worldY) const;
	int getWorldX(int h_res, int renderX) const;
	int getWorldY(int v_res, int renderY) const;
	double getZoomScaleX(int h_res)const;
	double getZoomScaleY(int v_res)const;

};

#endif
