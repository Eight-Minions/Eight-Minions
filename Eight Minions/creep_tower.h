#ifndef CREEP_TOWER_H
#define CREEP_TOWER_H

#include "resources.h"
#include "tower.h"
#include "game_host.h"
#include "Spawner.h"

class Creep_Tower : public tower
{
public:
	Creep_Tower();
	Creep_Tower(int newX, int newY, game_host *nManager);
	void upgradeTower();
	void checkTick();
	void generateCreep();
	void pause();
	void unpause();

private:
	Spawner *cSpawner;
	game_host *manager;
	bool paused;
	int cost;
};

#endif