#ifndef GAMESTATE_SCORES_H
#define GAMESTATE_SCORES_H

#define TOTAL_SCORES 10

#include "GameState.h"
#include "Label.h"
#include "Button.h"
#include "ScoreRecord.h"

class Scores : public GameState{

private:

	int screen_width;
	int screen_height;
	SDL_Renderer* renderer;
	//Event handler
	SDL_Event e;

	//The file that store the score records
	ScoreRecord* scores;

	//Elements for the Menu
	Button* btn_menu;

	Label* lbl_Position;
	Label* lbl_Name;
	Label* lbl_Score;
	Label* lbl_Dificulty;

	Label* txt_Position[ TOTAL_SCORES ];
	Label* txt_Name[ TOTAL_SCORES ];
	Label* txt_Score[ TOTAL_SCORES ];
	Label* txt_Dificulty[ TOTAL_SCORES ];


public:
    Scores(int screen_width, int screen_height, SDL_Renderer* renderer);
    ~Scores();

	// Game states inherited functions 
	void handle_events();
    void logic();
    void render();
	bool getError();

};

#endif