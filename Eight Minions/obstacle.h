#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "resources.h"
#include "tower.h"

class Obstacle : public structure
{
public:
	Obstacle();
	Obstacle(int type, int x, int y);
	~Obstacle();
private:

};
#endif