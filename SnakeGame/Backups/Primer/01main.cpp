#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <time.h>

//Custom classes
#include "Grid.h"
#include "Rectangle.h"

//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;



enum rectangleType{

	RECTANGLE_TYPE_HEAD,
	RECTANGLE_TYPE_BODY,
	RECTANGLE_TYPE_FOOD,
	RECTANGLE_TYPE_WALL,
	RECTANGLE_TYPE_TOTAL
};



//-------- Global Variables --------

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Main Grid
Grid mainGrid(SCREEN_WIDTH,SCREEN_HEIGHT);



//-------- Main functions --------


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Moves all the body parts of the snake, takes 3 arguments(head,bodyparts,length of bodyparts array)
void moveBody(Rectangle,Rectangle*,int);

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



//*************** MAIN FUNCTIONS ***************


void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool init()
{
	//Initialization flag
	bool success = true;
	
	//Set the seed for random numbers
	srand(time(NULL)); 

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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
			}
		}
	}

	return success;
}

void moveBody(Rectangle head, Rectangle* body, int length, bool justAte){
	for (int i = length-1; i >= 0; i--)
	{
		
		
		if(i==0){

			//First body element

			//Set row and column
			body[i].setRow(head.getRow());
			body[i].setCol(head.getCol());
			//Change grid state
			mainGrid.changeBlockState(body[i].getRow(),body[i].getCol(),&body[i]);

			

		}else{

			//Last body element


			if( i==length-1 && justAte == false){
				//Change grid state: We only need to free the tail of the snake because it will move.
				// We won't free it if the snake just ate.
				mainGrid.changeBlockState(body[i].getRow(),body[i].getCol(),NULL);
			}

			//n body element

			//Set row and column
			body[i].setRow(body[i-1].getRow());
			body[i].setCol(body[i-1].getCol());
			mainGrid.changeBlockState(body[i].getRow(),body[i].getCol(),&body[i]);
		}
	}
}

void moveHead(Rectangle* h, int r, int c){

	//This is an auxiliar variable to modify rows and col because it's not allowed to call *h method.
	Rectangle aux = *h;

	//Move head
	aux.setRow(aux.getRow() + r);
	aux.setCol(aux.getCol() + c);

	//Change grid state
	mainGrid.changeBlockState(aux.getRow(),aux.getCol(),h);

	*h = aux;
}

bool isHeadInside(int limitX, int limitY, int r, int c){

	//printf("r:%d, c:%d, x:%d, y:%d \n",r,c,limitX,limitY);

	if( r>= limitX || r<0 || c>=limitY || c<0)
		return false;
	else
		return true;

}

int headCollidesWith(int r, int c){
	Rectangle* rAux;
	Rectangle bodyPart;
	int collitionPart = -1;

	rAux = mainGrid.checkAvailability(r,c);

	if(rAux!= NULL){
		bodyPart = *rAux;
		collitionPart = bodyPart.getType();
	}
	return collitionPart;
}

int handleKeybord(bool player1_move[], int currentDirection, int cD[], int rD[], int* cont){
	
	//Get current keystate
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] && currentDirection != SDL_SCANCODE_LEFT){

		if (!player1_move[0]){
						
			currentDirection = SDL_SCANCODE_RIGHT;
			cD[*cont] = 1;
			rD[*cont] = 0;

			*cont = *cont + 1;
			player1_move[0] = true;
		}
						

	}else if( currentKeyStates[ SDL_SCANCODE_LEFT ] && currentDirection != SDL_SCANCODE_RIGHT ){


		if (!player1_move[1]){
			currentDirection = SDL_SCANCODE_LEFT;
			cD[*cont] = -1;
			rD[*cont] = 0;

			*cont = *cont + 1;
			player1_move[1] = true;
		}
					
	}else if( currentKeyStates[ SDL_SCANCODE_UP ] && currentDirection != SDL_SCANCODE_DOWN ){

		if (!player1_move[2]){
			currentDirection = SDL_SCANCODE_UP;
			cD[*cont] = 0;
			rD[*cont] = -1;

			*cont = *cont + 1;
		player1_move[2] = true;
		}
					
	}else if( currentKeyStates[ SDL_SCANCODE_DOWN ] && currentDirection != SDL_SCANCODE_UP ){

		if (!player1_move[3]){
			currentDirection = SDL_SCANCODE_DOWN;
			cD[*cont] = 0;
			rD[*cont] = 1;

			*cont = *cont + 1;
			player1_move[3] = true;
		}
					
	}else{
		player1_move[0] = false;
		player1_move[1] = false;
		player1_move[2] = false;
		player1_move[3] = false;
	}

	return currentDirection;
}

