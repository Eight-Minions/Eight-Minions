#ifndef CREEP_H
#define CREEP_H

#include "resources.h"

#define NORM 0 //average everything
#define FAST 1 //low armor, low health, high speed, and medium numbers
#define TANK 2 //high armor, medium health, low speed, low numbers
#define SWARM 3 // low armor, low health, average speed, high numbers
#define TITAN 4 //high armor, high health, average speed, very low numbers


class creep : public location
{
private:
	int health;
	int armor;
	int speed;
	int level;
	int type;
	int attack;
	SDL_Surface *img;
	SDL_Rect *r; //could we include this rect inside the locations class? it would be nice
	// A queue of locations for a path.
	//queue<location> path;
public:
	creep(int type, int level, int x, int y);
	creep();
	~creep();
	int damage(int damage);
	void move();
	void calculatePath();

	void displayCreep(SDL_Surface *screen);
	//J: somewhere, the image needs to be set. you tell me where (same for towers)
	//TL: In creep(int type, ... ) (inside of if(type == FAST))
	//J: that works, and also, we are going to need a function somewhere that does spawnWave(type(s)) and spawns the given
	//		type(s) of monsters at timed intervals.

};

#endif