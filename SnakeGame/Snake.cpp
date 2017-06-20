//*************** Snake Class ***************
#include "Snake.h"

Snake::Snake(){
	//Empty Constructor
}

Snake::Snake(int nsnakeLenght, int npartWidth, int npartHeight, int nheadStartX, int nheadStartY, int colorHead, int colorBody){
	
	//Initialize variables.
	head = NULL;
	tail = NULL;
	snakeLength = nsnakeLenght;

	//Create and set the head of the Snake
	Rectangle* headPart = new Rectangle(nheadStartX,nheadStartY,npartWidth,npartHeight,2,colorHead,RECTANGLE_TYPE_SNAKEPART);
	addSnakePart(headPart);

	//Create and set the body parts

	for (int i = 1; i < snakeLength; i++)
	{
		Rectangle*bodyPart = new Rectangle(nheadStartX-i,nheadStartY,npartWidth,npartHeight,2,colorBody,RECTANGLE_TYPE_SNAKEPART);
		addSnakePart(bodyPart);
	}

}

Snake::~Snake(){
	freeSnake();
}

void Snake::freeSnake(){
	SnakePart* iterator = head;
	SnakePart* iteratorNext = head;

	while( iterator!= NULL ){

		//Get the next part before free the current one.
		iteratorNext = iterator->next;
		free(iterator);
		iterator = iteratorNext;
	}
}

void Snake::addSnakePart(Rectangle* part){

	SnakePart* newPart;
	newPart = (SnakePart *) malloc(sizeof (SnakePart));
	newPart->part = part;
	newPart->next = NULL;

	
	if( head == NULL ) {
		//If it is the first element of the snake
		newPart->prev = NULL;
		head = newPart;
		tail = newPart;
	}else{
		newPart->prev = tail;
		tail->next = newPart;
		tail = newPart;
	}

}

void Snake::increaseLenght(int positionX, int positionY){

	Rectangle*bodyPart = new Rectangle(positionX, positionY, tail->part->getWidth(), tail->part->getHeight(), 2, tail->part->getColor(), RECTANGLE_TYPE_SNAKEPART);
	addSnakePart(bodyPart);
	snakeLength++;

}

void Snake::render( SDL_Renderer* renderer ){

	//Used to go throw the list. It starts in the head
	SnakePart* iterator = head;

	while (iterator != NULL){

		//Get the part as a rectangle and render it
		(iterator->part)->render(renderer);

		//Go to the next part
		iterator = iterator->next;

	}
}

void Snake::move(int xDir, int yDir){

	//Used to go throw the list. It starts in the tail. 
	SnakePart* iterator = tail;
	Rectangle part;
	Rectangle prevPart;


	//Move the body

	while (iterator->prev != NULL){
		
		//We start from the tail, if we want to start from the head first we would need to save the previuos position

		//Get the part as a rectangle
		part = *(iterator->part);

		//Get the previous part of the snake
		prevPart = *(iterator->prev->part);

		//Move the current part towards where the previous part is.
		part.setPosX(prevPart.getPosX());
		part.setPosY(prevPart.getPosY());

		//Set the part with new values
		*(iterator->part) = part;

		//Go to the previous part
		iterator = iterator->prev;

	}

	//Move the head

	part = *(head->part);

	part.setPosX(part.getPosX() + xDir);
	part.setPosY(part.getPosY() + yDir);

	*(head->part) = part;

		
	
}

int Snake::getHeadPositionX(){

	return head->part->getPosX();

}

int Snake::getHeadPositionY(){

	return head->part->getPosY();

}

int Snake::getTailPositionX(){

	return tail->part->getPosX();

}

int Snake::getTailPositionY(){

	return tail->part->getPosY();

}

void Snake::setOpacity(int opacity){

	//Used to go throw the list. It starts in the head
	SnakePart* iterator = head;

	while (iterator != NULL){

		//Get the part as a rectangle and render it
		(iterator->part)->setAlpha(opacity);

		//Go to the next part
		iterator = iterator->next;

	}

}
