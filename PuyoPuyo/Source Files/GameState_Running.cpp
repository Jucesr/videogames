#include "../Header Files/GameState_Running.h"

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
	speedRate = 1000;
	gameState = START;
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
	mainGrid = new Grid(ROWS,COLUMNS,screen_width - (XRENDEROFFSET + YRENDEROFFSET), screen_height - 100);

	//Get the block dimensions for a puyo
	puyoWitdth = mainGrid->getBlockWidth();
	puyoHeight = mainGrid->getBlockHeight();

	//Get the first position
	headStartRow = 0;
	headStartCol = COLUMNS/2;

	//Create the player 
	player1 = new Player(headStartCol, headStartRow, puyoWitdth, puyoHeight, puyoSprite, XRENDEROFFSET, YRENDEROFFSET);
	player1->setSpeed(100,700,100);
	playerScore = 0;

	//CPU Player
	headStartRow = 0;
	headStartCol = rand() % COLUMNS;
	puyoCPU_yspeed = 150;
	puyoCPU_xspeed = 100;
	int randomPuyoType = rand() % PUYO_TOTAL;
	puyoCPU = new Puyo(headStartCol, headStartRow, puyoWitdth, puyoHeight, randomPuyoType, puyoSprite, XRENDEROFFSET, YRENDEROFFSET );
	cpuScore = 0;

	//Create buttons 
	btn_again = new Button(screen_width - 200,screen_height-65,"Play Again",35,renderer);
	btn_menu = new Button(screen_width - 200,screen_height-115,"Menu",35,renderer);

	btn_again->setPosition(screen_width/2 - btn_again->getWidth() - 50 , screen_height/2);
	btn_menu->setPosition(screen_width/2 + 50, screen_height/2);
	

	//Create labels
	lbl_score = new Label(0,screen_height-90,"Score: 0",30,renderer);
	lbl_SCPUscore = new Label(screen_width/2,screen_height-80,"CPU Score: 0",30,renderer);


	lbl_rotate = new Label(0,0,"Press R to rotate",15,renderer); 
	lbl_start = new Label(0,0," ",150,renderer); 
	lblName = new Label(0,0,"New High Score!   ",30,renderer);

	lblName->setFontColor(255,0,0);
	lblName->setPosition(screen_width/2 - lblName->getWidth()/2, screen_height/2 - lblName->getHeight()/2);

	lbl_rotate->setPosition(screen_width/2 - lbl_rotate->getWidth()/2, screen_height/2 - lbl_rotate->getHeight()/2);

	//Create textboxes
	txtName = new TextBox(15,0,"Click here to type your name",20,renderer);
	txtName->setPosition(screen_width/2 - txtName->getWidth()/2, screen_height/2 + lblName->getHeight()/2);

	puyosMovedDown = 0;
	gridNeedUpdate = false;
	
	gamePaused = false;
	gridIsInverting = false;
	invertMode = false;
	gameOverCondition = -1;

	
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
        }else if( e.type == SDL_KEYDOWN ){

			switch( e.key.keysym.sym){

			case SDLK_p:
				if (gamePaused == true){

					gamePaused = false;

				}else{

					gamePaused = true;

				}
			break;

			case SDLK_t:
				gridIsInverting = true;
				puyosMovedUp = 0;
			break;

			}
		}

		//Check the sub gamestate
		switch ( gameState ){

		case GAMEOVER:
			btn_again->handle_event(&e);	
			btn_menu->handle_event(&e);
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
		lbl_score->render();
		lbl_SCPUscore->render();
	break;

	case RUN:
		lbl_rotate->render();
		mainGrid->render();
		
		if( !gridIsInverting ){

			player1->render( renderer );
			puyoCPU->render();

		}

		lbl_score->render();
		lbl_SCPUscore->render();

	break;

	case GET_SCORE:
		lbl_score->render();
		lbl_SCPUscore->render();
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
    mainMusic = Mix_LoadMUS( "Resource Files/music.wav" );
    if( mainMusic == NULL )
    {
        success = false;
    }
    
    //Load sound effects
	gameoverEffect = Mix_LoadWAV( "Resource Files/gameover.wav" );
    if( gameoverEffect == NULL )
    {
         success = false;
    }

	increaseScore = Mix_LoadWAV( "Resource Files/scoreUp.wav" );
    if( increaseScore == NULL )
    {
        success = false;
    }

	//Load images
	puyoSprite = new Texture(renderer);
	puyoSprite->loadFromFile( "Resource Files/puyo_sprite.png" );
    if( puyoSprite == NULL )
    {
        success = false;
    }
    
    return success;
}

