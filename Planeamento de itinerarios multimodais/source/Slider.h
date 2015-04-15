#ifndef SLIDER_H
#define SLIDER_H

class Slider{
public:
	Slider(int x, int y, int width, int height,int cursorWidth, int cursorHeight,  double min, double max, double value, bool horizontal = true){
		this->x = x;
		this->y = y;
		this->width = width;
		this->cursorWidth = cursorWidth;
		this->cursorHeight = cursorHeight;
		this->height = height;
		this->min = min;
		this->max = max;
		this->value;
		this->horizontal = true;
		this->selected = false;
	}
	bool setValue(double value){
		if(value < min ){
			this->value = min;
			return false;
		}
		else if(value > max){
			this->value = max;
			return false;
		}
		this->value = value;
		return true;
	}
	double getValue() const{
		return value;
	}
	int getHeight() const {
		return height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	double getMax() const {
		return max;
	}

	void setMax(double max) {
		this->max = max;
	}

	double getMin() const {
		return min;
	}

	void setMin(double min) {
		this->min = min;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	bool isHorizontal() const {
		return horizontal;
	}

	void setHorizontal(bool horizontal) {
		this->horizontal = horizontal;
	}
	bool setValueUI(int screenPos){
		return setValue(resToValue(screenPos));
	}
	double resToValue(int res){
		int ori;
		int dim;
		if(horizontal){
			ori = x;
			dim = width;
		}else {
			ori = y;
			dim = height;
		}
		return ((max-min)*(res - ori))/dim;
	}
	int valueToRes(double value){
		int ori;
		int dim;
		if(horizontal){
			ori = x;
			dim = width;
		}else {
			ori = y;
			dim = height;
		}
		return (int)((dim*value)/(max-min) + ori);
	}
	int getCursorHeight() const {
		return cursorHeight;
	}

	void setCursorHeight(int cursorHeight) {
		this->cursorHeight = cursorHeight;
	}

	int getCursorWidth() const {
		return cursorWidth;
	}

	void setCursorWidth(int cursorWidth) {
		this->cursorWidth = cursorWidth;
	}

	int getCursorX(){
		if(horizontal){
			int cursorMiddle = valueToRes(value);
			return cursorMiddle - cursorWidth/2;
		}else{
			return x + width/2 - cursorWidth/2;
		}
	}
	int getCursorY(){
			if(!horizontal){
				int cursorMiddle = valueToRes(value);
				return cursorMiddle - cursorHeight/2;
			}else{
				return y + height/2 - cursorHeight/2;
			}
		}

	bool select(int posX, int posY){
		/*int middle = valueToRes(value);
		if(horizontal){
			if(posX >= middle - cursorWidth /2 && posX <= middle + cursorWidth /2  && posY >=  y + height/2 - cursorHeight/2 &&  posY <=  y + height/2 + cursorHeight/2)
				selected = true;
			else selected = false;
		}else {
			if(posY >= middle - cursorHeight /2 && posY <= middle + cursorHeight /2  && posX >=  x + width/2 - cursorWidth/2 &&  posX <=  x + width/2 + cursorWidth/2)
				selected = true;
			else selected = false;
		}
		return selected;*/
		int cursorX = getCursorX();
		int cursorY = getCursorY();
		if(posX >= cursorX && posX <= cursorX + cursorWidth&&posY >= cursorY && posY <= cursorY + cursorHeight)
			selected = true;
		else selected = false;
		return selected;
	}

	bool isSelected() const {
		return selected;
	}

	void setSelected(bool selected) {
		this->selected = selected;
	}

private:
	int x, y;
	int width, height;
	int cursorWidth, cursorHeight;
	double min, max;
	double value;
	bool horizontal;
	bool selected;

};



#endif
