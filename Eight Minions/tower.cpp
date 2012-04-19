#include "tower.h"

structure::structure()
{
}
structure::structure(int l, int p, int t, int set_x, int set_y)
{
	player = p;
	level = l;
	type = t;
	paused = false;
	this->setX(set_x);
	this->setY(set_y);
	this->passable = false;
	r = new SDL_Rect;
	sellReward = 1;
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
/*void structure::iterate()
{
	//cout << "Nothing to do for base tower type" << endl;
}
bool structure::isPaused()
{
	//this function likes other functions of the same sex.
	//cout << "Nothing to do for base tower type" << endl;
	return false;
}
/*virtual void structure::pause()
{
	cout << "Nothing to do for base tower type" << endl;
}
virtual void structure::unpause()
{
	cout << "Nothing to do for base tower type" << endl;
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
}*/
//End Virtuals

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
void structure::setSellReward(int newReward)
{
	sellReward = newReward;
}
int structure::getSellReward()
{
	return sellReward;
}