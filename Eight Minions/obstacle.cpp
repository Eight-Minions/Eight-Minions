#include "obstacle.h"

Obstacle::Obstacle() : structure ()
{
	this->setPassable(false);
}
Obstacle::Obstacle(int type, int new_x, int new_y) : structure (0, 0, type, new_x, new_y)
{
	this->setPassable(false);
}
Obstacle::~Obstacle()
{	
}