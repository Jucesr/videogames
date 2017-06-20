#include "GameState_Credits.h"

Credits::Credits(int nscreen_width, int nscreen_height, SDL_Renderer* nrenderer){

	//This is to keep in the this state until some event change the state
	nextState = STATE_NULL;

	screen_height = nscreen_height;
	screen_width = nscreen_width;

	renderer = nrenderer;

	//Set buttons
	btn_menu = new Button(0, 0, "Menu", 30, renderer);
	btn_menu->setPosition(screen_width - btn_menu->getWidth() - 30, screen_height - btn_menu->getHeight() - 30);

	//Set content
	int x_offset = 50;
	int y_offset = 50;
	int x_increment = 120;
	int y_increment = 40;
	int fontSize = 24;


	int fontSizeText = 18;

	lbl_Author = new Label(x_offset, y_offset + y_increment*0 , "Author: ", fontSize, renderer);
	txt_Author = new Label(x_offset + x_increment, y_offset + y_increment*0, "Julio Cesar Ojeda Magdaleno", fontSize, renderer);
	lbl_Author->setFontColor(255,0,0);

	lbl_Title = new Label(x_offset, y_offset + y_increment*1 , "Title: ", fontSize, renderer);
	txt_Title = new Label(x_offset + x_increment, y_offset + y_increment*1, "Snake Game", fontSize, renderer);
	lbl_Title->setFontColor(255,0,0);

	lbl_Date = new Label(x_offset, y_offset + y_increment*2 , "Date: ", fontSize, renderer);
	txt_Date = new Label(x_offset + x_increment, y_offset + y_increment*2, "April 3, 2017", fontSize, renderer);
	lbl_Date->setFontColor(255,0,0);

	lbl_Contact = new Label(x_offset, y_offset + y_increment*3 , "Contact: ", fontSize, renderer);
	txt_Contact = new Label(x_offset + x_increment, y_offset + y_increment*3, "jcom.94m@gmail.com", fontSize, renderer);
	lbl_Contact->setFontColor(255,0,0);

	lbl_Text01 = new Label(x_offset, y_offset + y_increment*6 , "This program was written to show my programming skills.", fontSizeText, renderer);
	lbl_Text02 = new Label(x_offset, y_offset + y_increment*7 , "It was written only by the author Julio Cesar Ojeda Magdaleno.", fontSizeText, renderer);
	lbl_Text03 = new Label(x_offset, y_offset + y_increment*8 , "Around 85% of the code was designed and coded by the author.", fontSizeText, renderer);
	lbl_Text04 = new Label(x_offset, y_offset + y_increment*9 , "Around 15% of the code was obtained from www.lazyfoo.net", fontSizeText, renderer);
	lbl_Text05 = new Label(x_offset, y_offset + y_increment*10 , "Music and sound effects were obtained from www.freesound.org", fontSizeText, renderer);


}

bool Credits::getError(){

	return error;

}

void Credits::logic(){

	//Check if a button is pressed and change the main state
	if ( btn_menu->getState() == BUTTON_STATE_ON )
	{
		nextState = STATE_MENU;
	}

}

void Credits::render(){

	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	
	//Render elements
	lbl_Author->render();
	txt_Author->render();

	lbl_Title->render();
	txt_Title->render();

	lbl_Date->render();
	txt_Date->render();

	lbl_Contact->render();
	txt_Contact->render();

	lbl_Text01->render();
	lbl_Text02->render();
	lbl_Text03->render();
	lbl_Text04->render();
	lbl_Text05->render();

	btn_menu->render();

	//Update screen
	SDL_RenderPresent( renderer );


}

void Credits::handle_events(){

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

Credits::~Credits(){

	delete btn_menu;

	delete lbl_Author;
	delete txt_Author;

	delete lbl_Title;
	delete txt_Title;

	delete lbl_Date;
	delete txt_Date;

	delete lbl_Contact;
	delete txt_Contact;

	delete lbl_Text01;
	delete lbl_Text02;
	delete lbl_Text03;
	delete lbl_Text04;
	delete lbl_Text05;

}