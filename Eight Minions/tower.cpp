#include "tower.h"

structure::structure()
{
}
structure::structure(int l, int p, int t, int set_x, int set_y)
{
	player = p;
	level = l;
	type = t;
	this->setX(set_x);
	this->setY(set_y);
	img = IMG_Load("tower.png");
	r = new SDL_Rect;
}
int structure::getLevel()
{
	return this->level;
}
int structure::getType()
{
	return this->type;
}
int structure::setType(int newType)
{
	type = newType;
	return type;
}
structure::~structure()
{
}
void structure::displayTower(SDL_Surface *screen)
{
	if(img != NULL)
	{
		this->r->x = (GRID_SIZE * this->getX()) + BOARD_X_OFFSET;
		this->r->y = (GRID_SIZE * this->getY()) + BOARD_Y_OFFSET;
		SDL_BlitSurface(this->img, NULL, screen, r);
	}
}
int structure::getPlayer(){
	return player;
}
int structure::setLevel(int newLevel){
	level = newLevel;
	return level;
}
void structure::iterate()
{
	cout << "Nothing to do for base tower type" << endl;
}