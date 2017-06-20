/*
	PLEASE READ INFORMATION INSIDE PLAYER.H FILE TO UNDERSTAND BETTER THE LOGIC OF THE PROGRAM.
*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <time.h>

//Custom classes
#include "Grid.h"
#include "Timer.h"
#include "Player.h"

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

//Snake constants
const int SNAKE_LENGTH = 5;

enum GameStates
{
    STATE_NULL,
    STATE_MENU,
    STATE_GAME_RUNNING,
    STATE_SCORES,
    STATE_EXIT,
};

enum {
	KEY_PRESSED_RIGHT,
	KEY_PRESSED_LEFT,
	KEY_PRESSED_UP,
	KEY_PRESSED_DOWN,
	KEY_PRESSED_TOTAL
};


// This is used to represent a new direction to the snake. Each member can only hava a value of -1, 0 or 1.
// Sometimes the user presses the keys faster than the snake's speed and since I am getting the next direction every frame I could lose some direction.
// The solution I came with was putting the new direction in a linked list so I won't lose any key pressed.



//-------- Global Variables --------

//The music that will be played
Mix_Music *mainMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gameoverEffect = NULL;
Mix_Chunk *snakeEat = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Main Grid (rows, columns, width, height)
Grid mainGrid(12,12,SCREEN_WIDTH,SCREEN_HEIGHT);

//The frames per second timer
Timer fpsTimer;


//-------- Main functions --------


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Load music, textfiles, images etc.
bool loadMedia();

//Moves the head of the snake, takes 3 arguments (head, col, row)
void moveHead(Rectangle*, int, int);

//Check if the head is out of the grid
bool isHeadInside(int limitX, int limitY, int r, int c);

//Check if head collides with something.
int headCollidesWith(int r, int c);

//Check keyboard status and set snake direction
int handleKeybord(bool player1_move[], int currentDirection, int cD[], int rD[], int* cont);

//Creates a piece of food in a random position.
void createFood();

//Free players data and finishes the current game.
void gameover();

//Controls the music background
void playMusic();
void stopMusic();



//*************** MAIN FUNCTIONS ***************

void playMusic(){
	Mix_PlayMusic( mainMusic, -1 );
}
void stopMusic(){
	 //If the music is paused

    if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

bool loadMedia(){
	//Loading success flag
    bool success = true;

    ////Load prompt texture
    //if( !gPromptTexture.loadFromFile( "21_sound_effects_and_music/prompt.png" ) )
    //{
    //    printf( "Failed to load prompt texture!\n" );
    //    success = false;
    //}

    //Load music
    mainMusic = Mix_LoadMUS( "Media/music.wav" );
    if( mainMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
	gameoverEffect = Mix_LoadWAV( "Media/gameover.wav" );
    if( gameoverEffect == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

	snakeEat = Mix_LoadWAV( "Media/snakeEat.wav" );
    if( snakeEat == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();

	//Free the music
    Mix_FreeMusic( mainMusic );
    mainMusic = NULL;

	Mix_FreeChunk( gameoverEffect );
    gameoverEffect = NULL;

}

bool init()
{
	//Initialization flag
	bool success = true;
	
	//Set the seed for random numbers
	srand(time(NULL)); 

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Snake V1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
			}
		}
	}

	return success;
}


bool isHeadInside(int limitX, int limitY, int x, int y){

	if( x>= limitX || x<0 || y>=limitY || y<0)
		return false;
	else
		return true;

}


void createFood(Rectangle* f){

	bool suc = false;
	int type;
	Rectangle food = *f;

	//These numbers are used to get all the positions where a piece of food can be created.
	int ranRow;
	int ranCol;
	

	while ( suc == false ){

		ranRow = rand() % mainGrid.getRows();  
		ranCol = rand() % mainGrid.getColumns();

		//Check if the position is available.
	
		type = mainGrid.getType(ranCol, ranRow);
		if ( type == -1 ){

		//Set new position.
		food.setPosY(ranRow);
		food.setPosX(ranCol);

		//Change the main grid
		mainGrid.setType(food.getPosX(),food.getPosY(),RECTANGLE_TYPE_FOOD);

		//Return food
		*f = food;

		suc = true;

		}


	}
}


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{	
		loadMedia();	

		//Limits
		int limitX = mainGrid.getRows();
		int limitY = mainGrid.getColumns();
			
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//This variable is used to control the movement speed and is in miliseconds;
		int speedRate = 150;		

		// Game process flags
		bool isThereFood = false;
		bool gameover = false;
		bool justAte = false;
		// Used to only move the snake 1 block every speedRate (sometimes the code get executed more than one time in a milisecond)
		bool hasMoved = false;

		// Snake parts
		int snakeWitdth = mainGrid.getBlockWidth();
		int snakeHeight = mainGrid.getBlockHeight();
		int headStartRow = limitX/2;
		int headStartCol = limitY/2;

		//Create the player and change the state of the grid
		Player player1(SNAKE_LENGTH, snakeWitdth, snakeHeight, headStartRow, headStartCol, COLOR_RED, COLOR_BLUE);
		mainGrid.setType(headStartCol,headStartRow,RECTANGLE_TYPE_SNAKEPART);
		for (int i = 0; i < SNAKE_LENGTH; i++)
			mainGrid.setType(headStartCol-i,headStartRow,RECTANGLE_TYPE_SNAKEPART);

		int playerHeadPositionX;
		int playerHeadPositionY;
		int playerTailPositionX;
		int playerTailPositionY;


		//Creates food
		Rectangle food(0,0,snakeWitdth,snakeHeight,2,COLOR_GREEN,RECTANGLE_TYPE_FOOD); 
		
		//Start counting seconds
		fpsTimer.start();
		playMusic();

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}
				


			//************************GAME PROCESS************************
			if(gameover == false)
			{


				//************************Render process************************

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );


				//Render player 
				player1.render( gRenderer );

				//Render food 
				if( isThereFood == false )
				{
					createFood(&food);
					isThereFood = true;
					justAte = false;
				}
				food.render(gRenderer);
					

				//Update screen
				SDL_RenderPresent( gRenderer );

				//************************Snake movement************************

				//Get current direction: Here it is important to notice that we are getting the current direction every time a frame is render.
				player1.handle();

				//Speed movement control: The following code only get executed every (speedRate) miliseconds
				if( fpsTimer.getTicks() % speedRate == 1 && hasMoved == false )
				{
					//Free the square of the grid where the tail was.
					
					playerTailPositionX = player1.getTailPositionX();
					playerTailPositionY = player1.getTailPositionY();
					mainGrid.setType(playerTailPositionX,playerTailPositionY,-1);

					//Move player towards whatever the current direction is and get the head position to check collisions

					player1.move();
					playerHeadPositionX = player1.getHeadPositionX();
					playerHeadPositionY = player1.getHeadPositionY();

					//If the head went beyond the grid 
					if( !isHeadInside( limitX,limitY, playerHeadPositionX , playerHeadPositionY ) )
					{
						gameover = true;
						printf("Gameover\n");
						stopMusic();
						Mix_PlayChannel( -1, gameoverEffect, 0 );

					}else 
					{
						// If the head of the snake is still inside the grid we need to check if it has collided with something
							
						switch ( mainGrid.getType(playerHeadPositionX, playerHeadPositionY) )
						{
							case -1: 
								//There was no collision
								mainGrid.setType(playerHeadPositionX, playerHeadPositionY, RECTANGLE_TYPE_SNAKEPART);
									
							break;

							case RECTANGLE_TYPE_SNAKEPART: 
								//it collided with a part of his body
								gameover = true;	
								printf("Gameover\n");
								stopMusic();
								Mix_PlayChannel( -1, gameoverEffect, 0 );
							break;

							case RECTANGLE_TYPE_FOOD: 
								//it collided with a piece of food.
								Mix_PlayChannel( -1, snakeEat, 0 );
								player1.hasEaten(playerTailPositionX, playerTailPositionY);
								mainGrid.setType(playerTailPositionX, playerTailPositionY, RECTANGLE_TYPE_SNAKEPART);
								mainGrid.setType(playerHeadPositionX, playerHeadPositionY, RECTANGLE_TYPE_SNAKEPART);

								justAte = true;
								isThereFood = false;
							break;


						}

						mainGrid.printGrid();
						
					}


				hasMoved = true;
				}else if ( fpsTimer.getTicks() % speedRate != 1 ) 
				{
					hasMoved = false;
				}	

			}

		}
		
	}

	//Free resources and close SDL
	close();

	return 0;
}

