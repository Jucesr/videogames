#include "GameState_Menu.h"

//To see description of some variables and methods please read the comments located in Menu.h

Menu::Menu(int nscreen_width, int nscreen_height, SDL_Renderer* nrenderer){

	//This is to keep in the this state until some event change the state
	nextState = STATE_NULL;

	screen_height = nscreen_height;
	screen_width = nscreen_width;

	renderer = nrenderer;

	//Set buttons
	btn_play = new Button(0, 0, "Play", 30, renderer);
	btn_scores = new Button(0, 0, "Scores", 30, renderer);
	btn_credits = new Button( 0, 0, "Credits", 30, renderer);

	btn_play->setPosition(50, ( screen_height - btn_play->getHeight() / 2 ) - 150 );
	btn_scores->setPosition(screen_width/2 - btn_scores->getWidth()/2, (screen_height - btn_scores->getHeight() / 2) - 150 );
	btn_credits->setPosition(screen_width-btn_credits->getWidth()-50, ( screen_height - btn_credits->getHeight() / 2) - 150 );


	//Set titles
	lbl_Title01 = new Label(0,0, "SNAKE", 120, renderer);
	lbl_Title02 = new Label(0,0, "GAME", 120, renderer);
	lbl_Title03 = new Label(0,0, "By Julio Ojeda", 16, renderer);

	lbl_Title01->setPosition((screen_width / 2)- ( lbl_Title01->getWidth() / 2),0);
	lbl_Title02->setPosition((screen_width / 2)- ( lbl_Title01->getWidth() / 2),150);
	lbl_Title03->setPosition((screen_width / 2) + ( lbl_Title01->getWidth() / 6),280);

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