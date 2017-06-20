#include "GameState_Running.h"

//To see description of some variables and methods please read the comments located in GameRunning.h

GameRunning::GameRunning(int nscreen_width, int nscreen_height, SDL_Renderer* nrenderer){

	//This is to keep in the this state until some event change the state
	nextState = STATE_NULL;

	//Get the class members
	screen_height = nscreen_height;
	screen_width = nscreen_width;
	renderer = nrenderer;

	//Initialize game variables
	fpsTimer.start();
	speedRate = 0;
	gameState = SET_DIFFICULTY;
	start_messages[0] = "3";
	start_messages[1] = "2";
	start_messages[2] = "1";
	start_messages[3] = "GO!";
	animationFrame = 0;
	animationSpeed = 500;  //This is in Miliseconds
	hasExecuted = false;
	hasTypedName = false;

	//Read scores
	scores = new ScoreRecord();

	//Set the seed for random numbers
	srand(time(NULL));
	
	//Backgound music and effects
	loadMedia();
	

	//Main Grid (rows, columns, width, height)
	mainGrid = new Grid(ROWS,COLUMNS,screen_width,screen_height-100);

	//Get the block dimensions for a snake part depending on the grid.
	snakeWitdth = mainGrid->getBlockWidth();
	snakeHeight = mainGrid->getBlockHeight();

	//Get the first position
	headStartRow = ROWS/2;
	headStartCol = COLUMNS/2;

	//Create the player and change the state of the grid
	player1 = new Player(SNAKE_LENGTH, snakeWitdth, snakeHeight, headStartCol, headStartRow, COLOR_RED, COLOR_BLUE);
	mainGrid->setType(headStartCol, headStartRow, RECTANGLE_TYPE_SNAKEPART);
	for (int i = 0; i < SNAKE_LENGTH; i++)
		mainGrid->setType(headStartCol-i, headStartRow, RECTANGLE_TYPE_SNAKEPART);

	//Create the first piece of food
	food = new Rectangle(0,0,snakeWitdth,snakeHeight,2,COLOR_GREEN,RECTANGLE_TYPE_FOOD); 
	createFood();
	isThereFood = true;

	//Create the wall
	for (int i = 0; i < COLUMNS + 2; i++)
	{
		wall_top[i] = new Rectangle(-1 + i,-1,snakeWitdth,snakeHeight,2,COLOR_BLACK,RECTANGLE_TYPE_WALL); 
		wall_bot[i] = new Rectangle(-1 + i,ROWS,snakeWitdth,snakeHeight,2,COLOR_BLACK,RECTANGLE_TYPE_WALL); 
	}
	for (int i = 0; i < ROWS + 2; i++)
	{
		wall_left[i] = new Rectangle(-1, -1 + i,snakeWitdth,snakeHeight,2,COLOR_BLACK,RECTANGLE_TYPE_WALL); 
		wall_right[i] = new Rectangle(COLUMNS, -1 + i,snakeWitdth,snakeHeight,2,COLOR_BLACK,RECTANGLE_TYPE_WALL); 
	}

	//Create buttons 
	btn_again = new Button(screen_width - 200,screen_height-65,"Play Again",35,renderer);
	btn_menu = new Button(screen_width - 200,screen_height-115,"Menu",35,renderer);

	btn_again->setPosition(screen_width/2 - btn_again->getWidth() - 50 , screen_height-100);
	btn_menu->setPosition(screen_width/2 + 50, screen_height-100);
	

	btn_easy = new Button(0, 0,"Easy",40,renderer);
	btn_medium = new Button(0, 0,"Medium",40,renderer);
	btn_hard = new Button(0, 0,"Hard",40,renderer);

	//Center the buttons
	btn_easy->setPosition(50,(screen_height/2 - btn_easy->getHeight()/2));
	btn_medium->setPosition(screen_width/2 - btn_medium->getWidth()/2, (screen_height/2 - btn_medium->getHeight()/2));
	btn_hard->setPosition(screen_width-btn_hard->getWidth()-50,(screen_height/2 - btn_hard->getHeight()/2));

	//Create labels
	lbl_score = new Label(0,screen_height-100,"Score: 0",40,renderer);
	lbl_start = new Label(0,0," ",200,renderer); //This line will trigger an error because it is not posible to render empty text. We need to change the text before rendering
	lblName = new Label(0,0,"New High Score!   ",27,renderer);
	lblName->setFontColor(255,0,0);
	lblName->setPosition(0, screen_height-50);

	//Create textboxes
	txtName = new TextBox(0,0,"Click here to type your name",27,renderer);
	txtName->setPosition(lblName->getWidth() , screen_height-50);


	
}

void GameRunning::handle_events(){

	//While there's events to handle
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
			nextState = STATE_EXIT;
        }

		//Check the sub gamestate
		switch ( gameState ){

		case GAMEOVER:
			btn_again->handle_event(&e);	
			btn_menu->handle_event(&e);
		break;

		case SET_DIFFICULTY:
			btn_easy->handle_event(&e);	
			btn_medium->handle_event(&e);
			btn_hard->handle_event(&e);
		break;

		case GET_SCORE:
			txtName->handle_event(&e);


		break;

		}

	}

	

}

