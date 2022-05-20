
#include "game.h"
//#include <iostream>

bool LTexture::quit = false;
bool LTexture::die = true;
 short LTexture::score = 0;
SDL_Window* LTexture::gWindow = NULL;
SDL_Renderer* LTexture::gRenderer = NULL;
SDL_Event LTexture::event;

LTexture::LTexture(){
	Texture = NULL;
}

 short LTexture::getWidth(){
	return textureWidth;
}

 short LTexture::getHeight(){
	return textureHeight;
}

void LTexture::free(){
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}

void LTexture::Render( short x,  short y,  short angle, SDL_Rect* clip, SDL_RendererFlip flip){
	SDL_Rect Rec_Render = { x, y, textureWidth, textureHeight };

    if( clip != NULL )
	{
		Rec_Render.w = clip->w ;
		Rec_Render.h = clip->h ;
	}

    SDL_RenderCopyEx( gRenderer, Texture, clip, &Rec_Render, angle, NULL, flip );
}

bool LTexture::Load(string path,double scale)
{
	free();

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x00, 0xFF, 0xFF ) );

        Texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( Texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			textureWidth = (loadedSurface->w)*scale ;
			textureHeight = (loadedSurface->h)*scale;
		}

		SDL_FreeSurface( loadedSurface );
	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return Texture != NULL;

}

bool LTexture::isNULL()
{
    if (Texture == NULL) return true;
    return false;
}

void position::setPosition(const short int x, const short int y)
{
    this->x = x;
    this->y = y;
}
