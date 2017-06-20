#include "GameState_Scores.h"

Scores::Scores(int nscreen_width, int nscreen_height, SDL_Renderer* nrenderer){

	//This is to keep in the this state until some event change the state
	nextState = STATE_NULL;

	screen_height = nscreen_height;
	screen_width = nscreen_width;

	renderer = nrenderer;

	//Read scores
	scores = new ScoreRecord();

	//Set buttons
	btn_menu = new Button(0, 0, "Menu", 30, renderer);
	btn_menu->setPosition(screen_width - btn_menu->getWidth() - 30, screen_height - btn_menu->getHeight() - 30);

	//Set content
	int x_offset = 30;
	int y_offset = 50;
	int x_increment = 140;
	int y_increment = 40;
	int fontSize = 24;
	int fontSizeText = 18;

	//Set headers
	lbl_Position = new Label(x_offset + x_increment*0, y_offset + y_increment*0 , "#", fontSize, renderer);
	lbl_Name = new Label(x_offset + x_increment*1, y_offset + y_increment*0, "Name", fontSize, renderer);
	lbl_Score = new Label(x_offset + x_increment*2, y_offset + y_increment*0, "Score", fontSize, renderer);
	lbl_Dificulty = new Label(x_offset + x_increment*3, y_offset + y_increment*0, "Level", fontSize, renderer);
	//Set blue
	lbl_Position->setFontColor(0,0,255);
	lbl_Name->setFontColor(0,0,255);
	lbl_Score->setFontColor(0,0,255);
	lbl_Dificulty->setFontColor(0,0,255);

	//Set content
	for (int i = 0; i < scores->getNumRecords(); i++)
	{
		txt_Position[ i ] = new Label(x_offset + x_increment*0, y_offset + y_increment* (i+1) , std::to_string(i+1), fontSize, renderer);
		txt_Name[ i ] = new Label(x_offset + x_increment*1, y_offset + y_increment* (i+1) , scores->getName(i), fontSize, renderer);
		txt_Score[ i ] = new Label(x_offset + x_increment*2, y_offset + y_increment* (i+1) , std::to_string(scores->getScore(i)), fontSize, renderer);
		txt_Dificulty[ i ] = new Label(x_offset + x_increment*3, y_offset + y_increment* (i+1) , scores->getDifficulty(i), fontSize, renderer);
	}

}

void Scores::logic(){

	//Check if a button is pressed and change the main state
	if ( btn_menu->getState() == BUTTON_STATE_ON )
	{
		nextState = STATE_MENU;
	}

}

void Scores::render(){

	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	
	//Render elements
	lbl_Position->render();
	lbl_Name->render();
	lbl_Score->render();
	lbl_Dificulty->render();

	for (int i = 0; i < scores->getNumRecords(); i++)
	{
		txt_Position[ i ]->render();
		txt_Name[ i ]->render();
		txt_Score[ i ]->render();
		txt_Dificulty[ i ]->render();
	}


	btn_menu->render();

	//Update screen
	SDL_RenderPresent( renderer );


}

void Scores::handle_events(){

	//While there's events to handle
    while( SDL_PollEvent( &e ) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
			nextState = STATE_EXIT;
        }

		//Handle buttons
		btn_menu->handle_event(&e);	

	}
}

bool Scores::getError(){

	return error;

}

Scores::~Scores(){

	delete lbl_Position;
	delete lbl_Name;
	delete lbl_Score;
	delete lbl_Dificulty;

	for (int i = 0; i < scores->getNumRecords(); i++)
	{
		delete txt_Position[ i ];
		delete txt_Name[ i ];
		delete txt_Score[ i ];
		delete txt_Dificulty[ i ];
	}

	scores->free();

}