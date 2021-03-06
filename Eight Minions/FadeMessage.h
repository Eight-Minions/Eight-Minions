#ifndef FADEMESSAGE_H
#define FADEMESSAGE_H

#ifdef WIN32
#include "SDL.h"
#include "SDL_ttf.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#endif
#include <string>

using std::string;

class FadeMessage
{
private:
	SDL_Surface *text;
	SDL_Rect *r;
	string messageText;
	int alphaVal;

	TTF_Font *font;
	SDL_Color color;
	int fadeTime;
	int fps;

	bool paused;
public:
	FadeMessage(TTF_Font* nFont, int x, int y, int FPS, int nFadeTime, SDL_Color nColor);
	~FadeMessage();

	void setMessage(string nMess);
	void display(SDL_Surface *screen);

	void checkMouseover(int x, int y);
};
#endif