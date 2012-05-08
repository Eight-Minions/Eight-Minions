#ifndef MINE_H
#define MINE_H

#include "resources.h"
#include "standard_tower.h"

class gameMap;

class Mine : public structure
{
public:
	Mine();
	Mine(int level, int player, int type, int set_x, int set_y);
	Mine(int level, int player, int type, int set_x, int set_y, gameMap *nManager);
	~Mine();

	void iterate();
	bool isOnTop();
	void choose();
	void doDamage();

	bool upgrade();
	int updateCost(int cLevel);
	void updateStats(int cLevel);

	int getCost();

private:
	gameMap *manager;
	queue<int> chosenCreeps;

	int cost;
	int damageValue;
	int armorPen;
	int range;

};
#endif