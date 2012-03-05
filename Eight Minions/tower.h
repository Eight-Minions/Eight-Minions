#ifndef TOWER_H
#define TOWER_H
#include "resources.h"
#include "creep.h"

class tower : public location
{	
private:
	int health;
	int level;
	//to go along with level, do we want towers to have experience?
	//and then once they have enough experience, you can upgrade them along a few different specialization trees?
	int type;
	int attackSpeed;
	int attackType;
	SDL_Surface *img;
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