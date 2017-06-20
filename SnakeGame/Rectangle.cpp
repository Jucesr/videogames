#include "Rectangle.h"

struct RGBColor{

	Uint8 red;
	Uint8 blue;
	Uint8 green;
	Uint8 alpha;

};

Rectangle::Rectangle(){
}

Rectangle::Rectangle(int nposX, int nposY, int nwidth, int nheight, int nborder , int ncolor, int ntype){

	width = nwidth;
	color = ncolor;
	height = nheight;
	border = nborder;
	posX = nposX;
	posY = nposY;
	type = ntype;
	alpha = 255;

}

void Rectangle::setRectangle(int nposX, int nposY, int nwidth, int nheight, int nborder, int ncolor , int ntype){
	width = nwidth;
	color = ncolor;
	height = nheight;
	border = nborder;
	posX = nposX;
	posY = nposY;
	type =ntype;
}

void Rectangle::render(SDL_Renderer* gRenderer){


	bool suc = true;

	//Draw the fill rectangle
	SDL_Rect fill = { (posX+1)*width + border, (posY+1)*height + border, width - border*2, height - border*2 };
	RGBColor cRGB = getRGBColor();
	SDL_SetRenderDrawBlendMode( gRenderer, SDL_BLENDMODE_BLEND );
	SDL_SetRenderDrawColor( gRenderer, cRGB.red, cRGB.green, cRGB.blue, cRGB.alpha );		
	SDL_RenderFillRect( gRenderer, &fill );


	//Draw the border
	for (int i = 0; i < border-1; i++)
	{
	SDL_Rect fill = { (posX+1)*width+i, (posY+1)*height+i, width-i*2, height-i*2};
	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );		
	SDL_RenderDrawRect( gRenderer, &fill);
	
	}


}

int Rectangle::getColor(){

	return color;

}

RGBColor Rectangle::getRGBColor(){

	RGBColor cRGB;

	switch (color)
	{
		case COLOR_RED:
			cRGB.red = 255;
			cRGB.green = 0;
			cRGB.blue = 0;
			cRGB.alpha = alpha;
		break;

		case COLOR_BLUE:
			cRGB.red = 0;
			cRGB.green = 0;
			cRGB.blue = 255;
			cRGB.alpha = alpha;
		break;

		case COLOR_GREEN:
			cRGB.red = 0;
			cRGB.green = 255;
			cRGB.blue = 0;
			cRGB.alpha = alpha;
		break;

		case COLOR_BLACK:
			cRGB.red = 0;
			cRGB.green = 0;
			cRGB.blue = 0;
			cRGB.alpha = alpha;
		break;

		default:
			cRGB.red = 0;
			cRGB.green = 0;
			cRGB.blue = 0;
			cRGB.alpha = 0;
		break;
	}
	return cRGB;
}

void Rectangle::setPosX(int x){

	posX = x;

}

void Rectangle::setPosY(int y){

	posY = y;

}

int Rectangle::getWidth(){
	return width;
}

int Rectangle::getHeight(){
	return height;
}

int Rectangle::getPosX(){
	return posX;
}

int Rectangle::getPosY(){
	return posY;
}

int Rectangle::getType(){
	return type;
}

int Rectangle::getAlpha(){

	return alpha;
}

void Rectangle::setAlpha(int nalpha){

	alpha = nalpha;

}