bool GameRunning::getError(){

	return error;

}

void GameRunning::run_gameover(){

	if( mainGrid->getInfo( COLUMNS/2, gameOverCondition ) !=NULL){

		//Check if the user has done a new high score to know which state it will go to.
		if ( playerScore > scores->getHightScore() )
		{
			gameState = GET_SCORE;
		} else
		{
			gameState = GAMEOVER;
		}

		//lbl_score->setPosition(0, screen_height-50);


		stopMusic();
		Mix_PlayChannel( -1, gameoverEffect, 0 );

	}
}

 GameRunning::~GameRunning(){
	delete player1;
	 
	 //Free elements

	delete mainGrid;
	delete btn_again;
	delete btn_menu;
	delete lbl_score;
	delete lbl_start;
	delete txtName;
	delete lblName;

	mainGrid = NULL;
	btn_again = NULL;
	btn_menu = NULL;
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

void GameRunning::checkHeadCollition(){

	//Check if the head collides with something
	if( mainGrid->getInfo(playerHeadPosition.x, playerHeadPosition.y) != NULL && ( player1->getPuyoState() == COMPLETE || player1->getPuyoState() == ONLY_HEAD) )
	{
		player1->setHeadPositionY(player1->getHeadPrevPosition().y);
		mainGrid->setInfo(player1->getPuyoHead() );
		player1->cutHead();
		//The grid has been updated. We need to check tail colition
		checkTailCollition();				
	}

}

void GameRunning::checkTailCollition(){

	//Check if the tail collides with something
	if( mainGrid->getInfo(playerTailPosition.x, playerTailPosition.y) != NULL && ( player1->getPuyoState() == COMPLETE || player1->getPuyoState() == ONLY_TAIL )){

		player1->setTailPositionY(player1->getTailPrevPosition().y );
		mainGrid->setInfo(player1->getPuyoTail() );
		player1->cutTail();

		//The grid has been updated. We need to check head colition
		checkHeadCollition();
	}
}

void GameRunning::runLogic(){

	if( !gamePaused )
	{

		if( !gridIsInverting ){

			if( !gridNeedUpdate ){

				//Check gameover
				run_gameover();

				//Check colliton and Move puyo cpu
				currentPlayerName = CPU;
				movePuyoCPU();

				//Check the keyboard state
				player1->handle(invertMode);

				currentPlayerName = PLAYER1;

					//---------------Handle horizontal movement---------------
					player1->moveHorizontal( fpsTimer.getTicks() );

					playerHeadPosition = player1->getHeadPosition();
					playerTailPosition = player1->getTailPosition();

					//Only when the puyo is complete because is when it's able to move horizontally
					if ( player1->getPuyoState() == COMPLETE)
					{

						//Check collition with the right side of the screen.
						if( playerHeadPosition.x >= COLUMNS || playerTailPosition.x >= COLUMNS){

							player1->setHeadPositionX(player1->getHeadPosition().x - 1);	
							player1->setTailPositionX(player1->getTailPosition().x - 1);
			
						//Check collition with the left side of the screen.
						}else if( playerHeadPosition.x < 0 || playerTailPosition.x < 0 ){

							player1->setHeadPositionX(player1->getHeadPosition().x + 1);
							player1->setTailPositionX(player1->getTailPosition().x + 1);

						//Check collition with another puyo
						}else if( mainGrid->getInfo(playerHeadPosition.x, playerHeadPosition.y) != NULL)
						{
							player1->setHeadPositionX(player1->getHeadPrevPosition().x);
							player1->setTailPositionX(player1->getTailPrevPosition().x);
				
						}else if( mainGrid->getInfo(playerTailPosition.x, playerTailPosition.y) != NULL)
						{
							player1->setHeadPositionX(player1->getHeadPrevPosition().x);
							player1->setTailPositionX(player1->getTailPrevPosition().x);
						}

					}

					//---------------Handle rotation movement---------------

					if( player1->getPuyoState() == COMPLETE && player1->getHeadPosition().y < ROWS - 1){

						player1-> rotate( fpsTimer.getTicks() );

						playerHeadPosition = player1->getHeadPosition();
						playerTailPosition = player1->getTailPosition();

						//Check collition with the right side of the screen.
						if( playerHeadPosition.x >= COLUMNS || playerTailPosition.x >= COLUMNS){

							player1->setHeadPositionX(player1->getHeadPosition().x - 1);	
							player1->setTailPositionX(player1->getTailPosition().x - 1);

			
						//Check collition with the left side of the screen.
						}else if( playerHeadPosition.x < 0 || playerTailPosition.x < 0 ){

							player1->setHeadPositionX(player1->getHeadPosition().x + 1);
							player1->setTailPositionX(player1->getTailPosition().x + 1);

			
						}
			
						playerHeadPosition = player1->getHeadPosition();
						playerTailPosition = player1->getTailPosition();

						//Check collition with another puyo
						if( mainGrid->getInfo(playerTailPosition.x, playerTailPosition.y) != NULL)
						{
 				
							int headPosX = player1->getHeadPosition().x;
							int headPosY = player1->getHeadPosition().y;
							//180* rotation
							player1->setHeadPositionX(player1->getTailPrevPosition().x);
							player1->setHeadPositionY(player1->getTailPrevPosition().y);

							player1->setTailPositionX(headPosX);
							player1->setTailPositionY(headPosY);
						}else if(  mainGrid->getInfo(playerHeadPosition.x, playerHeadPosition.y) != NULL )
						{

							player1->setHeadPositionX(player1->getTailPrevPosition().x);
							player1->setHeadPositionY(player1->getTailPrevPosition().y);

							player1->setTailPositionX(player1->getHeadPrevPosition().x);
							player1->setTailPositionY(player1->getHeadPrevPosition().y);

						}

					}


					//---------------Handle vertical movement---------------
					player1->moveDown( fpsTimer.getTicks(), invertMode);

					playerHeadPosition = player1->getHeadPosition();
					playerTailPosition = player1->getTailPosition();

					if( invertMode ){

						switch ( player1->getPuyoState() )
						{
							case COMPLETE:

								//Check collition with the top
								if( playerHeadPosition.y < 0 || playerTailPosition.y < 0)
								{
									player1->setHeadPositionY(player1->getHeadPrevPosition().y );
									player1->setTailPositionY(player1->getTailPrevPosition().y );

									mainGrid->setInfo(player1->getPuyoHead() );
									mainGrid->setInfo(player1->getPuyoTail() );

									player1->cutHead();
									player1->cutTail();

								//The puyo is inside the grid. We still need to check collition with elements
								}else{

									checkHeadCollition();
									checkTailCollition();
				
								}

							break;

							case ONLY_HEAD:

								if( playerHeadPosition.y < 0 )
								{
									player1->setHeadPositionY(player1->getHeadPrevPosition().y );

									mainGrid->setInfo(player1->getPuyoHead() );
									player1->cutHead();

								}else{				
									checkHeadCollition();
								}


							break;

							case ONLY_TAIL:

								if( playerTailPosition.y < 0)
								{
									player1->setTailPositionY(player1->getTailPrevPosition().y );

									mainGrid->setInfo(player1->getPuyoTail() );
									player1->cutTail();

								}else{
					
									checkTailCollition();
		
								}

							break;



						}

					}else{

						switch ( player1->getPuyoState() )
						{
							case COMPLETE:

								//Check collition with the bottom
								if( playerHeadPosition.y >= ROWS || playerTailPosition.y >= ROWS)
								{
									player1->setHeadPositionY(player1->getHeadPrevPosition().y );
									player1->setTailPositionY(player1->getTailPrevPosition().y );

									mainGrid->setInfo(player1->getPuyoHead() );
									mainGrid->setInfo(player1->getPuyoTail() );

									player1->cutHead();
									player1->cutTail();

								//The puyo is inside the grid. We still need to check collition with elements
								}else{

									checkHeadCollition();
									checkTailCollition();
				
								}

							break;

							case ONLY_HEAD:

								if( playerHeadPosition.y >= ROWS )
								{
									player1->setHeadPositionY(player1->getHeadPrevPosition().y );

									mainGrid->setInfo(player1->getPuyoHead() );
									player1->cutHead();

								}else{				
									checkHeadCollition();
								}


							break;

							case ONLY_TAIL:

								if( playerTailPosition.y >= ROWS)
								{
									player1->setTailPositionY(player1->getTailPrevPosition().y );

									mainGrid->setInfo(player1->getPuyoTail() );
									player1->cutTail();

								}else{
					
									checkTailCollition();
		
								}

							break;



						}

						}

					//Create another pair of puyos and check for combinations
					if(player1->getPuyoState() == NONE)
					{
						//Check combination on grid.
						checkCombinationsInGrid(PLAYER1);

						player1->createPuyo();

					}

				//If the grid need an update!
				}else{

					//Only to see the animation of the grid beeing update.
					if( fpsTimer.getTicks() % animationSpeed == 1 && hasExecuted == false )
					{
						updateGrid(currentPlayerName);

						//This flag is used to prevent the code above to get executed more than once in a milisecond	
						hasExecuted = true;
					}else if ( fpsTimer.getTicks() % animationSpeed != 1 ) 
					{
							//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond	
							hasExecuted = false;
					}
				}
			
			//If the grid is updating
			}else{

				//Only to see the animation of the grid beeing update.
					if( fpsTimer.getTicks() % animationSpeed == 1 && hasExecuted == false )
					{
						invertBoard();
						//This flag is used to prevent the code above to get executed more than once in a milisecond	
						hasExecuted = true;
					}else if ( fpsTimer.getTicks() % animationSpeed != 1 ) 
					{
							//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond	
							hasExecuted = false;
					}

			}

	}
	
}

void GameRunning::getCombination(int c, int r, int puyoType, int level, int playerName){

	Entity* gridSquare;
	int nextPuyoType;
	
	gridSquare = mainGrid->getInfo(c,r);

	if ( gridSquare!= NULL && gridSquare->getState() == false)
	{

		//Get puyo type
		nextPuyoType = gridSquare->getType();
		//Check if they are the same type
		if( puyoType == nextPuyoType)
		{
			puyosTogether[puyosTogetherCount] = gridSquare;
			puyosTogetherCount++;
			gridSquare->setState(true);

			//Right side
			if( c < COLUMNS - 1 )
				getCombination(c + 1, r, nextPuyoType, level + 1, playerName);

			//Left side
			if( c > 0 )
				getCombination(c - 1, r, nextPuyoType, level + 1, playerName);

			//Down side
			if( r < ROWS - 1 )
				getCombination(c, r+1, nextPuyoType, level + 1, playerName);

			//Up side
			if( r > 0 )
				getCombination(c, r-1, nextPuyoType, level + 1, playerName);

		}

		if( level == 0 ){

			if( puyosTogetherCount >= 4 ) {
				
				//Free grid spaces
				for (int i = 0; i < puyosTogetherCount; i++)
				{	
					mainGrid->setInfo(puyosTogether[i], true);
					delete puyosTogether[i];
					
				}

				if (playerName == PLAYER1){

					//Increase player's score
					playerScore = playerScore + puyosTogetherCount;
					//Change score label
					std::string player_score;
					player_score = "Score: " + std::to_string(playerScore);

					lbl_score->setText(player_score);
				

				}else if(playerName == CPU){

					//Increase player's score
					cpuScore = cpuScore + puyosTogetherCount;
					//Change score label
					std::string cpu_Score;
					cpu_Score = "CPU Score: " + std::to_string(cpuScore);

					lbl_SCPUscore->setText(cpu_Score);

				}

				Mix_PlayChannel( -1, increaseScore, 0 );
				gridNeedUpdate = true;


			}else{
				for (int i = 0; i < puyosTogetherCount; i++)
				{	
					puyosTogether[i]->setState(false);
				}
				
			}
			puyosTogetherCount = 0;
		}
		

	}

}

void GameRunning::updateGrid(int playerName){
	
	Entity* gridSquare;

	if( !invertMode ){

		for (int r = ROWS - 2; r >= 0; r--)
			{
				for (int c = COLUMNS - 1; c >= 0; c--)
				{
					gridSquare =  mainGrid->getInfo(c,r);
					if( gridSquare !=NULL ){

						if( mainGrid->getInfo(c,r + 1) == NULL){						
							mainGrid->setInfo(gridSquare , true);
							gridSquare->setPosY(r+1);
							mainGrid->setInfo(gridSquare);

							puyosMovedDown ++;
						}
					}
				}
			}

			if (puyosMovedDown > 0){
					
				gridNeedUpdate = true;
				puyosMovedDown = 0;

			}else{

				gridNeedUpdate = false;
				checkCombinationsInGrid(playerName);
			
				
			}
	}else{
			for (int r = 1 ; r < ROWS; r++)
			{
				for (int c = 0; c < COLUMNS; c++)
				{
					gridSquare =  mainGrid->getInfo(c,r);
					if( gridSquare !=NULL ){

						if( mainGrid->getInfo(c,r - 1) == NULL){						
							mainGrid->setInfo(gridSquare , true);
							gridSquare->setPosY(r-1);
							mainGrid->setInfo(gridSquare);

							puyosMovedDown ++;
						}
					}
				}
			}

			if (puyosMovedDown > 0){
					
				gridNeedUpdate = true;
				puyosMovedDown = 0;

			}else{

				gridNeedUpdate = false;
				checkCombinationsInGrid(playerName);
			
				
			}
	}
	

}

void GameRunning::checkCombinationsInGrid(int playerName){

	puyosTogetherCount = 0;
			Entity* gridSquare;
			for (int r = 0; r < ROWS; r++)
			{
				for (int c = 0; c < COLUMNS; c++)
				{
				
					//getCombination(c,r, SIDE_NONE);
					gridSquare =  mainGrid->getInfo(c,r);
					if( gridSquare !=NULL ){						
						getCombination(c,r, gridSquare->getType(), 0, playerName);
					}
				}

			}
}

void GameRunning::get_scoreLogic(){

	//If the user has type a valid name (So far it's valid if is not empty)
	if ( txtName->isValid() )
	{
		//Write a new record in the file
		scores->addNewRecord(txtName->getText(),playerScore);
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


void GameRunning::movePuyoCPU(){
	

	//This if control the movement speed. Only got executed every (y_speed) miliseconds
	if( fpsTimer.getTicks() % puyoCPU_yspeed == 1 && puyoCPUhasMoved == false )
	{		
		int puyoCPU_x = puyoCPU->getPosX();
		int puyoCPU_y = puyoCPU->getPosY();

		puyoHasMovedHorizontal = false;

		if (rand() % 3 == 0){
			puyoWillMoveX = true;
		}

		//---------Horizontal Movement ----------

		if (puyoWillMoveX){

			int nextMove;

			if( rand() % 2 == 0){

				nextMove = -1;

			}else{

				nextMove = 1;

			}

			//Check borders
			if( puyoCPU_x + nextMove < COLUMNS && puyoCPU_x + nextMove > 0)
			{

				//Check grid squares
				if( mainGrid->getInfo(puyoCPU_x + nextMove, puyoCPU_y) == NULL )
				{

					//Check player

					if( puyoCPU_x + nextMove != player1->getHeadPosition().x && puyoCPU_y != player1->getHeadPosition().y &&
						puyoCPU_x + nextMove != player1->getTailPosition().x && puyoCPU_y != player1->getTailPosition().y)
					{

						puyoCPU->setPosX(puyoCPU->getPosX() + nextMove);
						puyoWillMoveX = false;
						puyoHasMovedHorizontal = true;
					}
				}

			}

		}

		//---------Vertical Movement ----------

		if( !puyoHasMovedHorizontal )
		{

			bool condition;
			int y_value;

			//Check the mode
			if( invertMode )
			{

				condition = puyoCPU_y - 1 > -1;
				y_value = -1;

			}else{

				condition =  puyoCPU_y + 1 < ROWS;
				y_value = 1;

			}

			//Check borders
			if( condition )
			{

				//Check grid squares
				if( mainGrid->getInfo(puyoCPU_x , puyoCPU_y + y_value) != NULL )
				{
					mainGrid->setInfo(puyoCPU);
					checkCombinationsInGrid(CPU);
					createPuyoCPU();
				}else{

					//Check player
					if( puyoCPU_x != player1->getHeadPosition().x && puyoCPU_y + y_value != player1->getHeadPosition().y &&
						puyoCPU_x != player1->getTailPosition().x && puyoCPU_y + y_value != player1->getTailPosition().y)
					{

						
						puyoCPU->setPosY(puyoCPU->getPosY() + y_value);

					}
				}

			}else{

					mainGrid->setInfo(puyoCPU);
					checkCombinationsInGrid(CPU);
					createPuyoCPU();
			}

			
		}
		


	//This flag is used to prevent the code above to get executed more than once in a milisecond	
	puyoCPUhasMoved = true;
	}else if ( fpsTimer.getTicks() % puyoCPU_yspeed != 1 ) 
	{
		//Now when the milisecond has change the flag changes its value in order to execute the code the next (SpeedRate) milisecond
		puyoCPUhasMoved = false;
	}

}

void GameRunning::createPuyoCPU(){

	if(!invertMode){

		headStartRow = 0;

	}else{
		
		headStartRow = ROWS-1;

	}
	headStartCol = rand() % COLUMNS;
	puyoCPU_yspeed = 150;
	puyoCPU_xspeed = 100;
	int randomPuyoType = rand() % PUYO_TOTAL;
	puyoCPU = new Puyo(headStartCol, headStartRow, puyoWitdth, puyoHeight, randomPuyoType, puyoSprite, XRENDEROFFSET, YRENDEROFFSET );


}

void GameRunning::invertBoard(){

	Entity* gridSquare;

	if( invertMode ){

			for (int r = ROWS - 2; r >= 0; r--)
			{
				for (int c = COLUMNS - 1; c >= 0; c--)
				{
					gridSquare =  mainGrid->getInfo(c,r);
					if( gridSquare !=NULL ){

						if( mainGrid->getInfo(c,r + 1) == NULL){						
							mainGrid->setInfo(gridSquare , true);
							gridSquare->setPosY(r+1);
							mainGrid->setInfo(gridSquare);

							puyosMovedUp ++;
						}
					}
				}
			}

			if (puyosMovedUp > 0){
					
				gridIsInverting = true;
				puyosMovedUp = 0;

			}else{

				gridIsInverting = false;
				invertMode = false;
				gameOverCondition = -1;
				player1->setStartPosition(COLUMNS/2, 0);
				player1->createPuyo();
				createPuyoCPU();
				
			}

	}else{

		for (int r = 1 ; r < ROWS; r++)
			{
				for (int c = 0; c < COLUMNS; c++)
				{
					gridSquare =  mainGrid->getInfo(c,r);
					if( gridSquare !=NULL ){

						if( mainGrid->getInfo(c,r - 1) == NULL){						
							mainGrid->setInfo(gridSquare , true);
							gridSquare->setPosY(r-1);
							mainGrid->setInfo(gridSquare);

							puyosMovedUp ++;
						}
					}
				}
			}

			if (puyosMovedUp > 0){
					
				gridIsInverting = true;
				puyosMovedUp = 0;

			}else{

				gridIsInverting = false;
				invertMode = true;
				gameOverCondition = ROWS-1;
				player1->setStartPosition(COLUMNS/2, ROWS-1);
				player1->createPuyo();
				createPuyoCPU();
				
			}

	}

}






