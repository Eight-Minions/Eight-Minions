#ifndef GAME_HOST_H
#define GAME_HOST_H

#include "resources.h"
#define REQSOCKVER 2
#define MAXWAITINGCONNECTIONS 3
class game_host
{
private:
	unsigned int port;
	int something;
	SOCKET sock;
	WSADATA wsaData;
	int socketType;
	struct sockaddr_in local;
	//also need objects for two socket connections, possibly four, i/o for each player

public:
	int init();
	int waitForClients();
	int run(); //runs the game itself
	void setPort(unsigned int);
	int sendUpdate(); //called by run() to send information to each player about changes in what they need to display
	int sendToClient(string);
};

#endif