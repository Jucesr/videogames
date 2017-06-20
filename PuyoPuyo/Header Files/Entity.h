#ifndef ENTITY_H
#define ENTITY_H


//This class is used to represent the kind of entity that will be in the grid. Each element that will be inside the grid should inherit from this class 


class Entity{

protected:

	int type;
	int posX;
	int posY;
	//This flag becomes true when the entity is next to another entity from the same type
	bool state;

public:
    int getType();
	int getPosX();
	int getPosY();
	bool getState();
	
	void setState(bool);
	void setType(int);
	void setPosX(int);
	void setPosY(int);

	virtual void render() = 0;

};
 
#endif