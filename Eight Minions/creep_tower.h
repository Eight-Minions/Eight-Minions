#ifndef CREEP_TOWER_H
#define CREEP_TOWER_H

#include "resources.h"
#include "tower.h"

class Creep_Tower : public tower{
public:
	Creep_Tower();
	Creep_Tower(int X, int Y);
	void upgradeTower();
	void checkTick();
	void generateCreep();
	void pause();
	void unpause();
private:
	bool paused;
	int tick;
	int interval;
	int cost;
};

#endif