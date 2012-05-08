#ifndef CREEP_TOWER_H
#define CREEP_TOWER_H

#include "resources.h"
#include "tower.h"
#include "Spawner.h"
#include "gameMap.h"

class Creep_Tower : public structure
{
public:
	Creep_Tower();
	Creep_Tower(int level, int player, int type, int newX, int newY);						//Client Constructor
	Creep_Tower(int level, int player, int type, int newX, int newY, gameMap *nManager);	//Server Constructor
	~Creep_Tower();
	void iterate();
	bool upgrade();
	bool upgradeClient();
	bool changeType(int newType);
	bool changeTypeClient(int newType);
	int updateCost(int uLevel, int uType);
	int getCost();
	void updateSell();
	void displayTower(SDL_Surface *screen, SDL_Surface *image);

	
	bool isPaused();
	void pause();
	void unpause();


private:
	Spawner *cSpawner;
	gameMap *manager;
	SDL_Rect *animRects[4];
	unsigned int animIndex;
	int anim_delay;

	int cost;
	int creepType;
	int creepLevel;
	int delay;
	int maxQueue;
};

#endif