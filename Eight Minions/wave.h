#ifndef WAVE_H
#define WAVE_H
#include "game_host.h"

class game_host;

class Wave
{
private:
	game_host *manager;
	int player;
	queue<creep*> waveQueue;
	queue<int*> waveDelay;
	int waveCount;

public:
	Wave();
	Wave(game_host* nManager, int nPlayer); //manager is the object that this wave class will manage spawning creeps for
	
	void testing();

	void generateWave();

	void iterate();

	void addCreepsToCurrent(int num);

	void setDifficulty();
	void setDifIncrease(int n);

};





#endif