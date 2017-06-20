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


#include "Puyo.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <SDL_mixer.h>

//Game constants
#define ROWS 10
#define COLUMNS 12
#define XRENDEROFFSET 30
#define YRENDEROFFSET 30

//This class is where the game logic is located. I divied this state into sub-states because it's easier to read .


//Used to represent the an embedded state of the game and know what to render/handle/proccess.
enum GAMESTATE{
	START,
	RUN,
	GET_SCORE,
	GAMEOVER,
	PAUSE
};

enum PlayerName{
	PLAYER1,
	CPU
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
	Label* lbl_score;
	Label* lbl_SCPUscore;
	Label* lbl_start;
	Label* lbl_rotate;

	TextBox* txtName;
	Label* lblName;
	std::string start_messages[5];
	int animationFrame;
	int animationSpeed;

	// Puyo parts
	int puyoWitdth;
	int puyoHeight;
	int headStartRow;
	int headStartCol;

	//Player variables
	Player* player1;
	position playerHeadPosition;
	position playerTailPosition;
	int playerScore;
			
	//Event handler
	SDL_Event e;

	//This variable is used to control the movement speed and is in miliseconds;
	int speedRate;		

	// Game process flags
	int gameState;
	// Used to only execute once the code that is inside of the speedrate IF (sometimes the code get executed more than one time in a milisecond)
	bool hasExecuted;
	bool hasTypedName;

	//The texture for puyo
	Texture* puyoSprite;

	//The music and effect sounds
	Mix_Music *mainMusic;
	Mix_Chunk *gameoverEffect;
	Mix_Chunk *increaseScore;

	//The frames per second timer
	Timer fpsTimer;

	//The file that store the score records
	ScoreRecord* scores;

	//Controls the music background
	void playMusic();
	void stopMusic();
	bool loadMedia();

	void checkHeadCollition();
	void checkTailCollition();


	//Run logic helper functions
	void run_gameover();
	//Recursive function to check combionations on the grid
	void getCombination(int c, int r, int ,int, int);
	void updateGrid(int);
	void checkCombinationsInGrid(int playerName);

	//Sub states logic
	void startLogic();
	void runLogic();
	void get_scoreLogic();
	void gameoverLogic();

	//Grid status variables
	Entity* puyosTogether[ROWS*COLUMNS];
	int puyosTogetherCount;
	int puyosMovedDown;
	bool gridNeedUpdate;


	Puyo* puyoCPU;
	void movePuyoCPU();
	int puyoCPU_yspeed;
	int puyoCPU_xspeed;
	bool puyoCPUhasMoved;
	bool puyoWillMoveX;
	bool puyoHasMovedHorizontal;
	void createPuyoCPU();
	int cpuScore;

	int currentPlayerName;

	bool gamePaused;
	void invertBoard();
	int puyosMovedUp;
	bool gridIsInverting;
	bool invertMode;
	int gameOverCondition;


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