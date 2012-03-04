#ifndef CREEP_H
#define CREEP_H
#include "resources.h"

class creep : public location
{
private:
	int health;
	int speed;
	int level;
	int type;
	int attack;
	
public:
	creep(int type, int level, int x, int y);
	~creep();


};

#endif