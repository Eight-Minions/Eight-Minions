#ifndef PROJANIM_H
#define PROJANIM_H

#include "attackAnim.h"

class projectileAnimation: public attackAnim
{
public:
	projectileAnimation::projectileAnimation( int startX, int startY, int nType, int nTick, int nTargetIndex );

	bool projectileAnimation::update( int targetX, int targetY );

};
#endif