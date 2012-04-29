#include "attackAnim.h"







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
	sprite_r->x = animSize * animIndex;
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

int attackAnim::getType()
{
	return type;
}
