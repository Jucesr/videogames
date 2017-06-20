#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include "Texture.h"

//This class is the base class to create elements like Labels, Buttons, TextBoxes, etc.

enum elementType{
	ELEMENT_LABEL,
	ELEMENT_BUTTON,
	ELEMENT_TEXT_BOX
};

class GraphicElement{

protected:
	Texture* graphicText;
	std::string text;
	SDL_Color textColor;
	TTF_Font* textFont;

	int positionX;
	int positionY;
	int width;
	int height;

public:

	//Shared methods
	int getWidth();
	int getHeight();
	int getPositionX();
	int getPositionY();


	std::string getText();
	
	void setPosition(int x, int y);

	void setFontColor(int r, int g, int b);
	void setFontSize(int size);
	void setText(std::string text);

	//These methods need to be over-written (polymorphism)
	virtual void render() = 0;
	virtual int getType() = 0;

};


#endif