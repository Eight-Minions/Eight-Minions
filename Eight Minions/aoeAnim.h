#ifndef AOEANIM_H
#define AOEANIM_H

#include "attackAnim.h"

class AoeAnimation: public attackAnim
{
public:
	AoeAnimation(int towerX, int towerY, int speed);

	bool AoeAnimation::update( int targetX, int targetY );
};
#endif