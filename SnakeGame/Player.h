#ifndef PLAYER_H
#define PLAYER_H

#include "Snake.h"



/*
	This class is used to represent a player in the snake game, It handles everthing that has to do with the player. 
	I decided to create this class after having problems with keyboard inputs for the snake. I realize that it's easier
	to have a class that controls only one player, in this way you can have 2 or more players.

	PLEASE READ THE FOLLOWING INFORMATION, IT IS IMPORTANT.

	This is used to control the movement of the snake related to the logic of this program.

	I coded that the snake will move towards whatever the current direction is and when a key is pressed this current dirrection 
	will change. Because of the logic of the snake game if the snake is moving to the RIGHT the current direction can't change 
	to LEFT, first it has to be changed to UP or DOWN. It also applies in the other way around, if it is moving to the LEFT 
	it can't change to the RIGHT. Same happens with UP and DOWN. In this case we need a way to prevent this. That is what the 
	"currentDirection" int variable is for.
	
	The snake has to move a single square every X seconds depending on the level (easy, normal, hard..). We have to decided when 
	to get the current direction, it could be whether a frame is render (every time the snake and everything else is render) or 
	every time the snake moves.

	NOTE: The method that I used to get the current direction uses the SDL function that get the keyboard state. This means that
	a key has to be pressed to get a TRUE value when it is called.
		
	Let's take a look of this scenario.

	The snake is moving to the right and it moves a square every 1 second (Slow speed).
	Let's supposes that we are getting the current direction every time a frame is render .
	Then the user presses UP and Left almost at the same time. What would it happen ?
	What would happen is that the snake will only move to the left. Let's see why. 

	When the user presses the UP key the current direction will change to UP but since we are moving the snake every 1 second
	the snake will not move until 1 second has passed, in the other hand the current direction will change every time a frame is
	render (it could be thousands of frames rendered in a second). I said the user pressed the left key right away so the current 
	direction will change to LEFT before the snake even moves.

	Notice that this won't happend if we change the speed of the snake. If the speed of the snake is faster than user's speed of
	pressing keys this problem is solved. Of course this is not ideal.

	One idea that I came up with (and pretty ovbious I think) is keeping these key presses in a queue so no matter how fast or slow the
	user presses a key it will store it in the queue. There is a problem with this solution though. I said we are getting  the current
	direction evey time a frame is rendered and also I said the method that I used is returning a true while a key is pressed. This means
	that the user would have to be faster enought to press and release the key before the method get executed again to store just 1 movement.

	Being aware of the previous information we need a way of getting just 1 movement until the user releases the key. In fact we need to have 
	a flag for every key that controls the snake, that is what the array of booleans is for "keyState[KEY_TOTAL]". It keeps the state of each key
	whether it has been pressed or it has been released. It is an array because sometimes the user wants to press another key without releasing the 
	one that is pressing already.

	After all of this, there is still a slight problem which is when the snake speed is super slow the user may make a bunch of movement and overfill
	the queue or make the snake move for a while even when the user is not pressing any key. That is why we have to set a limit in this case it is
	called LIMIT_MOVEMENT.

	I hope I have explained myself very clearly. I know there are other approaches to solve this problem but this is the one that I came up with.	

	
*/

enum KeyControl{
	KEY_UP,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_DOWN,
	KEY_TOTAL,
};

struct direction{
	int xDir;
	int yDir;
};

const int LIMIT_MOVEMENT = 7;


class Player{

public:
	//Constructors
	Player();
	Player(int nsnakeLenght, int npartWidth, int npartHeight, int nheadStartX, int nheadStartY, int colorHead, int colorBody);

	//Destructor
	~Player();
	void freePlayer();

	///Set the snake. In case we want to change the snake or we create an empty player
	void setSnake(Snake* mainSnake);

	//Get the current snake to the player
	Snake* getSnake();

	//Render everthing that has to do with the player
	void render( SDL_Renderer* renderer );

	//Move the snake through the grid.
	void Player::move();

	//Handle the events related to the player. In this case only the keyboard inputs
	void handle();

	//Increase the lenght of the snake and its score
	void hasEaten(int positionX, int positionY);

	//Get the head position
	int getHeadPositionX();
	int getHeadPositionY();

	//Get the tail position
	int getTailPositionX();
	int getTailPositionY();

	//Change the opacity of the player
	void setOpacity(int opacity);

	int getScore();

private:
	//The snake that is gonna appear on the screen
	Snake* mainSnake;

	//The score of the player
	int score;

	//The current direction of the snake (RIGHT, UP, LEFT, DOWN)
	int currentDirection;

	//Read information above to understand the following variables
	bool keyState[KEY_TOTAL];
	direction movesQueue[LIMIT_MOVEMENT];
	direction currentMove;
	int top;
	int currentRecord;
	
};

#endif