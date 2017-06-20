#ifndef MENU_H
#define MENU_H

#include "GameState.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "SDL_ttf.h"

class Menu : public GameState{

private:
	
	//Media resources for menu
	SDL_Renderer* renderer;


	TTF_Font *fontTitle;
	TTF_Font *fontButton;
	SDL_Color textColor;

	SDL_Texture* bigTitle;
	SDL_Texture* btn_play;
	SDL_Texture* btn_scores;
	SDL_Texture* btn_credits;


public:
    Menu();
    ~Menu();

	// Game states inherited functions 
	void handle_events();
    void logic();
    void render();
};

#endif