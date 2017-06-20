#include "../Header Files/Entity.h"

int Entity::getType(){

	return type;

}

int Entity::getPosX(){

	return posX;

}

int Entity::getPosY(){

	return posY;

}


void Entity::setType(int nType){

	type = nType;

}

void Entity::setPosX(int nPosX){

	posX = nPosX;

}

void Entity::setPosY(int nPosY){

	posY = nPosY;

}

void Entity::setState(bool s){

	state = s;

}

bool Entity::getState(){

	return state;
}
