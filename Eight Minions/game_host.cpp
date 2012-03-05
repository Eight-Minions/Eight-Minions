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
	this->sendToClients("testing!!!");
	system("pause");
	//runs the game itself
	return 0;
}
void game_host::setPort(unsigned int setPort)
{
	//Last Changed: 3-5-12 @ 10:53
	//changelog:
	//made function set port
	//validated the input
	//todo:
	//
	if(setPort > 65535)
	{
		cout << "INVALID PORT!\n";
		system("pause");
		exit(1);
	}
	this->port = setPort;
}


int game_host::sendUpdate()
{
	//send updates about the game to each player
	return 0;
}

int game_host::sendToClients(string buff)
{
	if(!this->player1sd || !this->player2sd)
	{
		cout << "No Connection!\n";
		return -1;
	}
	else
	{
		if(SDLNet_TCP_Send(player1sd, (void *)buff.c_str(), buff.length()+1) < buff.length() + 1)
		{
			cout << "Message to client 1 failed to send...\n";
			return -1;
		}
		if(SDLNet_TCP_Send(player2sd, (void *)buff.c_str(), buff.length()+1) < buff.length() + 1)
		{
			cout << "Message to client 2 failed to send...\n";
			return -1;
		}
	}
	return 1;
}

string game_host::recieveMessagep1()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->player1sd, buff, 512));
	//cout << buff << "\n";
	string ret = buff;
	return ret;
}

string game_host::recieveMessagep2()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->player2sd, buff, 512));
	//cout << buff << "\n";
	string ret = buff;
	return ret;
}

void game_host::recieveMessageToQueue()
{
	//pseudocode:
	//recieve string from p1
	//push to queue
	//recieve string from p2
	//push to queue
	//return
}