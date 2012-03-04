#include "game_host.h"

int game_host::init()
{


	return 0; // temporary
}

int game_host::waitForClients()
{

	return 1;
}

int game_host::run()
{
	this->init();

	//runs the game itself
	return 0;
}
void game_host::setPort(unsigned int setPort)
{
	//Last Changed: 3-2-12 @ 5:21
	//changelog:
	//made function set port
	//todo:
	//error checking, ensure input is valid
	this->port = setPort;
}
int game_host::sendUpdate()
{
	//send updates about the game to each player
	return 0;
}