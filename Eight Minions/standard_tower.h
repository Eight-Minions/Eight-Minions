#ifndef STANDARD_TOWER_H
#define STANDARD_TOWER_H
#include "resources.h"
#include "tower.h"
#include "UpdMess.h"
#include "gameMap.h"

class gameMap;

class Standard_Tower : public structure
{
public:
	Standard_Tower();
	Standard_Tower(int l, int p, int t, int set_x, int set_y);
	Standard_Tower(int l, int p, int t, int set_x, int set_y, gameMap *nManager);
	void chooseClosestCreep(double radius);
	void chooseClosestCreepToPosition(double radius, coord position);
	void chooseNeighbors(double radius);
	void chooseNeighborsNearPosition(double radius, coord position);

	bool choose();
	bool doDamage();
	void iterate();

	bool upgrade();
	bool upgradeClient();
	bool changeType(int newType);
	int getID();
	int getCost();
	int updateCost(int costLevel, int costType);
	void updateSell();
private:
	gameMap *manager;
	vector<int> chosenCreeps;

	int attackType;
	int damageValue;
	int armorPenetration;
	int range;
	int cost;

	int coolDownTick;
	int coolDownDuration;

	int attackTick;
	int attackStrategy;
	int attackDuration;

	bool waiting;
	bool cooldown;
};

#endif