void GameRunning::logic(){

	//Check the gamestate to know what to do

	switch ( gameState ){

	case START:
		startLogic();
	break;
	
	case GAMEOVER:
		gameoverLogic();
	break;

	case RUN:
		runLogic();
	break;

	case SET_DIFFICULTY:
		set_difficultyLogic();
	break;

	case GET_SCORE:
		get_scoreLogic();
	break;

	}
}

void GameRunning::render(){

	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );


	//Check the gamestate to see what to render

	switch ( gameState ){

	case START:
		lbl_start->render();
	break;
	
	case GAMEOVER:
		btn_again->render();				
		btn_menu->render();
		player1->render( renderer );
		food->render(renderer);
		renderWall();
	break;

	case RUN:
		player1->render( renderer );
		food->render(renderer);
		lbl_score->render();
		renderWall();
	break;

	case SET_DIFFICULTY:
		btn_easy->render();	
		btn_medium->render();
		btn_hard->render();
	break;

	case GET_SCORE:
		player1->render( renderer );
		food->render(renderer);
		lbl_score->render();
		renderWall();
		lblName->render();
		txtName->render();	
	break;

	}


	//Update screen
	SDL_RenderPresent( renderer );

}

void GameRunning::playMusic(){
	Mix_PlayMusic( mainMusic, -1 );
}

