#ifndef STANDARD_TOWER_H
#define STANDARD_TOWER_H
#include "resources.h"
#include "tower.h"
#include "game_host.h"
#include <list>

using std::list;

class Standard_Tower : public tower
{
public:
	Standard_Tower();
	Standard_Tower(int l, int t, int set_x, int set_y);
	Standard_Tower(int l, int t, int set_x, int set_y, game_host *nManager);
	void damageClosestCreep(double radius);
	void damageClosestCreepToPosition(double radius, location position);
	void damageNeighbors(double radius);
	void damageNeighborsNearPosition(double radius, location position);
private:
	game_host *manager;
	int damageValue;
	double range;
	int attackSpeed;
	int attackType;
	int attackStrategy;
};

#endif