#include "projectileAnim.h"

projectileAnimation::projectileAnimation( int startX, int startY, int nType, int nTick, int nTargetIndex )
{
	x = startX + (GRID_SIZE / 2);
	y = startY + (GRID_SIZE / 2);
	type = ATTACKONECREEP;
	TickTimer = nTick;
	animIndex = 0;
	animMax = 4;
	targetIndex = nTargetIndex;
	animSize = 12;
	sprite_r = newRect(0,0,animSize,animSize);
	place_r = newRect(x,y,animSize,animSize);
}

bool projectileAnimation::update( int targetX, int targetY )
{
	x += (targetX - x) / TickTimer;
	y += (targetY - y) / TickTimer;

	TickTimer--;

	if(TickTimer <= 0)
		return true;
	else
		return false;
}