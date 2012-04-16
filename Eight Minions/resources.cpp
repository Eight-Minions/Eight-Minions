#include "resources.h"

location::location(){
	x = 0;
	y = 0;
}
location::location(int new_x, int new_y){
	x = new_x;
	y = new_y;
}
location::~location(){
}
int location::getX(){
	return (int)floor(this->x);
}
int location::getY(){
	return (int)floor(this->y);
}
void location::setX(double new_x){
	this->x = new_x;
}
void location::setY(double new_y){
	this->y = new_y;
}

double location::getXd()
{
	return x;
}

double location::getYd()
{
	return y;
}

coord location::gC( int x, int y )
{
	coord n = {x,y};
	return n;
}

SDL_Rect * newRect( int x, int y, int w, int h )
{
	SDL_Rect *temp = new SDL_Rect;
	temp->x = x;
	temp->y = y;
	temp->h = h;
	temp->w = w;
	return temp;
}

SDL_Color makeColor( int r, int g, int b )
{
	SDL_Color n = {r,g,b};
	return n;
}

SDL_Surface *LoadImageCK(string filename)
{
	SDL_Surface *newImage = IMG_Load(filename.c_str());
	SDL_Surface *keyedImage = NULL;

	if(newImage != NULL)
	{
		keyedImage = SDL_DisplayFormat(newImage);

		SDL_FreeSurface(newImage);

		if(keyedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(keyedImage->format, 0xFF, 0, 0xFF);

			SDL_SetColorKey(keyedImage, SDL_SRCCOLORKEY, colorkey);

			return keyedImage;
		}
		else
		{
			return NULL;
		}

	}
	else
	{
		return NULL;
	}
}


