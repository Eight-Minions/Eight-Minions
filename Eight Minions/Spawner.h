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
	queue<int*> SpawnerDelay;
	int SpawnerCount;

public:
	Spawner();
	Spawner(game_host* nManager, int nPlayer); //manager is the object that this Spawner class will manage spawning creeps for
	
	void testing();

	void generateSpawner();

	void iterate();

	void addCreepsToCurrent(int num);

	void setDifficulty();
	void setDifIncrease(int n);

};





#endif