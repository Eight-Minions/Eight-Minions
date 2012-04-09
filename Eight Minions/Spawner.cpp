#include "Spawner.h"

Spawner::Spawner()
{
	//Spawner should never be called like this, just sayin
}

Spawner::Spawner( game_host* nManager, int nPlayer )
{
	this->manager = nManager;
	this->player = nPlayer;
	SpawnerCount = 0;
}


void Spawner::testing()
{

}

bool Spawner::iterate()
{
	if(*SpawnerDelay.front() <= 0)
	{
		int creepIndex;
		SpawnerDelay.pop();
		creep *retCreep = SpawnerQueue.front();
		SpawnerQueue.pop();
		creepIndex = manager->creepList.insertInOrder(retCreep);
		manager->sendMessageToQueue(UpdMess(player,NEWCREEP,creepIndex,retCreep->getX(),retCreep->getY(),retCreep->getHealth(),retCreep->getType(),retCreep->getLevel()).getMT());
		if(SpawnerQueue.empty())
		{
			//generate next Spawner, or trigger end-game, or whatever.
		}
		return true;
	}
	else
	{
		*SpawnerDelay.front()--;
		return false;
	}
}

void Spawner::generateSpawner()
{
	//decide creep type and number
	//spawn that amount of creeps of chosen type and put them into the queue
	//decide on a good delay between creeps
	
	
}
