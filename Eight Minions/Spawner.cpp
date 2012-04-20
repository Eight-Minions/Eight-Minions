#include "Spawner.h"

Spawner::Spawner()
{
	//Spawner should never be called like this, just sayin
}


//spawner constructor
//
//params: 
//	nManager - a pointer to THE game_host object that is running the game
//	nPlayer - the player who will own the creeps that are spawned
//	isTower - whether or not this spawner will be part of a creep tower
Spawner::Spawner(game_host *nManager, int Player, bool Tower, coord nLoc)
{
	manager = nManager;
	nPlayer = Player;
	SpawnerCount = 0;
	creepType = NORM;
	spawnerLevel = 1;
	Loc = nLoc;
	delay = CREEPTOWERDELAY;
	waveNumber = 0;
	isTower = Tower;
	if(!isTower)
	{
		generateWave();
		curDelay = 200;
	}

}
Spawner::Spawner( game_host* nManager, int Player, bool Tower, int nCreepType, int nLevel, coord nLoc)
{
	Loc = nLoc;
	manager = nManager;
	nPlayer = Player;
	SpawnerCount = 0;
	creepType = nCreepType;
	spawnerLevel = nLevel;
	delay = CREEPTOWERDELAY;
	waveNumber = 0;
	isTower = Tower;
	if(!isTower)
	{
		generateWave();
		curDelay = 200;
	}
	
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
			creep *retCreep = new creep(creepType,nPlayer,spawnerLevel,Loc.x,Loc.y);
			if(retCreep->getPrice() <= manager->getPlayer(nPlayer)->getMoney())
			{
				retCreep->p.setGoal(manager->Bases[nPlayer % 2]);
				retCreep->p.genPath(manager->Nodemap, false);
				manager->getPlayer(nPlayer)->spendMoney(retCreep->getPrice());
				creepIndex = manager->creepList.insertInOrder(retCreep);
				manager->sendMessageToQueue(UpdMess(nPlayer, PLAYERUPDATE, manager->getPlayer(nPlayer)->getHealth(), manager->getPlayer(nPlayer)->getMoney()).getMT());
				manager->sendMessageToQueue(UpdMess(nPlayer,NEWCREEP,creepIndex,retCreep->getX(),retCreep->getY(),retCreep->getHealth(),retCreep->getType(),retCreep->getLevel()).getMT());

				//CHANGES NEEDED HERE
				curDelay = delay;

				//also, add handlers for if the player wants to save up a swarm.
				return true;
			}
			else
			{
				//cout << "Not enough money for creep" << endl;
				return false;
			}
		}
		return false;
	}
	else
	{
		if(curDelay <= 0)
		{
			int creepIndex;
			creep *retCreep = SpawnerQueue.front();
			SpawnerQueue.pop();
			retCreep->p.genPath(manager->Nodemap, false);
			creepIndex = manager->creepList.insertInOrder(retCreep);
			manager->sendMessageToQueue(UpdMess(nPlayer,NEWCREEP,creepIndex,retCreep->getX(),retCreep->getY(),retCreep->getHealth(),retCreep->getType(),retCreep->getLevel()).getMT());
			if(SpawnerQueue.empty())
			{
				//generate next Spawner, or trigger end-game, or whatever.
				generateWave();
			}
			curDelay = SpawnerDelay.front();

			SpawnerDelay.pop();
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
	waveNumber++;
	spawnableCreeps.push(creepType);
	creepType = spawnableCreeps.front();
	spawnableCreeps.pop();
	creep *tempCreep = NULL;

	while(!SpawnerDelay.empty())
		SpawnerDelay.pop();
	int spawnNum = creepBaseSpawnNum[creepType];
	//creep number selection.
	spawnNum /= 2;
	if(waveNumber > 10)
	{
		spawnNum += (waveNumber - 5) / 5;
	}
	for(int i = 0; i < spawnNum; i++) 
	{
		switch(creepType)
		{
		case NORM:
			tempCreep = new creep(creepType,this->nPlayer,spawnerLevel,Loc.x,Loc.y);
			tempCreep->p.setGoal(manager->Bases[nPlayer % 2]);
			SpawnerQueue.push(tempCreep);
			if(i < spawnNum - 1)
				SpawnerDelay.push(normCreepArr[this->getLevel() - 1][5] * MAX_FPS);
			break;

		case FAST:
			tempCreep = new creep(creepType,this->nPlayer,spawnerLevel,Loc.x,Loc.y);
			tempCreep->p.setGoal(manager->Bases[nPlayer % 2]);
			SpawnerQueue.push(tempCreep);
			if(i < spawnNum - 1)
				SpawnerDelay.push(fastCreepArr[this->getLevel() - 1][5] * MAX_FPS);
			break;

		case SWARM:
			tempCreep = new creep(creepType,this->nPlayer,spawnerLevel,Loc.x,Loc.y);
			tempCreep->p.setGoal(manager->Bases[nPlayer % 2]);
			SpawnerQueue.push(tempCreep);
			SpawnerDelay.push(5);
			tempCreep = new creep(creepType,this->nPlayer,1,Loc.x,Loc.y);
			tempCreep->p.setGoal(manager->Bases[nPlayer % 2]);
			SpawnerQueue.push(tempCreep);
			if(i < spawnNum - 1)
				SpawnerDelay.push(swarmCreepArr[this->getLevel() - 1][5] * MAX_FPS);
			break;

		case TANK:
			tempCreep = new creep(creepType,this->nPlayer,spawnerLevel,Loc.x,Loc.y);
			tempCreep->p.setGoal(manager->Bases[nPlayer % 2]);
			SpawnerQueue.push(tempCreep);
			if(i < spawnNum - 1)
				SpawnerDelay.push(tankCreepArr[this->getLevel() - 1][5] * MAX_FPS);
			break;

		case FATTY:
			tempCreep = new creep(creepType,this->nPlayer,spawnerLevel,Loc.x,Loc.y);
			tempCreep->p.setGoal(manager->Bases[nPlayer % 2]);
			SpawnerQueue.push(tempCreep);
			if(i < spawnNum - 1)
				SpawnerDelay.push(fattyCreepArr[this->getLevel() - 1][5] * MAX_FPS);
			break;

		case TITAN:
			tempCreep = new creep(creepType,this->nPlayer,spawnerLevel,Loc.x,Loc.y);
			tempCreep->p.setGoal(manager->Bases[nPlayer % 2]);
			SpawnerQueue.push(tempCreep);
			if(i < spawnNum - 1)
				SpawnerDelay.push(titanCreepArr[this->getLevel() - 1][5] * MAX_FPS);
			break;

		}
		if(i == spawnNum - 1)
			SpawnerDelay.push(25 * MAX_FPS);

	}
}

int Spawner::getLevel()
{
	return spawnerLevel;
}

int Spawner::getType()
{
	return creepType;
}

void Spawner::setDelay(int newDelay)
{
	delay = newDelay;
}

//add creep type
//author: Jeromy Johnson
//
//add the specified creep type to the queue of creeps to generate waves for
void Spawner::addCreepType(int nCreepType)
{
	spawnableCreeps.push(nCreepType);
}