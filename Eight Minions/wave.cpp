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

creep* Wave::iterate()
{
	if(*waveDelay.front() <= 0)
	{
		waveDelay.pop();
		creep *retCreep = waveQueue.front();
		waveQueue.pop();
		return retCreep;
	}
	else
	{
		return NULL;
	}
}