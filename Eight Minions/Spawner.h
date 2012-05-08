#ifndef Spawner_H
#define Spawner_H
#include "game_host.h"

class game_host;

class Spawner
{
private:
	client *manager; //a pointer to THE game_host
	int nPlayer; //index of the player to spawn creeps for
	queue<creep*> SpawnerQueue; //the queue of creeps to spawn, only for generating waves of creeps for the base (not for creep towers)
	queue<int> SpawnerDelay; //the queue of delays between spawns, also only for spawning from base (not for creep towers)
	queue<int> spawnableCreeps;
	
	int SpawnerCount; //not sure what im using this for actually

	int creepType; //the type of creep the spawner will create
	int spawnerLevel; //the level of the spawner/level of creep to be spawned
	
	int waveNumber;

	int curDelay; //the current delay until the next creep is spawned
	int delay;

	coord Loc; 
	//the location of the spawner
	//for bases, this will be set to the base coordinates
	//for creep towers, this will be its placement on the grid
	//creeps that are spawned will be placed at this point


	bool stream; //true- send out constant stream of creeps. false- store up creeps (only for spawn)
	bool isTower; //true- this spawner is part of a tower, false- this spawner is the players main spawner

public:
	Spawner();
	Spawner(game_host *nManager, int nPlayer, bool isTower, coord nLoc);
	Spawner(game_host* nManager, int nPlayer, bool isTower, int nCreepType, int nLevel, coord nLoc); //manager is the object that this Spawner class will manage spawning creeps for
	
	void testing();

	//GenerateSpawner
	//this function will create a certain number of creeps and add them to a queue
	void generateWave();

	//this function is called once per game loop, if the current delay is zero it spawns the first creep on the queue
	//otherwise it decrements the current delay
	bool iterate();

	//add 'num' number of creeps (we should change this to specify type and level etc) to the queue
	void addCreepsToCurrent(int num);

	void setCreepType(int nCreepType);
	void addCreepType(int nCreepType);
	void setStream(bool toStream); //set whether or not creeps should be released, can only be false for swarms

	void setDifficulty();
	void setDifIncrease(int n);

	void setDelay(int newDelay);

	int getLevel();
	void setLevel(int newLevel);
	int getType();

	bool isInSpawner(int checkType);
	
};





#endif