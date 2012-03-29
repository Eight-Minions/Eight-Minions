#ifndef TOWER_H
#define TOWER_H
#include "resources.h"
#include "creep.h"

class tower : public location
{	
private:
	int level;
	//J:
	//to go along with level, do we want towers to have experience?
	//and then once they have enough experience, you can upgrade them along a few different specialization trees?
	//TL:
	//I thought we would do money or something. That seems to be typical. Money for killed creeps allow and then allow upgrading.
	//That will be for later though.
	int type;
	int attackSpeed;
	int attackType;
	SDL_Surface *img;
	SDL_Rect *r; 

public:
	tower();
	tower(int level, int type, int x , int y);
	~tower();
	int getLevel();
	int getType();
	int setType(int newType);

	void displayTower(SDL_Surface *screen);

	void damageNeighbors(int radius);
	void damageClosestCreep(int radius);
	void damageClosestCreepToPosition(int radius, location position);
	// TL: How would you want to do attacks?
	// TL: We could do a radius and a damageNeighbors(int radius);
	// TL: It could attack just one creep damageClosestCreep(int radius);
	// TL: We could implement both and have them be differnt types.
	// J: we should have attackStrongest, attackNearest, AttackFarthest, and attackClosestToBase which i think 
	//		would be most relevant	
	//TL: That sounds good to me. I'll work on these three for now.
	//TL: Maybe an Attack(); and it decides what type of damage to do.
};


#endif 