#ifndef ATTACK_ANIM_H
#define ATTACK_ANIM_H
#include "resources.h"

class attackAnim
{
private:
	int x, y;
	int TickTimer;
	int type;
	int animIndex;
	int animMax;
	int targetIndex;

	SDL_Rect *place_r;
	SDL_Rect *sprite_r;

public:
	attackAnim(int x, int y, int type, int nTick, int nTargetIndex);
	~attackAnim();

	bool update(int targetX, int targetY);

	void animUpdate();

	void display(SDL_Surface *screen, SDL_Surface *sprites);

	int getTarget();

};
#endif