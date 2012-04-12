#include "Spawner.h"

Spawner::Spawner()
{
	//Spawner should never be called like this, just sayin
}

Spawner::Spawner(game_host* nManager, int nPlayer, bool isT)
{
	this->manager = nManager;
	this->player = nPlayer;
	this->isTower = isT;
	SpawnerCount = 0;
	creepType = NORM;
}

void Spawner::testing()
{
	//not doing anything here at the moment, had been used for testing
	//keeping this around just in case testing is needed
}

//iterate
//author:Jeromy Johnson
//
//
/// this function is called once per game loop
/// it has two operation paths; 1- if its in a tower, 2- if its in a players base
/// behavior for towers is as follows:
///		>decrement current delay
///		>if current delay is now zero, spawn a creep, and reset delay
///
/// behavior for bases is as follows:
///		>if the current delay is zero, spawn the top creep on the queue
///		>pop the top creep
///		>set the next delay from the  queue
///		>pop the top delay
///		>if the queues are empty, run generateWave to refill them
///		>if the delay wasnt zero, decrement it
/// 
/// 
/// Returns:
///		true when a creep was spawned
///		false when a creep was NOT spawned
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
			return true;
		}
		return false;
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
				generateWave();
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


//generateWave
//author:Jeromy Johnson
//
//this function will generate a 'Wave' of creeps to be spawned and the delays between each spawning
void Spawner::generateWave()
{
	//decide creep type and number
	//spawn that amount of creeps of chosen type and put them into the queue
	//decide on a good delay between creeps


}
