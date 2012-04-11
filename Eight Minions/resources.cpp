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
