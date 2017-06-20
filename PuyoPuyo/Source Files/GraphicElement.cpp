#include "../Header Files/GraphicElement.h"

int GraphicElement::getWidth(){
	return width;
}

int GraphicElement::getHeight(){
	return height;
}

int GraphicElement::getPositionX(){
	return positionX;
}

int GraphicElement::getPositionY(){
	return positionY;
}

void GraphicElement::setPosition(int x, int y){

	positionX = x;
	positionY = y;

}

void GraphicElement::setText(std::string ntext){

	text = ntext;
	graphicText->loadFromRenderedText(text, textColor, textFont);

	//Update the size
	width = graphicText->getWidth();
	height = graphicText->getHeight();

}

void GraphicElement::setFontColor(int r, int g, int b){
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;
	graphicText->loadFromRenderedText(text, textColor, textFont);

}

std::string GraphicElement::getText(){

	return text;

}