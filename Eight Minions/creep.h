#ifndef CREEP_H
#define CREEP_H
#include "resources.h"

#define FAST 0
#define TANK 1


class creep : public location
{
private:
	int health;
	int armor;
	int speed;
	int level;
	int type;
<<<<<<< HEAD
	int attack;
	SDL_Surface *img;
	// A queue of locations for a path.
=======
	// A queue of loactions for a path
	queue<location> path;
>>>>>>> origin/master
public:
	creep(int type, int level, int x, int y);
	creep();
	~creep();
	int damage(int damage);
	void move();
	void calculatePath();

	//J: somewhere, the image needs to be set. you tell me where (same for towers)
};

#endif