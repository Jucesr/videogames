#ifndef GAMESTATE_CREDITS_H
#define GAMESTATE_CREDITS_H

#include "GameState.h"
#include "Label.h"
#include "Button.h"

class Credits : public GameState{

private:

	int screen_width;
	int screen_height;
	SDL_Renderer* renderer;
	//Event handler
	SDL_Event e;

	//Elements for the Menu
	Button* btn_menu;

	Label* lbl_Author;
	Label* txt_Author;

	Label* lbl_Title;
	Label* txt_Title;

	Label* lbl_Date;
	Label* txt_Date;

	Label* lbl_Contact;
	Label* txt_Contact;

	Label* lbl_Text01;
	Label* lbl_Text02;
	Label* lbl_Text03;
	Label* lbl_Text04;
	Label* lbl_Text05;


public:
    Credits(int screen_width, int screen_height, SDL_Renderer* renderer);
    ~Credits();

	// Game states inherited functions 
	void handle_events();
    void logic();
    void render();
	bool getError();

};


#endif