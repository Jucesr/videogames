//*************** Player Class ***************
#include "../Header Files/Player.h"


Player::Player(int nheadStartX, int nheadStartY, int npuyoWidth, int npuyoHeight, Texture* npuyoSprite , int nxrenderOffset, int nyrenderOffset){
	puyoHeight = npuyoHeight;
	puyoWidth = npuyoWidth;
	startPositionX = nheadStartX;
	startPositionY = nheadStartY;
	puyoSprite = npuyoSprite;
	xrenderOffset = nxrenderOffset;
	yrenderOffset = nyrenderOffset;
	topMovesQueue = 0;
	topRotationQueue = 0;
	currentRecordMovesQueue = 0;
	currentRecordRotationQueue = 0;
	acceleration = 0;
	moveFast = false;
	currentDirection.xDir = 0;
	currentDirection.yDir = 1;
	keyState[KEY_R] = false;
	keyState[KEY_LEFT] = false;
	keyState[KEY_RIGHT] = false;
	freeFalling = false;
	createPuyo();
}

void Player::createPuyo(){

	int randomPuyoType;

	randomPuyoType = rand() % PUYO_TOTAL;
	puyoHead = new Puyo(startPositionX, startPositionY, puyoWidth, puyoHeight, randomPuyoType, puyoSprite, xrenderOffset, yrenderOffset);

	randomPuyoType = rand() % PUYO_TOTAL;
	puyoTail = new Puyo(startPositionX, startPositionY - 1, puyoWidth, puyoHeight, randomPuyoType, puyoSprite, xrenderOffset, yrenderOffset);
	
	headPrevPosition.x = startPositionX;
	headPrevPosition.y = startPositionY;

	tailPrevPosition.x = startPositionX;
	tailPrevPosition.y = startPositionY - 1;

	puyoState = COMPLETE;

}

void Player::render( SDL_Renderer* renderer ){

	puyoHead->render();
	puyoTail->render();


}

void Player::setSpeed(int x, int y, int rot){

	x_speed = x;
	y_speed = y;
	rotation_speed = rot;

	y_speed_normal = y;
	y_speed_fast = y/10;

	x_speed_normal = x;
	x_speed_fast = x/2;

}

void Player::moveHorizontal(Uint32 time){

	//This if control the movement speed. Only got executed every (x_speed) miliseconds
	if( time % x_speed == 1 && hasMovedHorizontal == false )
	{

		//If movefast mode is activated.
		if ( moveFast ){

			movePuyosHorizontal(puyoHead->getPosX() + currentDirection.xDir, puyoTail->getPosX() + currentDirection.xDir);

			/*puyoHead->setPosX(puyoHead->getPosX() + currentDirection.xDir);
			puyoTail->setPosX(puyoTail->getPosX() + currentDirection.xDir);*/

		}else{

			//Check if there is an element in the queue
			if( currentRecordMovesQueue < topMovesQueue ){

				//Get the element and go to the next elment in the queue
				currentDirection.xDir = movesQueue[currentRecordMovesQueue].xDir;
				currentDirection.yDir = movesQueue[currentRecordMovesQueue].yDir;
				currentRecordMovesQueue ++;

				movePuyosHorizontal(puyoHead->getPosX() + currentDirection.xDir, puyoTail->getPosX() + currentDirection.xDir);


			}else{

				// There was no move, the direction has't changed. Reset queue
				topMovesQueue = 0;
				currentRecordMovesQueue = 0;

			}


		}

	//This flag is used to prevent the code above to get executed more than once in a milisecond	
	hasMovedHorizontal = true;
	}else if ( time % x_speed != 1 ) 
	{
		//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond
		hasMovedHorizontal = false;
	}

}

void Player::moveDown(Uint32 time, bool invert){

	//This if control the movement speed. Only got executed every (y_speed) miliseconds
	if( time % y_speed == 1 && hasMovedVertical == false )
	{		
		if (invert == true){
			
			movePuyosVertical(puyoHead->getPosY() - 1, puyoTail->getPosY() - 1);

		}else{

			movePuyosVertical(puyoHead->getPosY() + 1, puyoTail->getPosY() + 1);

		}

	//This flag is used to prevent the code above to get executed more than once in a milisecond	
	hasMovedVertical = true;
	}else if ( time % y_speed != 1 ) 
	{
		//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond
		hasMovedVertical = false;
	}

}

