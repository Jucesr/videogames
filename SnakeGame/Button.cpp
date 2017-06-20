#include "Button.h"

Button::Button(int npositionX, int npositionY, std::string ntext, int fontSize, SDL_Renderer* renderer){
	positionX = npositionX;
	positionY = npositionY;
	text = ntext;
	state = BUTTON_STATE_OFF;
	//over = false;
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

void Button::render(){

	//I could have changed the render method of the button so it can have a square with a background color. 
	//For the purpose of this program it will stay just like this
	graphicText->render(positionX, positionY);

}

void Button::handle_event(SDL_Event* e){


	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < positionX )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > positionX + width )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < positionY )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > positionY + height )
		{
			inside = false;
		}


		//Mouse is outside button
        if( !inside )
        {
			//Set button text black
			if( state == BUTTON_STATE_OVER || state == BUTTON_STATE_CLICK_DOWN)
			{
				setFontColor(0,0,0);
				state = BUTTON_STATE_OFF;
				//over = false;
				//pressed = false;
			}
	
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:

					if ( state == BUTTON_STATE_OFF)
					{
						//Set color red
						setFontColor(255,0,0);
						state = BUTTON_STATE_OVER;
					}

                break;
            
                case SDL_MOUSEBUTTONDOWN:

					if( state == BUTTON_STATE_OVER)
					{
						//Set color green
						setFontColor(0,255,0);
						state = BUTTON_STATE_CLICK_DOWN;

					}else if( state == BUTTON_STATE_ON )
					{
						state = BUTTON_STATE_OFF;
						//Set color red
						setFontColor(255,0,0);
					}

                break;
                
                case SDL_MOUSEBUTTONUP:

					if( state == BUTTON_STATE_CLICK_DOWN)
					{
						//Set color blue
						setFontColor(0,0,255);
						state = BUTTON_STATE_ON;

					}
					
                break;
            }
        }

	}

}

int Button::getState(){

	return state;

}

int Button::getType(){

	return ELEMENT_BUTTON;

}

Button::~Button(){

	delete graphicText;

	graphicText = NULL;
	textFont = NULL;

}





