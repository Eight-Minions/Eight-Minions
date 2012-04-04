#include "wave.h"

Wave::Wave()
{
	//wave should never be called like this
}

Wave::Wave( game_host* nManager, int nPlayer )
{
	this->manager = nManager;
	this->player = nPlayer;
}


void Wave::testing()
{
	coord n = {0,0};
	manager->spawnCreep(player,2,2,n);
}