void Player::rotate(Uint32 time){

	//This if control the movement speed. Only got executed every (rotation_speed) miliseconds
	if( time % rotation_speed == 1 && hasRotated == false )
	{		


		//Check if there is an element in the queue
		if( topRotationQueue > 0 && currentRecordRotationQueue < topRotationQueue){

			//Get the element and go to the next elment in the queue
			nextRotation.xDir = rotationQueue[currentRecordRotationQueue].xDir;
			nextRotation.yDir = rotationQueue[currentRecordRotationQueue].yDir;
			currentRecordRotationQueue ++;

			movePuyosVertical( puyoHead->getPosY(), puyoHead->getPosY() + nextRotation.yDir);
			movePuyosHorizontal(puyoHead->getPosX(), puyoHead->getPosX() + nextRotation.xDir);


		}else{

			// There was no rotation. Reset queue

			topRotationQueue = 0;
			currentRecordRotationQueue = 0;

		}

	//This flag is used to prevent the code above to get executed more than once in a milisecond	
	hasRotated = true;
	}else if ( time % y_speed != 1 ) 
	{
		//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond
		hasRotated = false;
	}

}

void Player::freePlayer(){
	//mainSnake->freeSnake();
}

Player::~Player(){
	freePlayer();
}

void Player::handle(bool invertMode){

	//Get current keystate
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	//-----------Move control-------------------

	//If the user is pressing the right key
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ){

		// It is the first time the user presses the key.
		if (!keyState[KEY_RIGHT]){

		//Add the movement to the queue if is below the limit

			if ( topMovesQueue < LIMIT_MOVEMENT ){

				movesQueue[topMovesQueue].xDir = 1;
				movesQueue[topMovesQueue].yDir = 0;
				topMovesQueue++;

			}

			//It states that the key has been pressed for the first time. I will change until all key are released.
			keyState[KEY_RIGHT] = true;

		// if the user keep presing the right key
		}else{

			acceleration ++;

			if ( acceleration >2000 ){

				moveFast = true;
				currentDirection.xDir = 1;
				currentDirection.yDir = 0;
				acceleration = 0;
				x_speed = x_speed_fast;

			}

		}

	}else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ){

		// It is the first time the user presses the key.
		if (!keyState[KEY_LEFT]){

		//Add the movement to the queue if is below the limit

			if ( topMovesQueue < LIMIT_MOVEMENT ){

				movesQueue[topMovesQueue].xDir = -1;
				movesQueue[topMovesQueue].yDir = 0;
				topMovesQueue++;

			}

			//It states that the key has been pressed for the first time. I will change until all key are released.
			keyState[KEY_LEFT] = true;

		// if the user keep presing the right key
		}else{

			acceleration ++;

			if ( acceleration > 2000 ){

				//Activate fast mode
				moveFast = true;
				currentDirection.xDir = -1;
				currentDirection.yDir = 0;
				acceleration = 0;
				x_speed = x_speed_fast;

			}

		}
					
	}else if( currentKeyStates[ SDL_SCANCODE_DOWN ]  ){

		if( !invertMode ){
			currentDirection.xDir = 0;
			currentDirection.yDir = 1;
			y_speed = y_speed_fast;

		}

	}else if( currentKeyStates[ SDL_SCANCODE_UP ]  ){

		if( invertMode ){
			currentDirection.xDir = 0;
			currentDirection.yDir = 1;
			y_speed = y_speed_fast;

		}

	}else{

		// All key are released.
		keyState[KEY_RIGHT] = false;
		keyState[KEY_LEFT] = false;
		moveFast = false;
		acceleration = 0;

		if( freeFalling == false ){
			x_speed = x_speed_normal;
			y_speed = y_speed_normal;
		}

		//Set current direction down.
		currentDirection.xDir = 0;
		currentDirection.yDir = 1;

	}


	//---------Rotation control---------------

	if( currentKeyStates[ SDL_SCANCODE_R ] ){

		if ( !keyState[KEY_R] && topRotationQueue < LIMIT_MOVEMENT){

			int tX = puyoTail->getPosX();
			int tY = puyoTail->getPosY();
			int hX = puyoHead->getPosX();
			int hY = puyoHead->getPosY();

			if( tX == hX )
			{
			
				if( tY < hY )
				{
					rotationQueue[topRotationQueue].yDir = 0;
					rotationQueue[topRotationQueue].xDir = 1;
					topRotationQueue++;

				}else
				{
					rotationQueue[topRotationQueue].yDir = 0;
					rotationQueue[topRotationQueue].xDir = -1;
					topRotationQueue++;
				}

			}else
			{
				if( tX > hX )
				{
					rotationQueue[topRotationQueue].xDir = 0;
					rotationQueue[topRotationQueue].yDir = 1;
					topRotationQueue++;

				}else
				{
					rotationQueue[topRotationQueue].xDir = 0;
					rotationQueue[topRotationQueue].yDir = -1;
					topRotationQueue++;

				}

			}


		keyState[KEY_R] = true;
		}

	}else{

		keyState[KEY_R] = false;

	}


	// Pause control

	//---------Rotation control---------------

	if( currentKeyStates[ SDL_SCANCODE_P ] ){

		if ( !keyState[KEY_P] ){

			if(stopPlayer)
				stopPlayer = false;
			else
				stopPlayer = true;

			keyState[KEY_P] = true;

		}else{
			keyState[KEY_P] = false;
		}

	}


}

