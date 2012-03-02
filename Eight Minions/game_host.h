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
	int run(); //runs the game itself
	void setPort(unsigned int);
	int sendUpdate(); //called by run() to send information to each player about changes in what they need to display
};

#endif