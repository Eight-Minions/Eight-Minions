#ifndef GAME_HOST_H
#define GAME_HOST_H

#include "resources.h"


class game_host
{
private:
	unsigned int port;
	IPaddress ip, player1ip, player2ip;
	TCPsocket sd;
	TCPsocket player1sd, player2sd;
	SDLNet_SocketSet socketset;
	UDPsocket p1UDPsock, p2UDPsock;
	UDPpacket *UDPpack1, *UDPpack2;


public:
	int init();
	int waitForClients();
	int run(); //runs the game itself
	void setPort(unsigned int);
	int sendUpdate(); //called by run() to send information to each player about changes in what they need to display
	int sendUpdate(char mess[15]);
	int sendUpdate(int ToC, int id, int attr, int newVal);
	int sendToClients(string);
	string recieveMessagep1();
	string recieveMessagep2();
	void recieveMessageToQueue();
	void parseQueue();
};

#endif