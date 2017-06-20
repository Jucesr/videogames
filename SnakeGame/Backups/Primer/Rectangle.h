#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <SDL.h>


class Rectangle{

public:
	//Constructor
	Rectangle();
	Rectangle(int r, int c, int width, int height, int border,std::string ncolor, int type);
	
	//Getters and Setters
	int getWidth();
	int getHeight();
	int getRow();
	int getCol();
	int getType();

	//Used to determinated the kind of rectangle for snake game (head,body,wall,food)
	int type;

	void setRow(int);
	void setCol(int);
	void setXPosition(int);
	void setYPosition(int);
	void setRectangle(int r, int c, int width, int height , int nborder, std::string ncolor, int type);

	//Render on the screen
	void render(SDL_Renderer* renderer);

private:
	//Position
	int row;
	int col;

	int width;
	int height;
	int border;
	std::string color;

	//This function is used to convert the string color to real hex color.
	struct RGBColor getColor();


};

#endif