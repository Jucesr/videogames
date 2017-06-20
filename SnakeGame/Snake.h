#ifndef SNAKE_H
#define SNAKE_H

/* 
	Snake class is used to represent a graphic snake. 
	The snake class is just a doubly linked list since we don't know the maximum number of body parts.
*/

#include "Rectangle.h"

//This struct is used to represent each part of the snake. It has a reference to the next part.
struct SnakePart{
	Rectangle* part;
	SnakePart* next;
	SnakePart* prev;
};

class Snake{

public:
	//Constructor
	Snake();
	Snake(int snakeLenght, int partWidth, int partHeight, int headStartX, int headStartY, int colorHead, int colorBody);

	//Destructor
	~Snake();

	//Add a snake part to the end of the list
	void addSnakePart(Rectangle* part);

	//Render each element of the snake
	void render( SDL_Renderer* renderer );

	//Frees snake
	void freeSnake();

	//Moves the snake one place towards ( x + xDir), (y + yDir )
	void move(int xDir, int yDir);

	//Get the head position
	SnakePart* getHead();

	//Get the tail position
	SnakePart* getTail();

	//Get the head position
	int getHeadPositionX();
	int getHeadPositionY();

	//Get the tail position
	int getTailPositionX();
	int getTailPositionY();

	//Add a new body part to the tail
	void increaseLenght(int positionX, int positionY);

	//Change the opacity of the snake
	void setOpacity(int opacity);


private:

	int snakeLength;
	SnakePart* head;
	SnakePart* tail;

};


#endif