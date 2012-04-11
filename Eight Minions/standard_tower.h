#ifndef STANDARD_TOWER_H
#define STANDARD_TOWER_H
#include "resources.h"
#include "tower.h"
#include "game_host.h"


#define ATTACKCLOSESTTOTOWER	1
#define ATTACKCLOSESTTOBASE		2

#define AREAOFEFFECT			1
#define ATTACKONECREEP			2

class Standard_Tower : public tower
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
private:
	game_host *manager;
	queue<creep*> chosenCreeps;

	int damageValue;
	int attackType;
	double range;

	int coolDownTick;
	int coolDownDuration;

	int attackTick;
	int attackStrategy;
	int attackDuration;
};

#endif