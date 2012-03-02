#ifndef GAME_HOST_H
#define GAME_HOST_H

#include <iostream>
#include "networking.h"

class game_host
{
private:
	unsigned int port;
	
	//also need objects for two socket connections, possibly four, i/o for each player

public:
	int run();
	void setPort(unsigned int);
	int sendUpdate();
};

#endif