void GameRunning::stopMusic(){
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

bool GameRunning::loadMedia(){
	//Loading success flag
    bool success = true;

    //Load music
    mainMusic = Mix_LoadMUS( "Media/music.wav" );
    if( mainMusic == NULL )
    {
        success = false;
    }
    
    //Load sound effects
	gameoverEffect = Mix_LoadWAV( "Media/gameover.wav" );
    if( gameoverEffect == NULL )
    {
         success = false;
    }

	snakeEat = Mix_LoadWAV( "Media/snakeEat.wav" );
    if( snakeEat == NULL )
    {
        success = false;
    }
    
    return success;
}

void GameRunning::createFood(){

	bool suc = false;
	int type;

	//These numbers are used to get all the positions where a piece of food can be created.
	int ranRow;
	int ranCol;
	

	while ( suc == false ){

		ranRow = rand() % ROWS;  
		ranCol = rand() % COLUMNS;

		//Check if the position is available.
	
		type = mainGrid->getType(ranCol, ranRow);
		if ( type == -1 ){

		//Set new position.
		food->setPosY(ranRow);
		food->setPosX(ranCol);

		//Change the main grid
		mainGrid->setType(food->getPosX(),food->getPosY(),RECTANGLE_TYPE_FOOD);

		suc = true;

		}


	}
}

bool GameRunning::getError(){

	return error;

}

bool GameRunning::isHeadInside(int limitY, int limitX, int x, int y){

	if( x>= limitX || x<0 || y>=limitY || y<0)
		return false;
	else
		return true;

}

void GameRunning::fgameover(){

	//Check if the user has done a new high score to know which state it will go to.
	if ( player1->getScore() > scores->getHightScore() )
	{
		gameState = GET_SCORE;
	} else
	{
		gameState = GAMEOVER;
	}

	//lbl_score->setPosition(0, screen_height-50);

	//Change the opacity of all the elements
	player1->setOpacity(128);
	food->setAlpha(128);

	for (int i = 0; i < COLUMNS + 2; i++){
		wall_top[i]->setAlpha(128);
		wall_bot[i]->setAlpha(128);
	}

	for (int i = 0; i < COLUMNS + 2; i++){

		wall_left[i]->setAlpha(128);
		wall_right[i]->setAlpha(128);
	}


	stopMusic();
	Mix_PlayChannel( -1, gameoverEffect, 0 );
}

 GameRunning::~GameRunning(){
	delete player1;
	 
	 //Free elements
	delete food; 

	delete mainGrid;
	delete btn_again;
	delete btn_menu;
	delete btn_easy;
	delete btn_medium;
	delete btn_hard;
	delete lbl_score;
	delete lbl_start;
	delete txtName;
	delete lblName;

	food = NULL;
	mainGrid = NULL;
	btn_again = NULL;
	btn_menu = NULL;
	btn_easy = NULL;
	btn_medium = NULL;
	btn_hard = NULL;
	lbl_score = NULL;
	lbl_start = NULL;
	txtName = NULL;
	lblName = NULL;

	//Free the music
    Mix_FreeMusic( mainMusic );
    mainMusic = NULL;

	Mix_FreeChunk( gameoverEffect );
    gameoverEffect = NULL;

	
	scores->free();
 }

void GameRunning::renderWall(){

	for (int i = 0; i < COLUMNS + 2; i++){

		wall_top[i]->render( renderer );
		wall_bot[i]->render( renderer );

	}

	for (int i = 0; i < COLUMNS + 2; i++){

		wall_left[i]->render( renderer );
		wall_right[i]->render( renderer );

	}

}

void GameRunning::startLogic(){

	//The following code only get executed every (animationSpeed) miliseconds
	if( fpsTimer.getTicks() % animationSpeed == 1 && hasExecuted == false )
	{
		if( animationFrame < 4)
		{	
			lbl_start->setText(start_messages[animationFrame]);
			//To center
			lbl_start->setPosition(screen_width/2 - lbl_start->getWidth()/2,screen_height/2-lbl_start->getHeight()/2);

			animationFrame++;
		}else
		{
			//Animation has finished now start the game
			playMusic();
			gameState = RUN;
			hasExecuted = false;
		}

	//This flag is used to prevent the code above to get executed more than once in a milisecond	
	hasExecuted = true;
	}else if ( fpsTimer.getTicks() % animationSpeed != 1 ) 
	{
			//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond	
			hasExecuted = false;
	}
	
}

void GameRunning::set_difficultyLogic(){

	// Depending on the button it will change the speed rate and i will change to start state
	if ( btn_easy->getState() == BUTTON_STATE_ON)
	{
		gameState = START;
		speedRate = 300;
		difficultyLevel = "Easy";
	}

	if ( btn_medium->getState() == BUTTON_STATE_ON)
	{
		gameState = START;
		speedRate = 170;
		difficultyLevel = "Medium";
	}

	if ( btn_hard->getState() == BUTTON_STATE_ON)
	{
		gameState = START;
		speedRate = 80;
		difficultyLevel = "Hard";
	}
}

void GameRunning::runLogic(){

	//Get current direction: Here it is important to notice that we are getting the current direction every time a frame is render.
	player1->handle();

	//Speed movement control: The following code only get executed every (speedRate) miliseconds
	if( fpsTimer.getTicks() % speedRate == 1 && hasExecuted == false )
	{

		//Check if the is a piece of food in the grid 
		if( isThereFood == false )
		{
			createFood();
			isThereFood = true;
		}

		//Free the square of the grid where the tail was.		
		playerTailPositionX = player1->getTailPositionX();
		playerTailPositionY = player1->getTailPositionY();
		mainGrid->setType(playerTailPositionX, playerTailPositionY, -1);

		//Move player towards whatever the current direction is and get the head position to check collisions
		player1->move();
		playerHeadPositionX = player1->getHeadPositionX();
		playerHeadPositionY = player1->getHeadPositionY();

		//If the head went beyond the grid 
		if( !isHeadInside( ROWS,COLUMNS, playerHeadPositionX , playerHeadPositionY ) )
		{
			fgameover();

		}else 
		{
			// If the head of the snake is still inside the grid we need to check if it has collided with something
							
			switch ( mainGrid->getType(playerHeadPositionX, playerHeadPositionY) )
			{
				case -1: 
					//There was no collision
					mainGrid->setType(playerHeadPositionX, playerHeadPositionY, RECTANGLE_TYPE_SNAKEPART);
									
				break;

				case RECTANGLE_TYPE_SNAKEPART: 
					//it collided with a part of his body
					fgameover();
				break;

				case RECTANGLE_TYPE_FOOD: 
					//it collided with a piece of food.
					Mix_PlayChannel( -1, snakeEat, 0 );
					player1->hasEaten(playerTailPositionX, playerTailPositionY);
					mainGrid->setType(playerTailPositionX, playerTailPositionY, RECTANGLE_TYPE_SNAKEPART);
					mainGrid->setType(playerHeadPositionX, playerHeadPositionY, RECTANGLE_TYPE_SNAKEPART);
					isThereFood = false;

					//Change score label
					std::string player_score;
					player_score = "Score: " + std::to_string(player1->getScore());

					lbl_score->setText(player_score);

				break;


			}
						
		}

	//This flag is used to prevent the code above to get executed more than once in a milisecond	
	hasExecuted = true;
	}else if ( fpsTimer.getTicks() % speedRate != 1 ) 
	{
		//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond
		hasExecuted = false;
	}
}

void GameRunning::get_scoreLogic(){

	//If the user has type a valid name (So far it's valid if is not empty)
	if ( txtName->isValid() )
	{
		//Write a new record in the file
		scores->addNewRecord(txtName->getText(),player1->getScore(),difficultyLevel);
		scores->writeOnFile();
		gameState = GAMEOVER;
	}
}

void GameRunning::gameoverLogic(){

	//Check if a button is pressed and change the mainState
	if ( btn_again->getState() == BUTTON_STATE_ON)
	{
		nextState = STATE_GAME_RUNNING;
	}

	if ( btn_menu->getState() == BUTTON_STATE_ON)
	{
		nextState = STATE_MENU;
	}
	
}

void GameRunning::readScoreRecords(){



}

