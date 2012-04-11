#include "Spawner.h"

Spawner::Spawner()
{
	//Spawner should never be called like this, just sayin
}

Spawner::Spawner( game_host* nManager, int nPlayer, bool isTower)
{
	this->manager = nManager;
	this->player = nPlayer;
	SpawnerCount = 0;
	creepType = NORM;
}


void Spawner::testing()
{

}

bool Spawner::iterate()
{
	if(isTower)
	{
		curDelay--;
		if(curDelay <= 0)
		{
			int creepIndex;
			creep *retCreep = new creep(creepType,player,spawnerLevel,Loc.x,Loc.y);
			creepIndex = manager->creepList.insertInOrder(retCreep);
			manager->sendMessageToQueue(UpdMess(player,NEWCREEP,creepIndex,retCreep->getX(),retCreep->getY(),retCreep->getHealth(),retCreep->getType(),retCreep->getLevel()).getMT());
			
			//CHANGES NEEDED HERE
			curDelay = 10;

			//also, add handlers for if the player wants to save up a swarm.
		}
	}
	else
	{
		if(curDelay <= 0)
		{
			int creepIndex;
			SpawnerDelay.pop();
			curDelay = SpawnerDelay.front();
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
			curDelay--;
			return false;
		}
	}
}

void Spawner::generateSpawner()
{
	//decide creep type and number
	//spawn that amount of creeps of chosen type and put them into the queue
	//decide on a good delay between creeps


}
