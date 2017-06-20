#include "../Header Files/TextBox.h"

TextBox::TextBox(int npositionX, int npositionY, std::string ntext, int fontSize, SDL_Renderer* renderer){
	positionX = npositionX;
	positionY = npositionY;
	text = ntext;

	//This is used only be typeable when it is being focused.
	focus = false;
	hasValidText = false;
	textFont = TTF_OpenFont( "Resource Files\\OpenSans-Regular.ttf", fontSize );

	//Enable text input
	SDL_StartTextInput();


	graphicText = new Texture(renderer);

	//Set default color: black
	textColor.r = 0 ;
	textColor.g = 0 ;
	textColor.b = 0 ;

	graphicText->loadFromRenderedText(text, textColor, textFont);
	
	width = graphicText->getWidth();
	height = graphicText->getHeight();
}

void TextBox::render(){

	//I could have changed the render method of the button so it can have a square with a background color. 
	//For the purpose of this program it will stay just like this
	graphicText->render(positionX, positionY);

}

int TextBox::getType(){

	return ELEMENT_TEXT_BOX;

}

void TextBox::handle_event(SDL_Event* e){


	
	if( focus )
	{
		//Works as a textbox
	
		//Special key input
		if( e->type == SDL_KEYDOWN )
		{
			//Handle backspace
			if( e->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0 )
			{
				//lop off character
				text.pop_back();
				updateText = true;
			}
			//Handle copy
			else if( e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
			{
				SDL_SetClipboardText( text.c_str() );
			}
			//Handle paste
			else if( e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
			{
				text = SDL_GetClipboardText();
				updateText = true;
			}
			//When the user presses enter it means it has finished
			else if (e->key.keysym.sym == SDLK_RETURN){

				focus = false;
				updateText = false;
				if ( !hasValidText )
					setText("Invalid Text");

			}
		}
		//Special text input event
		else if( e->type == SDL_TEXTINPUT )
		{
			//Not copy or pasting
			if( !( ( e->text.text[ 0 ] == 'c' || e->text.text[ 0 ] == 'C' ) && ( e->text.text[ 0 ] == 'v' || e->text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
			{
				//Append character
				text += e->text.text;
				updateText = true;
			}

		}

		//Rerender text if needed
		if( updateText )
		{
			//Text is not empty
			if( text != "" && text != " " )
			{
				//Render new text
				hasValidText = true;
				setText(text);
	
			}
			//Text is empty
			else
			{
				//Render space texture
				hasValidText = false;
				setText(" ");
			}
		}
	}else
	{
		//Works as a button
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


			//Mouse is inside button
			if( inside )
			{
			
				switch( e->type )
				{
            
					case SDL_MOUSEBUTTONDOWN:

						focus = true;
						setText(" ");

					break;
                
				}
			}

		}
	}
}

bool TextBox::getFocus(){

	return focus;

}

bool TextBox::isValid(){

	if ( hasValidText && !focus)
		return true;
	else
		return false;

}

TextBox::~TextBox(){

	delete graphicText;
	graphicText = NULL;
	textFont = NULL;

	SDL_StopTextInput();

}

