#include "../Header Files/GameState_Scores.h"

Scores::Scores(int nscreen_width, int nscreen_height, SDL_Renderer* nrenderer){

	//These group of variables is used to set the position of the elements on the screen.
	int y_offset;
	int x_offset;
	int y_increment;
	int x_increment;
	int fontSize;
	int fontSizeText;

	//This is to keep in the this state until some event change the state
	nextState = STATE_NULL;

	screen_height = nscreen_height;
	screen_width = nscreen_width;

	renderer = nrenderer;

	//Read scores
	scores = new ScoreRecord();

	//Set buttons
	x_offset = -15;
	y_offset = -15;
	btn_menu = new Button(0, 0, "Menu", 30, renderer);
	btn_menu->setPosition(screen_width - btn_menu->getWidth() + x_offset, screen_height - btn_menu->getHeight() + x_offset);

	//Set content
	x_offset = 15;
	y_offset = 15;
	x_increment = 90;
	y_increment = 40;
	fontSize = 15;
	fontSizeText = 14;

	//Set headers
	lbl_Position = new Label(x_offset + x_increment*0, y_offset + y_increment*0 , "#", fontSize, renderer);
	lbl_Name = new Label(x_offset + x_increment*1, y_offset + y_increment*0, "Name", fontSize, renderer);
	lbl_Score = new Label(x_offset + x_increment*2, y_offset + y_increment*0, "Score", fontSize, renderer);
	//Set blue
	lbl_Position->setFontColor(0,0,255);
	lbl_Name->setFontColor(0,0,255);
	lbl_Score->setFontColor(0,0,255);

	//Set content
	for (int i = 0; i < scores->getNumRecords(); i++)
	{
		txt_Position[ i ] = new Label(x_offset + x_increment*0, y_offset + y_increment* (i+1) , std::to_string(i+1), fontSize, renderer);
		txt_Name[ i ] = new Label(x_offset + x_increment*1, y_offset + y_increment* (i+1) , scores->getName(i), fontSize, renderer);
		txt_Score[ i ] = new Label(x_offset + x_increment*2, y_offset + y_increment* (i+1) , std::to_string(scores->getScore(i)), fontSize, renderer);
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

	for (int i = 0; i < scores->getNumRecords(); i++)
	{
		txt_Position[ i ]->render();
		txt_Name[ i ]->render();
		txt_Score[ i ]->render();
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

	for (int i = 0; i < scores->getNumRecords(); i++)
	{
		delete txt_Position[ i ];
		delete txt_Name[ i ];
		delete txt_Score[ i ];
	}

	scores->free();

}