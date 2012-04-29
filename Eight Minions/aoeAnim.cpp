#include "aoeAnim.h"


AoeAnimation::AoeAnimation( int towerX, int towerY, int speed )
{

	x = towerX - GRID_SIZE;
	y = towerY - GRID_SIZE;
	type = AREAOFEFFECT;
	TickTimer = 5;
	animIndex = 0;
	animMax = 5;
	animSize = 72;
	sprite_r = newRect(0,0,animSize,animSize);
	place_r = newRect(x,y,animSize,animSize);
}

bool AoeAnimation::update( int targetX, int targetY )
{
	TickTimer--;

	if(TickTimer <= 0)
		return true;
	else
		return false;
}
