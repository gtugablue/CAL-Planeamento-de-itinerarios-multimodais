#ifndef SDLRGB_H
#define SDLRGB_H

class SDLRGB{
public:
	unsigned char red;
	unsigned char blue;
	unsigned char green;


	SDLRGB(unsigned char red, unsigned char blue,unsigned char green){
		this->red =red;
		this->blue = blue;
		this->green = green;
	}
};

#endif
