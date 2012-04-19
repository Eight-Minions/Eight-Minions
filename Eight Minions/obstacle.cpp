#include "obstacle.h"

Obstacle::Obstacle() : structure ()
{
}
Obstacle::Obstacle(int type, int new_x, int new_y) : structure (0, 0, type, new_x, new_y)
{
}
Obstacle::~Obstacle()
{
}