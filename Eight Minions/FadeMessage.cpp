#include "FadeMessage.h"


FadeMessage::FadeMessage( TTF_Font* nFont, int x, int y, int FPS, int nFadeTime, SDL_Color nColor)
{
	r = new SDL_Rect;
	r->x = x;
	r->y = y;
	font = nFont;
	fps = FPS;
	fadeTime = nFadeTime;
	alphaVal = SDL_ALPHA_OPAQUE;
	color = nColor;
	text = NULL;
}

void FadeMessage::setMessage( string nMess )
{
	messageText = nMess;
	if(text != NULL)
		SDL_FreeSurface(text);
	text = TTF_RenderText_Solid(font,messageText.c_str(),color);
	alphaVal = SDL_ALPHA_OPAQUE;
}

void FadeMessage::display( SDL_Surface *screen )
{
	SDL_BlitSurface(text,NULL,screen,r);
	if(!paused)
	{
		alphaVal -= (SDL_ALPHA_OPAQUE / (fadeTime * fps));
		if(alphaVal < 0)
			alphaVal = 0;
		// SDL_SetAlpha( front, SDL_SRCALPHA, alpha );
		SDL_SetAlpha(text,SDL_SRCALPHA, alphaVal);
	}
}

void FadeMessage::checkMouseover( int x, int y )
{
	if(x >= r->x && x <= r->x + text->w && y >= r->y && y <= r->y + text->h)
		paused = true;
	else
		paused = false;
}
