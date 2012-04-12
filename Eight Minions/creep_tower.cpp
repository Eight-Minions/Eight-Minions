#include "creep_tower.h"

Creep_Tower::Creep_Tower() : tower()
{
}
Creep_Tower::Creep_Tower(int player, int new_x, int new_y) : tower (CREEPTOWERSTARTLEVEL, player, -1, new_x, new_y)
{
}
Creep_Tower::Creep_Tower(int player, int new_x, int new_y, game_host *nManager) : tower (CREEPTOWERSTARTLEVEL, player, -1, new_x, new_y)
{
	manager = nManager;
}
void Creep_Tower::unpause()
{
	paused = false;
}
void Creep_Tower::pause()
{
	paused = true;
}
void Creep_Tower::spawn()
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