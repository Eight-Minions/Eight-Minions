#ifndef GAME_HOST_H
#define GAME_HOST_H

#include "resources.h"

#define REQSOCKVER 2
#define MAXWAITINGCONNECTIONS 3
class game_host
{
private:
	unsigned int port;
	IPaddress ip;
	TCPsocket sd;
	TCPsocket player1sd, player2sd;
	UDPsocket usd;
	UDPpacket *pack;


public:
	int init();
	int waitForClients();
	int run(); //runs the game itself
	void setPort(unsigned int);
	int sendUpdate(); //called by run() to send information to each player about changes in what they need to display
	int sendToClients(string);
	string recieveMessagep1();
	string recieveMessagep2();
	void recieveMessageToQueue();
	void parseQueue();
};

#endif