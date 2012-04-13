#include "tower.h"

tower::tower()
{
}
tower::tower(int l, int p, int t, int set_x, int set_y)
{
	player = p;
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
void tower::displayTower(SDL_Surface *screen)
{
	if(img != NULL)
	{
		this->r->x = (GRID_SIZE * this->getX()) + BOARD_X_OFFSET;
		this->r->y = (GRID_SIZE * this->getY()) + BOARD_Y_OFFSET;
		SDL_BlitSurface(this->img, NULL, screen, r);
	}
}
int tower::getPlayer()
{
	return player;
}

int tower::setLevel(int newLevel)
{
	level = newLevel;
	return level;
}

bool tower::getPassable()
{
	return passable;
}

void tower::setPassable( bool nPass )
{
	passable = nPass;
}

