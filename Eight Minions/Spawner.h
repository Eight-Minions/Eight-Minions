#ifndef Spawner_H
#define Spawner_H
#include "game_host.h"

class game_host;

class Spawner
{
private:
	game_host *manager;
	int player; //which player it spawns for
	queue<creep*> SpawnerQueue;
	queue<int> SpawnerDelay;
	int SpawnerCount;
	int creepType;
	int curDelay;
	int spawnerLevel;

	coord Loc;

	bool stream; //true- send out constant stream of creeps. false- store up creeps (only for spawn)
	bool isTower; //true- this spawner is part of a tower, false- this spawner is the players main spawner


public:
	Spawner();
	Spawner(game_host* nManager, int nPlayer); //manager is the object that this Spawner class will manage spawning creeps for
	
	void testing();

	//GenerateSpawner
	//this function will create a certain number of creeps and add them to a queue
	void generateSpawner();

	//this function is called once per game loop, if the current delay is zero it spawns the first creep on the queue
	//otherwise it decrements the current delay
	bool iterate();

	//add 'num' number of creeps (we should change this to specify type and level etc) to the queue
	void addCreepsToCurrent(int num);

	void setDifficulty();
	void setDifIncrease(int n);

};





#endif