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
	sellReward = 1;
	alive = true;
}
structure::~structure()
{
	delete r;
}
int structure::getX(){
	return (int)floor(this->x);
}
int structure::getY(){
	return (int)floor(this->y);
}
void structure::setX(double new_x){
	this->x = new_x;
}
void structure::setY(double new_y){
	this->y = new_y;
}

double structure::getXd()
{
	return x;
}
double structure::getYd()
{
	return y;
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
int structure::calculateCost(int cType)
{
	if(cType == NORMTOWER)
	{
		return basicArr[0][4];
	}
	else if(cType == FASTTOWER)
	{
		return fastArr[0][4];
	}
	else if(cType == AOETOWER)
	{
		return areaOfEffectArr[0][4];
	}
	else if(cType == HEAVYTOWER)
	{
		return heavyArr[0][4];
	}
	else if(cType == NORMCREEPTOWER)
	{
		return 40 * normCreepArr[0][4];
	}
	else if(cType == FASTCREEPTOWER)
	{
		return 40 * fastCreepArr[0][4];
	}
	else if(cType == TANKCREEPTOWER)
	{
		return 40 * tankCreepArr[0][4];
	}
	else if(cType == SWARMCREEPTOWER)
	{
		return 40 * swarmCreepArr[0][4];
	}
	else if(cType == TITANCREEPTOWER)
	{
		return 40 * titanCreepArr[0][4];
	}
	else if(cType == FATTYCREEPTOWER)
	{
		return 40 * fattyCreepArr[0][4];
	}
	return 0;
}
// Virtuals
void structure::iterate()
{
	//cout << "Nothing to do for base tower type" << endl;
}
bool structure::isPaused()
{
	return paused;
}
void structure::pause()
{
	paused = true;
}
void structure::unpause()
{
	paused = false;
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
void structure::setSellReward(int newReward)
{
	sellReward = newReward;
}
int structure::getSellReward()
{
	return sellReward;
}
void structure::kill()
{
	alive = false;
}
bool structure::isAlive()
{
	return alive;
}