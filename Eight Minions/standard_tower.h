#ifndef STANDARD_TOWER_H
#define STANDARD_TOWER_H
#include "resources.h"
#include "tower.h"

class Standard_Tower : public tower{
public:
	Standard_Tower();
	Standard_Tower(int l, int t, int set_x, int set_y);
	
	void damageNeighbors(int radius);
	void damageClosestCreep(int radius);
	void damageClosestCreepToPosition(int radius, location position);
private:
	int attackSpeed;
	int attackType;
	int attackStrategy;
};
#endif