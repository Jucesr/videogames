#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include <String>

class Texture
{
	public:
		//Initializes variables
		Texture(SDL_Renderer* renderer);

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFromFile( std::string path);
		
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font *font );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		SDL_Renderer* renderer;


	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif