#include "Label.h"

Label::Label(int npositionX, int npositionY, std::string ntext, int fontSize, SDL_Renderer* renderer){
	positionX = npositionX;
	positionY = npositionY;
	text = ntext;
	textFont = TTF_OpenFont( "Media\\OpenSans-Regular.ttf", fontSize );


	graphicText = new Texture(renderer);

	//Set default color: black
	textColor.r = 0 ;
	textColor.g = 0 ;
	textColor.b = 0 ;

	graphicText->loadFromRenderedText(text, textColor, textFont);
	
	width = graphicText->getWidth();
	height = graphicText->getHeight();
}

void Label::render(){

	graphicText->render(positionX, positionY);

}

int Label::getType(){

	return ELEMENT_LABEL;

}

Label::~Label(){

	delete graphicText;

	graphicText = NULL;
	textFont = NULL;

}


