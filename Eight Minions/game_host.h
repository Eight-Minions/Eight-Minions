#ifndef GAME_HOST_H
#define GAME_HOST_H

#include "resources.h"
#include "creep.h"
#include "tower.h"

#define MAX_MESSAGE_LENGTH 200

class game_host
{
private:
	unsigned int port;
	IPaddress ip, *player1ip, *player2ip;
	TCPsocket sd;
	TCPsocket player1sd, player2sd;
	SDLNet_SocketSet socketset;
	UDPsocket p1UDPsock, p2UDPsock;
	UDPpacket *UDPpack1, *UDPpack2;
	string updateCollection;

	vector<vector<tower*>> Tmap;
	vector<vector<bool>> Nodemap;

	cList<creep*> creepList1;
	int p1numCreeps;
	cList<creep*> creepList2;
	int p2numCreeps;

	coord p1Base;
	coord p2Base;

public:
	int init();
	int init_net();
	void setPort(unsigned int);
	int waitForClients();
	int waitForClient_test();

	int run(); //runs the game itself
	int testrun();

	void setNodemap();
	void updatePaths();
	void spawnCreep(int playerNumber, int creepType, int creepLevel, coord spawnCoord);
	int placeTower(int playerNumber, int towerType, coord c);

	int sendToClients(string);
	int sendToClientsUDP(string mess);

	string recieveMessagep1();
	string recieveMessagep2();

	void sendMessageToQueue(string mess);
	void parseQueue();

	int sendtop1UDP(string mess);
	int sendtoP1_test(string buff);
};

#endif