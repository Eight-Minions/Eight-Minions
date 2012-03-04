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
	SOCKET player1;
	SOCKET player2;
	WSADATA wsaData;
	int socketType;
	struct sockaddr_in local;
	struct sockaddr_in p1_addr;
	struct sockaddr_in p2_addr;
	int p1_len;
	int p2_len;
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