#ifndef ATTACK_ANIM_H
#define ATTACK_ANIM_H
#include "resources.h"

#define ANIM_SIZE 12

class attackAnim
{
protected:
	int x, y;
	int TickTimer;
	int type;
	int animIndex;
	int animMax;
	int targetIndex;
	int animSize;

	SDL_Rect *place_r;
	SDL_Rect *sprite_r;

public:
	~attackAnim();

	virtual bool update(int targetX, int targetY)=0;

	void animUpdate();

	void display(SDL_Surface *screen, SDL_Surface *sprites);

	int getTarget();

};
#endif