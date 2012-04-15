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
			updateCost();
			return true;
		}
	}
	return false;
}
bool Creep_Tower::changeType(int newType)
{
	if(newType >= NORMCREEPTOWER && newType <= FATTYCREEPTOWER && newType != this->getType())
	{
		
	}
	return false;
}

void Creep_Tower::updateCost()
{
	if(this->getType() == NORMCREEPTOWER)
	{
		cost = normCreepArr[this->getLevel()][4];
	}
	else if(this->getType() == FASTCREEPTOWER)
	{
		cost = fastCreepArr[this->getLevel()][4];
	}
	else if(this->getType() == TANKCREEPTOWER)
	{
		cost = tankCreepArr[this->getLevel()][4];
	}
	else if(this->getType() == SWARMCREEPTOWER)
	{	
		cost = swarmCreepArr[this->getLevel()][4];
	}
	else if(this->getType() == TITANCREEPTOWER)
	{
		cost = titanCreepArr[this->getLevel()][4];
	}
	else if(this->getType() == FATTYCREEPTOWER)
	{
		cost = fattyCreepArr[this->getLevel()][4];
	}
	else
		cost = 0;
}