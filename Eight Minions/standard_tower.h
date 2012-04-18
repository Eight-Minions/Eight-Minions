#ifndef STANDARD_TOWER_H
#define STANDARD_TOWER_H
#include "resources.h"
#include "tower.h"
#include "game_host.h"
#include "UpdMess.h"

class Standard_Tower : public structure
{
public:
	Standard_Tower();
	Standard_Tower(int l, int p, int t, int set_x, int set_y);
	Standard_Tower(int l, int p, int t, int set_x, int set_y, game_host *nManager);
	void chooseClosestCreep(double radius);
	void chooseClosestCreepToPosition(double radius, location position);
	void chooseNeighbors(double radius);
	void chooseNeighborsNearPosition(double radius, location position);

	bool choose();
	bool doDamage();
	void iterate();

	bool upgrade();
	bool changeType(int newType);
	int getID();
	int getCost();
	int updateCost(int costLevel, int costType);
private:
	game_host *manager;
	queue<int> chosenCreeps;

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
};

#endif