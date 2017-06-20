#include "../Header Files/Puyo.h"

Puyo::Puyo(int nposX, int nposY, int nwidth, int nheight, int ntype, Texture* ngraphicSurface, int nxrenderOffset, int nyrenderOffset){

	
	posX = nposX;
	posY = nposY;
	state = false;
	width = nwidth;
	heigth = nheight;
	type = ntype;
	graphicSurface = ngraphicSurface;
	xrenderOffset = nxrenderOffset;
	yrenderOffset = nyrenderOffset;

}


void Puyo::render(){

	SDL_Rect clip;

	//Puyo sprite size
	clip.w = width;
	clip.h = heigth;
	clip.y = 0;

	switch (type)
	{
		case PUYO_RED:

			clip.x = 0;

		break;

		case PUYO_BLUE:

			clip.x = 45;

		break;

		case PUYO_YELLOW:

			clip.x = 90;

		break;

		case PUYO_PURPLE:

			clip.x = 135;

		break;


	}

	graphicSurface->render(posX*width + xrenderOffset, posY*heigth + yrenderOffset, &clip);

}



