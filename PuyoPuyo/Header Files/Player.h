#ifndef PLAYER_H
#define PLAYER_H

#include "Puyo.h"


/*
	Player class is used to represent the Pair of puyos when they are falling down. It handles its movement.
*/

enum KeyControl{
	KEY_RIGHT,
	KEY_LEFT,
	KEY_DOWN,
	KEY_R,
	KEY_TOTAL,
	KEY_P
};

enum PuyosState{
	COMPLETE,
	ONLY_HEAD,
	ONLY_TAIL,
	NONE
};


struct direction{
	int xDir;
	int yDir;
};

struct position{
	int x;
	int y;
};

const int LIMIT_MOVEMENT = 4;

class Player{

public:
	//Constructors
	Player(int nheadStartX, int nheadStartY, int npuyoWidth, int npuyoHeight,  Texture* puyoSprite, int xrenderOffset = 0, int yrenderOffset = 0);

	//Destructor
	~Player();
	void freePlayer();

	//Create a pair of puyos
	void createPuyo();

	//Render everthing that has to do with the player
	void render( SDL_Renderer* renderer );
	int xrenderOffset;
	int yrenderOffset;

	//Handle the events related to the player. In this case only the keyboard inputs
	void handle(bool invertMode);

	//Remove puyo parts and change falling speed.
	void cutHead();
	void cutTail();
	
	//Setters
	void setHeadPositionX(int);
	void setHeadPositionY(int);
	void setTailPositionX(int);
	void setTailPositionY(int);
	void setSpeed(int x, int y, int rot);
	void setPuyoState(int);

	//Getters
	Puyo* getPuyoHead();
	Puyo* getPuyoTail();
	position getHeadPosition();
	position getHeadPrevPosition();
	position getTailPosition();
	position getTailPrevPosition();
	int getPuyoState();

	void moveHorizontal(Uint32 time);
	void moveDown(Uint32 time, bool invert = false);
	void rotate(Uint32 time);

	void setStartPosition(int startPx, int startPy);

private:

	//Puyo variables
	Puyo* puyoHead ;
	Puyo* puyoTail ;
	int puyoState;
	int puyoHeight;
	int puyoWidth;
	int startPositionX;
	int startPositionY;
	position headPrevPosition;
	position tailPrevPosition;
	Texture* puyoSprite;

	//Player speed variables
	int x_speed;
	int y_speed;
	int rotation_speed;
	int y_speed_fast;
	int y_speed_normal;
	int x_speed_fast;
	int x_speed_normal;
	int acceleration;

	//Player flags
	bool hasMovedHorizontal;
	bool hasMovedVertical;
	bool hasRotated;
	bool moveFast;
	bool keyState[KEY_TOTAL];
	bool freeFalling;

	bool stopPlayer;

	//Queue rotation movement variables
	direction nextRotation;
	direction rotationQueue[LIMIT_MOVEMENT];
	int topRotationQueue;
	int currentRecordRotationQueue;

	//Queue left-right movement variables
	direction currentDirection;
	direction movesQueue[LIMIT_MOVEMENT];
	int topMovesQueue;
	int currentRecordMovesQueue;

	//Move helper functions
	void movePuyosVertical(int yHead,int yTail);
	void movePuyosHorizontal(int xHead, int xTail);


	

	
	
};

#endif