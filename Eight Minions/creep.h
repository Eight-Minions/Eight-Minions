#ifndef CREEP_H
#define CREEP_H
#include "resources.h"

#define FAST 0
#define TANK 1


class creep : public location
{
private:
	int health;
	int speed;
	int level;
	int type;
	// A queue of locations for a path.
public:
	creep(int type, int level, int x, int y);
	creep();
	~creep();
	int damage(int damage);
	void move();
	void calculatePath();
};

#endif