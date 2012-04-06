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
		int creepIndex;
		waveDelay.pop();
		creep *retCreep = waveQueue.front();
		waveQueue.pop();
		creepIndex = manager->creepList.insertInOrder(retCreep);
		manager->sendMessageToQueue(UpdMess(player,NEWCREEP,creepIndex,retCreep->getX(),retCreep->getY(),retCreep->getHealth(),retCreep->getType(),retCreep->getLevel()).getMT());
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