/*
	Author:		Julio Cesar Ojeda Magdaleno
	Title:		Snake Game
	Date:		April 03, 2017
	Contact:	jcom.94m@gmail.com

	This program was written to show my programming skills 
	It was written only by the author Julio Cesar Ojeda Magdaleno.
	Around 85% of the code was designed and coded by the author
	Around 15% of the code was obtained from www.lazyfoo.net
	Music and sound effects were obtained from www.freesound.org
	
	PLEASE READ INFORMATION INSIDE ANYCLASS.H FILE TO UNDERSTAND BETTER THE LOGIC OF THE PROGRAM SPECIALLY PLAYER.H
*/

#include "GameState_Menu.h"
#include "GameState_Running.h"
#include "GameState_Credits.h"
#include "GameState_Scores.h"

//Screen dimension constants
const int SCREEN_WIDTH = 602;
const int SCREEN_HEIGHT = 602;

//-------- Global Variables --------

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//State variables
int stateID = STATE_NULL;

//Game state object
GameState *currentState = NULL;


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//*************** MAIN FUNCTIONS ***************

void close()
{
	//Delete the current state reference
	delete currentState;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Font render
	TTF_Quit();

	//Quit SDL subsystems
	SDL_Quit();

	

}

bool init()
{
	//Initialization flag
	bool success = true;

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

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}


void change_state(int nextState)
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        //Change the state
        switch( nextState )
        {
            case STATE_MENU:
                currentState = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer );
                break;

			case STATE_GAME_RUNNING:
				currentState = new GameRunning(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                break;

			case STATE_CREDITS:
				currentState = new Credits(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                break;

			case STATE_SCORES:
				currentState = new Scores(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
                break;
        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
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

		//Set the current state ID
		stateID = STATE_MENU;

		//Set the current game state object
		currentState = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer );

		 //While the user hasn't quit
		while( stateID != STATE_EXIT )
		{
			
			//Do state event handling
			currentState->handle_events();

			//Do state logic
			currentState->logic();

			//Do state rendering
			currentState->render();

			//Change state if needed
			change_state( currentState->getNextState() );
		}
		
	}

	//Free resources and close SDL
	close();

	return 0;
}

