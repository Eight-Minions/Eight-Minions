#ifndef CREEP_H
#define CREEP_H

#include "resources.h"
#include "path.h"

#define NORM 0 //average everything
#define FAST 1 //low armor, low health, high speed, and medium numbers
#define TANK 2 //high armor, medium health, low speed, low numbers
#define SWARM 3 // low armor, low health, average speed, high numbers
#define TITAN 4 //high armor, high health, average speed, very low numbers
#define FATTY 5 //low armor, high health, low speed, medium numbers (could probably come up with a better name)

#define BOARD_X_OFFSET 38
#define BOARD_Y_OFFSET 38

#define CLOCK_CAP .15
//J:
//i think it might be better in the long run to have the client load the creep images just once
//and then pass those to the creeps to display as needed. that could save some memory

class creep : public location
{
private:
	int health;
	int armor;
	int speed;
	int level;
	int type;
	int attack;
	int Xdir;
	int Ydir;
	SDL_Surface *img;
	SDL_Rect *r; //could we include this rect inside the locations class? it would be nice
	coord prevPos;

public:
	Path p;

	creep(int type, int level, int x, int y);
	creep();
	~creep();
	int damage(int damage);
	bool move();
	void displayCreep(SDL_Surface *screen);
	//J: somewhere, the image needs to be set. you tell me where (same for towers)
	//TL: In creep(int type, ... ) (inside of if(type == FAST))
	//J: that works, and also, we are going to need a function somewhere that does spawnWave(type(s)) and spawns the given
	//		type(s) of monsters at timed intervals.

};

#endif