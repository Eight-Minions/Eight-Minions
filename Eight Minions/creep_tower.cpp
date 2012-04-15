#include "creep_tower.h"

Creep_Tower::Creep_Tower() : structure()
{
}
Creep_Tower::Creep_Tower(int level, int player, int type, int new_x, int new_y) : structure (CREEPTOWERSTARTLEVEL, player, type, new_x, new_y)
{	
}
Creep_Tower::Creep_Tower(int level, int player, int type, int new_x, int new_y, game_host *nManager) : structure (CREEPTOWERSTARTLEVEL, player, type, new_x, new_y)
{
	manager = nManager;
	cSpawner = new Spawner(nManager, player, true, NORM, 1);
	cSpawner->setDelay(normCreepArr[CREEPTOWERSTARTLEVEL][5] * MAX_FPS);
	paused = true;
}
void Creep_Tower::unpause()
{
	paused = false;
}
void Creep_Tower::pause()
{
	paused = true;
}
void Creep_Tower::iterate()
{
	if(!paused)
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
			cSpawner = new Spawner(this->manager, this->getPlayer(), true, cSpawner->getType(), cSpawner->getLevel() + 1);
			cSpawner->setDelay((delay * MAX_FPS)*(1.1-((this->getLevel())/10)));
			cost = updateCost(this->getLevel()+1, this->getType());
			return true;
		}
	}
	return false;
}
bool Creep_Tower::changeType(int newType)
{
	int costToSwitch;
	if(newType >= NORMCREEPTOWER && newType <= FATTYCREEPTOWER && newType != this->getType())
	{
		if(updateCost(this->getLevel(), newType) < this->manager->getPlayer(this->getPlayer())->getMoney())
		{
			this->manager->getPlayer(this->getPlayer())->spendMoney(updateCost(this->getLevel(), newType));
			cSpawner = new Spawner(this->manager, this->getPlayer(), true, cSpawner->getType(), cSpawner->getLevel());
			cost = updateCost(this->getLevel()+1, newType);
			this->setType(newType);
			return true;
		}
	}
	return false;
}
int Creep_Tower::updateCost(int uLevel, int uType)
{
	if(uLevel < 5)
	{
		if(uType == NORMCREEPTOWER)
		{
			return normCreepArr[uLevel][4];
		}
		else if(uType == FASTCREEPTOWER)
		{
			return fastCreepArr[uLevel][4];
		}
		else if(uType == TANKCREEPTOWER)
		{
			return tankCreepArr[uLevel][4];
		}
		else if(uType == SWARMCREEPTOWER)
		{	
			return swarmCreepArr[uLevel][4];
		}
		else if(uType == TITANCREEPTOWER)
		{
			return titanCreepArr[uLevel][4];
		}
		else if(uType == FATTYCREEPTOWER)
		{
			return fattyCreepArr[uLevel][4];
		}
		else
			return 0;
	}
	else 
		return 0;
}