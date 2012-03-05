#ifndef TOWER_H
#define TOWER_H
#include "resources.h"
#include "creep.h"

class tower : public location
{	
private:
	int level;
	int type;
	int attackSpeed;
	int attackType;
public:
	tower(int health, int level, int type, int x , int y);
	~tower();
	int getLevel();
	int getType();

	void damageNeighbors(int radius);
	void damageClosestCreep(int radius);
	// TL: How would you want to do attacks?
	// TL: We could do a radius and a damageNeighbors(int radius);
	// TL: It could attack just one creep damageClosestCreep(int radius);
	// TL: We could implement both and have them be differnt types.
};


#endif 