#ifndef CREEP_TOWER_H
#define CREEP_TOWER_H

#include "resources.h"
#include "tower.h"
#include "game_host.h"
#include "Spawner.h"

class Creep_Tower : public structure
{
public:
	Creep_Tower();
	Creep_Tower(int level, int player, int type, int newX, int newY);						//Client Constructor
	Creep_Tower(int level, int player, int type, int newX, int newY, game_host *nManager);	//Server Constructor
	void iterate();
	bool upgrade();
	bool upgradeClient();
	bool changeType(int newType);
	bool changeTypeClient(int newType);
	int updateCost(int uLevel, int uType);
	int getCost();
	void updateSell();

	/*
	bool isPaused();
	void pause();
	void unpause();
	*/
private:
	Spawner *cSpawner;
	game_host *manager;

	int cost;
	int creepType;
	int creepLevel;
	int delay;
	int maxQueue;

	//bool paused;
};

#endif