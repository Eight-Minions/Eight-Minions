#include "creep_tower.h"

Creep_Tower::Creep_Tower() : structure()
{
}
Creep_Tower::Creep_Tower(int level, int player, int type, int new_x, int new_y) : structure (level, player, type, new_x, new_y)
{	
	this->setPassable(true);
	this->unpause();
	updateSell();
}
Creep_Tower::Creep_Tower(int level, int player, int type, int new_x, int new_y, game_host *nManager) : structure (level, player, type, new_x, new_y)
{
	manager = nManager;
	cost = updateCost(level, type);
	cSpawner = new Spawner(nManager, player, true, NORM, 1, gC(this->getX(), this->getY()));
	cSpawner->setDelay(normCreepArr[CREEPTOWERSTARTLEVEL][5] * MAX_FPS + 30);
	updateSell();
	this->unpause();
	this->setPassable(true);

}
Creep_Tower::~Creep_Tower()
{
	delete cSpawner;
}
void Creep_Tower::iterate()
{
	if(!this->isPaused())
	{
		cSpawner->iterate();
	}
}
bool Creep_Tower::upgrade()
{
	if(this->getLevel() < 5)
	{
		if(this->cost < this->manager->getPlayer(this->getPlayer())->getMoney())
		{
			
			this->manager->getPlayer(this->getPlayer())->spendMoney(cost);
			int tempType = cSpawner->getType();
			delete cSpawner;
			cSpawner = new Spawner(this->manager, this->getPlayer(), true, tempType, this->getLevel() + 1, gC(this->getX(), this->getY()));
			//cSpawner->setDelay((delay * (11 - getLevel())) / 10);
			cost = updateCost(this->getLevel()+1, this->getType());
			this->setLevel(this->getLevel() + 1);
			updateSell();
			return true;
		}
	}
	return false;
}
bool Creep_Tower::upgradeClient()
{
	if(this->getLevel() < 5)
	{
		cost = updateCost(this->getLevel()+1, this->getType());
		this->setLevel(this->getLevel() + 1);
		updateSell();
		return true;
	}
	return false;
}
bool Creep_Tower::changeType(int newType)
{
	int costToSwitch;
	if(newType >= NORMCREEPTOWER && newType <= FATTYCREEPTOWER && newType != this->getType())
	{
		if(updateCost(this->getLevel(), newType) <= this->manager->getPlayer(this->getPlayer())->getMoney())
		{
			this->manager->getPlayer(this->getPlayer())->spendMoney(updateCost(this->getLevel(), newType));
			delete cSpawner;
			cSpawner = new Spawner(this->manager, this->getPlayer(), true, newType - GETCREEPTYPE, this->getLevel(),gC(this->getX(), this->getY()));
			this->cost = updateCost(this->getLevel()+1, newType);
			this->setType(newType);
			updateSell();
			return true;
		}
	}
	return false;
}
bool Creep_Tower::changeTypeClient(int newType)
{
	if(newType >= NORMCREEPTOWER && newType <= FATTYCREEPTOWER && newType != this->getType())
	{
		cost = updateCost(this->getLevel()+1, newType);
		this->setType(newType);
		updateSell();
		return true;
	}
	return false;
}
int Creep_Tower::updateCost(int uLevel, int uType)
{
	uLevel = uLevel - 1;
	if(uLevel < 5 && uLevel >= 0)
	{
		if(uType == NORMCREEPTOWER)
		{
			return normCreepArr[uLevel][4] * 20;
		}
		else if(uType == FASTCREEPTOWER)
		{
			return fastCreepArr[uLevel][4] * 20;
		}
		else if(uType == TANKCREEPTOWER)
		{
			return tankCreepArr[uLevel][4] * 20;
		}
		else if(uType == SWARMCREEPTOWER)
		{	
			return swarmCreepArr[uLevel][4] * 20;
		}
		else if(uType == TITANCREEPTOWER)
		{
			return titanCreepArr[uLevel][4] * 20;
		}
		else if(uType == FATTYCREEPTOWER)
		{
			return fattyCreepArr[uLevel][4] * 20;
		}
		else
			return 0;
	}
	else 
		return 0;
}
int Creep_Tower::getCost()
{
	return this->cost;
}
void Creep_Tower::updateSell()
{
	int newSell = 0;
	for(int i = 1; i <= getLevel(); i++)
	{
		newSell += updateCost(i, getType());
	}
	this->setSellReward(((int)(newSell / 2)));
}

bool Creep_Tower::isPaused()
{
	return paused;
}
void Creep_Tower::pause()
{
	paused = true;
}
void Creep_Tower::unpause()
{
	paused = false;
}

void Creep_Tower::displayTower(SDL_Surface *screen, SDL_Surface *image)
{


	if(image != NULL)
	{
		getr()->x = (GRID_SIZE * this->getX()) + BOARD_X_OFFSET;
		getr()->y = (GRID_SIZE * this->getY()) + BOARD_Y_OFFSET;
		SDL_BlitSurface(image, animRects[animIndex], screen, getr());
	}
}