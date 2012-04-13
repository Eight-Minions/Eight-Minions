#include "attackAnim.h"

attackAnim::attackAnim( int startX, int startY, int nType, int nTick, int nTargetIndex )
{
	x = startX;
	y = startY;
	type = nType;
	TickTimer = nTick;
	animIndex = 0;
	animMax = 5;
	targetIndex = nTargetIndex;
	sprite_r = newRect(0,8 * type,8,8);
	place_r = newRect(x,y,8,8);
}

bool attackAnim::update( int targetX, int targetY )
{
	x += (targetX - x) / TickTimer;
	y += (targetY - y) / TickTimer;

	TickTimer--;

	if(TickTimer <= 0)
		return true;
	else
		return false;
}

void attackAnim::display( SDL_Surface *screen, SDL_Surface *sprites )
{
	animUpdate();
	this->place_r->x = x;
	this->place_r->y = y;

	SDL_BlitSurface(sprites, sprite_r, screen, place_r);
}

void attackAnim::animUpdate()
{
	animIndex++;
	if (animIndex == animMax)
	{
		animIndex = 0;
	}
	sprite_r->x = 8 * animIndex;
}

int attackAnim::getTarget()
{
	return targetIndex;
}

attackAnim::~attackAnim()
{
	delete place_r;
	delete sprite_r;
}