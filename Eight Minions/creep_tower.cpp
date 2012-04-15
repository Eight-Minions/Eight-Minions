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
			return true;
		}
	}
	return false;
}
bool Creep_Tower::changeType()
{

	return false;
}