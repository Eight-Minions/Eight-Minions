#include "wave.h"

Wave::Wave()
{
	//wave should never be called like this, just sayin
}

Wave::Wave( game_host* nManager, int nPlayer )
{
	this->manager = nManager;
	this->player = nPlayer;
	waveCount = 0;
}


void Wave::testing()
{

}

void Wave::iterate()
{
	if(*waveDelay.front() <= 0)
	{
		waveDelay.pop();
		creep *retCreep = waveQueue.front();
		waveQueue.pop();
		manager->creepList.insertInOrder(retCreep);
		if(waveQueue.empty())
		{
			//generate next wave, or trigger end-game, or whatever.
		}
	}
	else
	{
		*waveDelay.front()--;
	}
}