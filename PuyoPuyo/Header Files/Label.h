#ifndef LABEL_H
#define LABEL_H

#include "GraphicElement.h"

//This class is used to represent a graphic label. Inherits from GraphicElement in order to get his behavior

class Label: public GraphicElement {

public:

	Label(int positionX, int positionY, std::string text, int fontSize, SDL_Renderer* renderer);
	~Label();

	//These methods need to be over-written (polymorphism)
	void render();
	int getType();
	
};


#endif