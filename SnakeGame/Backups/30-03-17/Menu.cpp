#include "Menu.h"

Menu::Menu(){

	fontTitle = TTF_OpenFont( "Media\\OpenSans-Regular.ttf", 36 );
	fontButton = TTF_OpenFont( "Media\\OpenSans-Regular.ttf", 20 );
	textColor.r = 0 ;
	textColor.g = 0 ;
	textColor.b = 0 ;

	bigTitle = SDL_CreateTextureFromSurface( renderer, TTF_RenderText_Solid( fontTitle, "Snake Game by Julio Ojeda.", textColor ) );
	btn_play = SDL_CreateTextureFromSurface( renderer, TTF_RenderText_Solid( fontButton, "Play", textColor ) );
	btn_scores = SDL_CreateTextureFromSurface( renderer, TTF_RenderText_Solid( fontButton, "Scores", textColor ) );
	btn_credits = SDL_CreateTextureFromSurface( renderer, TTF_RenderText_Solid( fontButton, "Credits", textColor ) );
	


}

void Menu::handle_events(){

}

void Menu::logic(){

}

void Menu::render(){

	
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { 0, 0, 100, 100 };

	//Set clip rendering dimensions
	/*if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}*/

	//Render to screen
	SDL_RenderCopy( renderer, bigTitle, NULL, &renderQuad );


}