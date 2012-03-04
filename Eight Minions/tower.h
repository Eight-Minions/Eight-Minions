#ifndef TOWER_H
#define TOWER_H

#include "resources.h"

class tower : public location
{	
private:
	int health;
	int level;
	int type;
	int attackSpeed;
	int attackType;
public:
	tower(int health, int level, int type, int x , int y);
	~tower();
	int getHealth();
	void setHealth(int);

	int getLevel();
	void setLevel(int);

	int getType();
	void setType(int);
};


#endif 