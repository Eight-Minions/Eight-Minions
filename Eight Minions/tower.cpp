#include "tower.h"

tower::tower()
{
}
tower::tower(int l, int t, int set_x, int set_y)
{
	level = l;
	type = t;
	this->setX(set_x);
	this->setY(set_y);
	img = IMG_Load("tower.png");
	r = new SDL_Rect;
}
int tower::getLevel()
{
	return this->level;
}
int tower::getType()
{
	return this->type;
}
int tower::setType(int newType)
{
	type = newType;
	return type;
}
tower::~tower()
{
}
void tower::damageNeighbors(int radius)
{
	// TL:
	// Check the linkedlist for neightbors based upon its position
	// Insert them in a new linked list
	// Damage those neighbors
}
void damageClosestCreepTo(int radius, location *position)
{
	// creep closest = NULL;
	// Check the linkedlist for the closest creep within some radius
	// closest.damage(this->attack * this->speed);
	// this->attack * this->speed because having some wait could be odd?
}
void tower::damageClosestCreep(int radius)
{
	 damageClosestCreepTo(radius, new location(this->getX(), this->getY()));
}

void tower::displayTower(SDL_Surface *screen)
{
	this->r->x = (GRID_SIZE * this->getX()) + BOARD_X_OFFSET;
	this->r->y = (GRID_SIZE * this->getY()) + BOARD_Y_OFFSET;
	SDL_BlitSurface(this->img, NULL, screen, r);
}