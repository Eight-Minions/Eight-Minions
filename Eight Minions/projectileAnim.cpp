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
	sprite_r = newRect(0,ANIM_SIZE * type,ANIM_SIZE,ANIM_SIZE);
	place_r = newRect(x,y,ANIM_SIZE,ANIM_SIZE);
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