void createFood(Rectangle* f){

	bool suc = false;
	Rectangle* rAux;
	Rectangle food = *f;

	//These numbers are used to get all the positions where a piece of food can be created.
	int ranRow;
	int ranCol;
	

	while ( suc == false ){

		ranRow = rand() % ROWS;  
		ranCol = rand() % COLUMNS;

		//Check if the position is available.
	
		rAux = mainGrid.checkAvailability(ranRow,ranCol);
		if ( rAux == NULL ){

		//Set new position.
		food.setRow(ranRow);
		food.setCol(ranCol);

		//Change the main grid
		mainGrid.changeBlockState(food.getRow(),food.getCol(),f);

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
			
			//Limits
			int limitX = mainGrid.getRows();
			int limitY = mainGrid.getCols();
			
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//This variable is used to control the movement speed;
			int speedRate = 700;
			int speedCont = 0;
			
			bool player1_move[] = {false,false,false,false};


			int currentDirection = SDL_SCANCODE_RIGHT;
			mainGrid.clearGrid();

			//
			int cont = 0;
			int cont2 = 0;
			int cD[1000] ;
			int rD[1000] ;

			int r=0;
			int c=1;

			//   Game Variables

			// Game process flags
			bool isThereFood = false;
			bool gameover = false;
			bool justAte = false;

			// Snake parts
			int snakeWitdth = mainGrid.getBlockWidth();
			int snakeHeight = mainGrid.getBlockHeight();
			int headStartRow = ROWS/2;
			int headStartCol = COLUMNS/2;

			Rectangle head(headStartCol,headStartRow,snakeWitdth,snakeHeight,2,"red",RECTANGLE_TYPE_HEAD);
			mainGrid.changeBlockState(headStartRow,headStartCol,&head);

			//Body parts
			int bodyLength = 2;
			Rectangle body[1000];
			for (int i = 0; i < bodyLength; i++)
			{
				body[i].setRectangle((headStartCol-1)-i,headStartRow,snakeWitdth,snakeHeight,2,"blue",RECTANGLE_TYPE_BODY);
				mainGrid.changeBlockState(headStartRow,(headStartCol-1)-i,&body[i]);
			}
			//Creates food
			Rectangle food(0,0,snakeWitdth,snakeHeight,2,"green",RECTANGLE_TYPE_FOOD); 
		



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
				if(gameover == false){

					//************************Render process************************

					//Clear screen
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );


					//Render Snake
					head.render(gRenderer);
					for (int i = 0; i < bodyLength; i++)
					body[i].render(gRenderer);

					//Render food 
					if( isThereFood == false ){
						createFood(&food);
						isThereFood = true;
						justAte = false;
					}
					food.render(gRenderer);
					

					//Update screen
					SDL_RenderPresent( gRenderer );



					//************************Get current direction************************
					currentDirection = handleKeybord(player1_move, currentDirection, cD, rD, &cont);


					//************************Snake movement************************

					//Speed movement control
					speedCont++;
					if(speedCont>speedRate ){



					//Get the next direction!

					if(cont2 < cont){

						r = rD[cont2];
						c = cD[cont2];
						cont2++;
				
					}else{
						cont=0;
						cont2=0;
					}


					//If the head goes beyond the world or collides with a body part
					if( !isHeadInside( limitX,limitY, head.getRow()+r , head.getCol() +c ) ){
						gameover = true;

					}else{

						//Check if the head will collide with something
						int headColittion = headCollidesWith(head.getRow()+r, head.getCol() +c );

						if( headColittion == RECTANGLE_TYPE_BODY){
						
							//Case 1: Head collided with body part

							gameover = true;

						}else if ( headColittion == RECTANGLE_TYPE_FOOD ){
							
							//Case 2: Head collided with food, Add a new body part.

							body[bodyLength].setRectangle(body[bodyLength-1].getRow(),body[bodyLength-1].getCol(),snakeWitdth,snakeHeight,2,"blue",RECTANGLE_TYPE_BODY);
							bodyLength = bodyLength + 1;
							justAte = true;
							isThereFood = false;

						}

							
							//Move body: We move the body first, if we want to move the head first we would need to save the previuos position
							moveBody(head,body,bodyLength, justAte);
							moveHead(&head,r,c);
					
							mainGrid.printGrid();
						
					}

					speedCont=0;

					}	

				}else{
					//printf("Gameover\n");
				}




				
			}
		
	}

	//Free resources and close SDL
	close();

	return 0;
}

