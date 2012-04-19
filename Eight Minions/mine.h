#ifndef MINE_H
#define MINE_H

#include "resources.h"
#include "standard_tower.h"

class Mine : public structure
{
public:
	Mine();
	Mine(int level, int player, int type, int set_x, int set_y);
	Mine(int level, int player, int type, int set_x, int set_y, game_host *nManager);
	~Mine();

	void iterate();
	bool isOnTop();
	void choose();
	void doDamage();

	bool upgrade();
	int updateCost(int cLevel);

	int getCost();
private:
	game_host *manager;
	queue<int> chosenCreeps;

	int cost;
	int damageValue;
	int range;
};
#endif