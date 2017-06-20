#include "../Header Files/GameState_Menu.h"

//To see description of some variables and methods please read the comments located in Menu.h

Menu::Menu(int nscreen_width, int nscreen_height, SDL_Renderer* nrenderer){

	//These group of variables is used to set the position of the elements on the screen.
	int y_offset;
	int x_offset;
	int y_increment;
	int x_increment;

	//This is to keep in the this state until some event change the state
	nextState = STATE_NULL;

	screen_height = nscreen_height;
	screen_width = nscreen_width;

	renderer = nrenderer;

	//Set buttons
	btn_play = new Button(0, 0, "Play", 35, renderer);
	btn_scores = new Button(0, 0, "Scores", 35, renderer);
	btn_credits = new Button( 0, 0, "Credits", 35, renderer);

	//Set position -> ( x, y )
	y_offset = -100;
	y_increment = -70;
	x_increment = 0;
	x_offset = 0;
	
	btn_credits->setPosition(screen_width/2 - btn_credits->getWidth()/2 + x_offset + ( x_increment * 0 ), ( screen_height - btn_credits->getHeight() / 2) + y_offset + ( y_increment * 0 ) );	
	btn_scores->setPosition(screen_width/2 - btn_scores->getWidth()/2 + x_offset + ( x_increment * 1 ), (screen_height - btn_scores->getHeight() / 2) + y_offset + ( y_increment * 1 )  );
	btn_play->setPosition(screen_width/2 - btn_play->getWidth()/2 + x_offset + ( x_increment * 2 ), ( screen_height - btn_play->getHeight() / 2 ) + y_offset + ( y_increment * 2 )  );


	//Set titles
	lbl_Title01 = new Label(0,0, "PUYO", 85, renderer);
	lbl_Title02 = new Label(0,0, "GAME", 85, renderer);
	lbl_Title03 = new Label(0,0, "By Julio Ojeda", 14, renderer);

	y_offset = 20;
	y_increment = 100;
	x_increment = 0;
	x_offset = 0;

	lbl_Title01->setPosition((screen_width / 2) - ( lbl_Title01->getWidth() / 2), y_offset + ( y_increment * 0 ));
	lbl_Title02->setPosition((screen_width / 2) - ( lbl_Title01->getWidth() / 2), y_offset + ( y_increment * 1 ));
	lbl_Title03->setPosition((screen_width / 2) + ( lbl_Title01->getWidth() / 6), y_offset + ( y_increment * 2 ));

}



bool Menu::getError(){

	return error;

}

void Menu::handle_events(){

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
		btn_play->handle_event(&e);
		btn_scores->handle_event(&e);
		btn_credits->handle_event(&e);
		

	}
}

void Menu::logic(){

	//Check if a button is pressed and change the main state
	if ( btn_play->getState() == BUTTON_STATE_ON )
	{
		nextState = STATE_GAME_RUNNING;
	}
	if ( btn_credits->getState() == BUTTON_STATE_ON )
	{
		nextState = STATE_CREDITS;
	}
	if ( btn_scores->getState() == BUTTON_STATE_ON )
	{
		nextState = STATE_SCORES;
	}
}

void Menu::render(){

	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	
	//Render elements of the menu
	lbl_Title01->render();
	lbl_Title02->render();
	lbl_Title03->render();

	btn_play->render();
	btn_scores->render();
	btn_credits->render();

	//Update screen
	SDL_RenderPresent( renderer );


}

Menu::~Menu(){
	delete btn_play;
	delete btn_scores;
	delete btn_credits;
	delete lbl_Title01;
	delete lbl_Title02;
	delete lbl_Title03;

	btn_play = NULL;
	btn_scores = NULL;
	btn_credits = NULL;
	lbl_Title01 = NULL;
	lbl_Title02 = NULL;
	lbl_Title03 = NULL;
}