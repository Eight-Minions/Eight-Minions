#include "aoeAnim.h"


AoeAnimation::AoeAnimation( int towerX, int towerY, int speed )
{

	x = towerX - GRID_SIZE;
	y = towerY - GRID_SIZE;
	type = AREAOFEFFECT;
	TickTimer = 5;
	animIndex = 0;
	animMax = 5;
	sprite_r = newRect(0,72 * type,72,72);
	place_r = newRect(x,y,72,72);
}

bool AoeAnimation::update( int targetX, int targetY )
{
	TickTimer--;

	if(TickTimer <= 0)
		return true;
	else
		return false;
}