position Player::getHeadPosition(){
	
	position help;
	help.x = puyoHead->getPosX();
	help.y = puyoHead->getPosY();
	return help;

}

position Player::getTailPosition(){
	
	position help;
	help.x = puyoTail->getPosX();
	help.y = puyoTail->getPosY();
	return help;

}

position Player::getHeadPrevPosition(){
	
	return headPrevPosition;

}

position Player::getTailPrevPosition(){
	
	return tailPrevPosition;

}

void Player::setHeadPositionX(int x){

	puyoHead->setPosX(x);

}

void Player::setHeadPositionY(int y){

	puyoHead->setPosY(y);

}

void Player::setTailPositionX(int x){

	puyoTail->setPosX(x);

}

void Player::setTailPositionY(int y){

	puyoTail->setPosY(y);

}

Puyo* Player::getPuyoHead(){

	return puyoHead;

}

Puyo* Player::getPuyoTail(){

	return puyoTail;

}

void Player::movePuyosVertical(int yHead,int yTail){

	if( puyoState == COMPLETE ){

		//Save previous positions
		headPrevPosition.y = puyoHead->getPosY();	
		tailPrevPosition.y = puyoTail->getPosY();

		puyoHead->setPosY(yHead);
		puyoTail->setPosY(yTail);

	}else if (puyoState == ONLY_HEAD ) {

		//Save previous positions
		headPrevPosition.y = puyoHead->getPosY();

		puyoHead->setPosY(yHead);

	}else{
		//Save previous positions
		tailPrevPosition.y = puyoTail->getPosY();

		puyoTail->setPosY(yTail);

	}

}

void Player::movePuyosHorizontal(int xHead, int xTail){
	if( puyoState == COMPLETE ){

		//Save previous positions
		headPrevPosition.x = puyoHead->getPosX();

		tailPrevPosition.x = puyoTail->getPosX();

		puyoHead->setPosX(xHead);

		puyoTail->setPosX(xTail);

	}
}

void Player::cutHead(){

	if (puyoState == COMPLETE ){

		puyoState = ONLY_TAIL;
		y_speed = y_speed_fast;
		freeFalling = true;
	
	}else{

		puyoState = NONE;
		freeFalling = false;

	}

}

void Player::cutTail(){

	if (puyoState == COMPLETE ){

	puyoState = ONLY_HEAD;
	y_speed = y_speed_fast;
	freeFalling = true;

	}else{

		puyoState = NONE;	
		freeFalling = false;

	}

}

int Player::getPuyoState(){

	return puyoState;

}

void Player::setPuyoState(int state){

	puyoState = state;

}


void Player::setStartPosition(int startPx, int startPy){

	startPositionX = startPx;
	startPositionY = startPy;

}