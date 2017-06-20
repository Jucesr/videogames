#ifndef RECTANGLE_H
#define RECTANGLE_H

/* 
	This is the most important class in the game since it is used to any entity in the snake game
*/

#include <SDL.h>

enum PartType{

	RECTANGLE_TYPE_SNAKEPART,
	RECTANGLE_TYPE_FOOD,
	RECTANGLE_TYPE_WALL,
	RECTANGLE_TYPE_TOTAL
};

enum Color{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_BLACK,
	COLOR_TOTAL
};



class Rectangle{

public:
	//Constructor
	Rectangle();
	Rectangle(int posX, int posY, int width, int height, int border,int ncolor, int type);
	
	//Getters and Setters
	int getWidth();
	int getHeight();
	int getPosX();
	int getPosY();
	int getType();
	int getColor();
	int getAlpha();

	void setAlpha(int);
	void setPosX(int);
	void setPosY(int);
	void setRectangle(int posX, int posY, int width, int height , int nborder, int ncolor, int type);

	//Render on the screen
	void render(SDL_Renderer* renderer);

private:
	//Position
	int posX;
	int posY;

	int width;
	int height;
	int border;
	int color;
	int alpha;

	//Used to determinated the kind of rectangle for snake game (head,body,wall,food)
	int type;

	//This function is used to convert the int color to real hex color.
	struct RGBColor getRGBColor();


};

#endif