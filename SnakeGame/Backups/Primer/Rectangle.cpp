#include "Rectangle.h"

struct RGBColor{

	Uint8 red;
	Uint8 blue;
	Uint8 green;
	Uint8 alpha;

};

Rectangle::Rectangle(){
	//Just to create the array
}

Rectangle::Rectangle(int c, int r, int nwidth, int nheight, int nborder , std::string ncolor, int ntype){

	width = nwidth;
	color = ncolor;
	height = nheight;
	border = nborder;
	row = r;
	col = c;
	type =ntype; 

}

void Rectangle::setRectangle(int c, int r, int nwidth, int nheight, int nborder, std::string ncolor , int ntype){
	width = nwidth;
	color = ncolor;
	height = nheight;
	border = nborder;
	row = r;
	col = c;
	type =ntype;
}

void Rectangle::render(SDL_Renderer* gRenderer){


	bool suc = true;

	//Draw the fill rectangle
	SDL_Rect fill = { col*width + border, row*height + border, width - border*2, height - border*2 };
	RGBColor cRGB = getColor();
	SDL_SetRenderDrawColor( gRenderer, cRGB.red, cRGB.green, cRGB.blue, cRGB.alpha );		
	SDL_RenderFillRect( gRenderer, &fill );


	//Draw the border
	for (int i = 0; i < border-1; i++)
	{
	SDL_Rect border = { col*width+i, row*height+i, width-i*2, height-i*2};
	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );		
	SDL_RenderDrawRect( gRenderer, &border);
	
	}


}

RGBColor Rectangle::getColor(){

	RGBColor cRGB;

	if (std::strcmp(color.c_str(), "red") == 0) 
	{
		cRGB.red = 255;
		cRGB.green = 0;
		cRGB.blue = 0;
		cRGB.alpha = 255;

	} 
	else if (std::strcmp(color.c_str(), "green") == 0) 
	{
		cRGB.red = 0;
		cRGB.green = 255;
		cRGB.blue = 0;
		cRGB.alpha = 255;
	}
	else if (std::strcmp(color.c_str(), "blue") == 0) 
	{
		cRGB.red = 0;
		cRGB.green = 0;
		cRGB.blue = 255;
		cRGB.alpha = 255;
	}
	else{
		cRGB.red = 0;
		cRGB.green = 0;
		cRGB.blue = 0;
		cRGB.alpha = 255;
	}

	return cRGB;
}

void Rectangle::setRow(int r){

	row = r;

}

void Rectangle::setCol(int c){

	col = c;

}

int Rectangle::getWidth(){
	return width;
}

int Rectangle::getHeight(){
	return height;
}

int Rectangle::getRow(){
	return row;
}

int Rectangle::getCol(){
	return col;
}

int Rectangle::getType(){
	return type;
}



