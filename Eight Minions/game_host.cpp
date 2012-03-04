#include "game_host.h"

int game_host::init()
{
	this->socketType = SOCK_STREAM;
	if(WSAStartup(0x202, &wsaData) != 0)
	{
		//fail
		WSACleanup();
		return -1;
	}
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(this->port);

	sock = socket(AF_INET, socketType, 0);

	if(sock == INVALID_SOCKET)
	{
		//fail

		WSACleanup();
		return -1;
	}
	bind(sock, (struct sockaddr*)&local, sizeof(local));
	listen(sock,MAXWAITINGCONNECTIONS);



	return 0; // temporary
}

int game_host::waitForClients()
{
	//waits for two clients to connect
	p1_len = sizeof(p1_addr);
	p2_len = sizeof(p2_addr);
	cout << "waiting for player 1 to connect...\n";
	player1 = accept(sock, (struct sockaddr*)&p1_addr, &p1_len);
	cout << "player 1 connected! now waiting on player 2...\n";
	player2 = accept(sock, (struct sockaddr*)&p2_addr, &p2_len);
	cout << "player 2 connected! continuing with startup.\n";
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