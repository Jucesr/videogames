#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "GraphicElement.h"

class TextBox : public GraphicElement{

private:

	bool hasValidText;
	bool focus;
	bool updateText;

public:

	TextBox(int positionX, int positionY, std::string text, int fontSize, SDL_Renderer* renderer);
	~TextBox();
	//Change the state of the button if is necessary
	void handle_event(SDL_Event* e);

	//Check if the button is pressed
	int getState();

	//These methods need to be over-written (polymorphism)
	void render();
	int getType();
	bool getFocus();
	bool isValid();
};

#endif