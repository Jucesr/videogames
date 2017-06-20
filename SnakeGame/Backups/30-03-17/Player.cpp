//*************** Player Class ***************
#include "Player.h"

Player::Player(){

	score = 0;
	mainSnake = NULL;
	top = 0;
	currentRecord = 0;
	currentMove.xDir = 1;
	currentMove.yDir = 0;
	currentDirection = SDL_SCANCODE_RIGHT;
}

Player::Player(int nsnakeLenght, int npartWidth, int npartHeight, int nheadStartX, int nheadStartY, int colorHead, int colorBody){
	mainSnake = new Snake(nsnakeLenght,npartWidth,npartHeight,nheadStartX,nheadStartY,colorHead,colorBody);
	score = 0;
	top = 0;
	currentRecord = 0;
	currentMove.xDir = 1;
	currentMove.yDir = 0;
	currentDirection = SDL_SCANCODE_RIGHT;
}

void Player::setSnake(Snake* mainSnake){
	Player::mainSnake = mainSnake;
}

Snake* Player::getSnake(){

	return Player::mainSnake;

}

void Player::render( SDL_Renderer* renderer ){

	mainSnake->render(renderer);

}

void Player::move(){

	//NOTE: To understand better how this method works please read the information that is at the top of the player.h file.

	//Check if there is an element in the queue
	if( currentRecord < top ){

		//Get the element and go to the next elment in the queue
		currentMove.xDir = movesQueue[currentRecord].xDir;
		currentMove.yDir = movesQueue[currentRecord].yDir;
		currentRecord ++;

	}else{

		// There was no move, the direction has't changed. Reset queue

		top = 0;
		currentRecord = 0;

	}

	mainSnake->move( currentMove.xDir, currentMove.yDir);

}

void Player::freePlayer(){
	mainSnake->freeSnake();
}

Player::~Player(){
	freePlayer();
}

void Player::handle(){

	//NOTE: To understand better how this method works please read the information that is at the top of the player.h file.

	//Get current keystate
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	//If the user is pressing the right key and Is not moving to the left
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] && currentDirection != SDL_SCANCODE_LEFT ){

		// And is the first time since the user pressed the key.
		if (!keyState[KEY_RIGHT]){
						
			//Change the current direction
			currentDirection = SDL_SCANCODE_RIGHT;

			//Add the movement to the queue if is below the limit

			if ( top < LIMIT_MOVEMENT ){

				movesQueue[top].xDir = 1;
				movesQueue[top].yDir = 0;
				top++;

			}

			//It states that the key has been pressed for the first time. I will change until all key are released.
			keyState[KEY_RIGHT] = true;
		}
						

	}else if( currentKeyStates[ SDL_SCANCODE_LEFT ] && currentDirection != SDL_SCANCODE_RIGHT ){

		if (!keyState[KEY_LEFT]){

			if ( top < LIMIT_MOVEMENT ){

				currentDirection = SDL_SCANCODE_LEFT;
				movesQueue[top].xDir = -1;
				movesQueue[top].yDir = 0;
				top++;

			}

			
			keyState[KEY_LEFT] = true;
		}
					
	}else if( currentKeyStates[ SDL_SCANCODE_UP ] && currentDirection != SDL_SCANCODE_DOWN){

		if (!keyState[KEY_UP]){

			if ( top < LIMIT_MOVEMENT ){

				currentDirection = SDL_SCANCODE_UP;
				movesQueue[top].xDir = 0;
				movesQueue[top].yDir = -1;
				top++;
			}

		keyState[KEY_UP] = true;
		}
					
	}else if( currentKeyStates[ SDL_SCANCODE_DOWN ] && currentDirection != SDL_SCANCODE_UP ){

		if (!keyState[KEY_DOWN]){

			if ( top < LIMIT_MOVEMENT ){

				currentDirection = SDL_SCANCODE_DOWN;
				movesQueue[top].xDir = 0;
				movesQueue[top].yDir = 1;

				top++;

			}
			keyState[KEY_DOWN] = true;
		}
					
	}else{

		// All key are released.

		keyState[KEY_UP] = false;
		keyState[KEY_DOWN] = false;
		keyState[KEY_RIGHT] = false;
		keyState[KEY_LEFT] = false;
	}
}

int Player::getHeadPositionX(){
	
	return mainSnake->getHeadPositionX();

}

int Player::getHeadPositionY(){
	
	return mainSnake->getHeadPositionY();

}

int Player::getTailPositionX(){
	
	return mainSnake->getTailPositionX();

}

int Player::getTailPositionY(){
	
	return mainSnake->getTailPositionY();

}

void Player::hasEaten(int positionX, int positionY){

	mainSnake->increaseLenght(positionX, positionY);

}