#ifndef GAMESTATE_MENU_H
#define GAMESTATE_MENU_H

#include "GameState.h"
#include "Label.h"
#include "Button.h"

class Menu : public GameState{

private:

	int screen_width;
	int screen_height;
	SDL_Renderer* renderer;

	//Elements for the Menu
	Button* btn_play;
	Button* btn_scores;
	Button* btn_credits;

	Label* lbl_Title01;
	Label* lbl_Title02;
	Label* lbl_Title03;
	
	//Event handler
	SDL_Event e;


public:
    Menu(int screen_width, int screen_height, SDL_Renderer* renderer);
    ~Menu();

	// Game states inherited functions 
	void handle_events();
    void logic();
    void render();
	bool getError();
};

#endif