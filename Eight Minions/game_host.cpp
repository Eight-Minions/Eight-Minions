#include "game_host.h"

int game_host::init()
{
	
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (SDLNet_ResolveHost(&ip, NULL, this->port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	return 0; // temporary
}

int game_host::waitForClients()
{
	cout << "waiting for first player to connect...\n";
	while(!(player1sd = SDLNet_TCP_Accept(sd)));
	cout << "waiting for second player to connect...\n";
	while(!(player2sd = SDLNet_TCP_Accept(sd)));

	cout << "both clients connected, continuing...\n";
	return 1;
}

int game_host::run()
{
	this->init();
	this->waitForClients();
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