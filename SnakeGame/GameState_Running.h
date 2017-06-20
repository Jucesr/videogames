#ifndef GAMESTATE_RUNNING_H
#define GAMESTATE_RUNNING_H

#include "GameState.h"
#include "Player.h"
#include "Grid.h"
#include "Timer.h"
#include "Button.h"
#include "Label.h"
#include "TextBox.h"
#include "ScoreRecord.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <SDL_mixer.h>

//Game constants
#define ROWS 12
#define COLUMNS 12
#define SNAKE_LENGTH 3

//This class is where the snake game logic is. I divied this state into sub-states because it's easier to read the code.


//Used to represent the an embedded state of the game and know what to render/handle/proccess.
enum GAMESTATE{
	START,
	SET_DIFFICULTY,
	RUN,
	GET_SCORE,
	GAMEOVER
};

class GameRunning : public GameState{

private:
	int screen_width;
	int screen_height;
	
	//Elements for the game
	SDL_Renderer* renderer;
	Grid* mainGrid;
	Button* btn_again;
	Button* btn_menu;
	Button* btn_easy;
	Button* btn_medium;
	Button* btn_hard;
	Label* lbl_score;
	Label* lbl_start;
	TextBox* txtName;
	Label* lblName;
	std::string start_messages[5];
	int animationFrame;
	int animationSpeed;
	std::string difficultyLevel;


	// Snake parts
	int snakeWitdth;
	int snakeHeight;
	int headStartRow;
	int headStartCol;

	Player* player1;

	int playerHeadPositionX;
	int playerHeadPositionY;
	int playerTailPositionX;
	int playerTailPositionY;
			
	//Event handler
	SDL_Event e;

	//This variable is used to control the movement speed and is in miliseconds;
	int speedRate;		

	// Game process flags
	bool isThereFood;
	int gameState;
	// Used to only execute once the code that is inside of the speedrate IF (sometimes the code get executed more than one time in a milisecond)
	bool hasExecuted;
	bool hasTypedName;

	//Used to represent the wall
	Rectangle* wall_bot[COLUMNS + 2];
	Rectangle* wall_top[COLUMNS + 2];
	Rectangle* wall_left[ROWS + 2];
	Rectangle* wall_right[ROWS + 2];

	//Used to represent a piece of food
	Rectangle* food; 

	//The music that will be played
	Mix_Music *mainMusic;

	//The sound effects that will be used
	Mix_Chunk *gameoverEffect;
	Mix_Chunk *snakeEat;

	//The frames per second timer
	Timer fpsTimer;

	//The file that store the score records
	ScoreRecord* scores;

	//Controls the music background
	void playMusic();
	void stopMusic();
	bool loadMedia();

	//Check if the head is inside the grid
	bool isHeadInside(int limitX, int limitY, int x, int y);

	//Creates a piece of food in a random position.
	void createFood();

	//Finish the game
	void fgameover();

	void renderWall();

	void readScoreRecords();

	//Sub states logic
	void startLogic();
	void set_difficultyLogic();
	void runLogic();
	void get_scoreLogic();
	void gameoverLogic();

	


public:
    GameRunning(int screen_width, int screen_height, SDL_Renderer* renderer);
    ~GameRunning();

	// Game states inherited functions 
	void handle_events();
    void logic();
    void render();
	bool getError();
};

#endif