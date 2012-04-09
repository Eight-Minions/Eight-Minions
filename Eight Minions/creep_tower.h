#ifndef CREEP_TOWER_H
#define CREEP_TOWER_H

#include "resources.h"
#include "tower.h"
#include "game_host.h"
#include "Spawner.h"

class game_host;
class Spawner;

class Creep_Tower : public tower
{
public:
	Creep_Tower();
	Creep_Tower(int X, int Y, game_host *manager);
	void upgradeTower();
	void checkTick();
	void generateCreep();
	void pause();
	void unpause();

	friend Spawner;
private:
	Spawner *cSpawner;
	bool paused;
	int cost;
};

#endif