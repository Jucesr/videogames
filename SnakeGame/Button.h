#ifndef BUTTON_H
#define BUTTON_H

#include "GraphicElement.h"

//This class is used to represent a graphic button. Inherits from GraphicElement in order to get his behavior
//Default colors.
//BLACK -> OFF
//RED   -> OVER
//GREEN -> CLICK
//BLUE  -> ON
enum buttonState{
	BUTTON_STATE_OVER,
	BUTTON_STATE_CLICK_DOWN,
	BUTTON_STATE_ON,
	BUTTON_STATE_OFF
};

class Button : public GraphicElement{

private:

	int state;

public:

	Button(int positionX, int positionY, std::string text, int fontSize, SDL_Renderer* renderer);
	~Button();

	//Change the state of the button if is necessary
	void handle_event(SDL_Event* e);

	//Check if the button is pressed
	int getState();

	//These methods need to be over-written (polymorphism)
	void render();
	int getType();
};

#endif