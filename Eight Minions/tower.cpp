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
	this->passable = false;
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
void structure::displayTower(SDL_Surface *screen, SDL_Surface *image)
{
	if(image != NULL)
	{
		this->r->x = (GRID_SIZE * this->getX()) + BOARD_X_OFFSET;
		this->r->y = (GRID_SIZE * this->getY()) + BOARD_Y_OFFSET;
		SDL_BlitSurface(image, NULL, screen, r);
	}
}
int structure::getPlayer(){
	return player;
}
int structure::setLevel(int newLevel){
	level = newLevel;
	return level;
}
int structure::getCost()
{
	return cost;
}
bool structure::getPassable()
{
	return passable;
}
void structure::setPassable(bool nPass)
{
	passable = nPass;
}

// Virtuals
void structure::iterate()
{
	//cout << "Nothing to do for base tower type" << endl;
}
bool structure::isPaused()
{
	//cout << "Nothing to do for base tower type" << endl;
	return false;
}
void structure::pause()
{
	//cout << "Nothing to do for base tower type" << endl;
}
void structure::unpause()
{
	//cout << "Nothing to do for base tower type" << endl;
}
bool structure::upgrade()
{
	//cout << "Nothing to do for base tower type" << endl;
	return false;
}
bool structure::upgradeClient()
{
	//cout << "Nothing to do for base tower type" << endl;
	return false;
}
bool structure::changeType(int newType)
{
	//cout << "Nothing to do for base tower type" << endl;
	return false;
}
bool structure::changeTypeClient(int newType)
{
	//cout << "Nothing to do for base tower type" << endl;
	return false;
}
//End Virtuals