#ifndef GAME_HOST_H
#define GAME_HOST_H

#include "resources.h"
#include "creep.h"
#include "tower.h"
#include "Spawner.h"
#include "standard_tower.h"
#include "creep_tower.h"
#include "obstacle.h"
#include "mine.h"
#include "player.h"
#include "FPS_Regulator.h"

#define MAX_MESSAGE_LENGTH 300

class game_host
{
private:
	//Networking Variables
	unsigned int port;
	IPaddress ip, *player1ip, *player2ip;
	TCPsocket sd;
	TCPsocket player1sd, player2sd;
	SDLNet_SocketSet socketset;
	UDPsocket p1UDPsock, p2UDPsock;
	UDPpacket *UDPpack1, *UDPpack2, *UDPrpack;
	string updateCollection;

protected:
	//Map variables
	vector<vector<structure*>> Tmap; //map of pointers to the towers, NULL if no tower
	vector<vector<bool>> Nodemap; //boolean map, false means passable

	cList<creep*> creepList; //the list of creeps, creeps contain their positions
	cList<structure*> towerList;

	creep *pathTestCreep;

	Spawner	*p1Spawner, *p2Spawner; //spawner objects for each player

	player players[2];

	//coordinate locations for each players base
	coord Bases[2]; //more modular

public:
	int init();
	int init_net();
	void setPort(unsigned int);
	int waitForClients();
	int waitForClient_test();

	int run(); //runs the game itself - use test run until we finish the engine
	int testrun();

	void setNodemap();
	void updatePaths(int newX, int newY);
	void spawnCreep(int playerNumber, int creepType, int creepLevel, coord spawnCoord);
	void spawnCreep(creep *newCreep);
	int placeTower(int playerNumber, int towerType, int x, int y);
	bool placeTowerForced(int playerNumber, int towerType, int x, int y, int towerID);
	bool removeTower(int towerID, int playerNum);
	bool removeTowerLocal(int towerID);
	bool changeStructure(int structureID, int newType);

	int sendToClients(string);
	int sendToClientsUDP(string mess);

	string recieveMessagep1();
	string recieveMessagep2();
	string recieveMessageUDP();

	bool recieveFromClients();
	int performUpdate(string upd);

	void sendMessageToQueue(string mess);
	void parseQueue();

	int sendtop1UDP(string mess);
	int sendtoP1_test(string buff);

	cList<creep*> * getCreepList();
	cList<structure*> * getTowerList();
	player * getPlayer(int playerNumber);
	bool isEmptyLocation(int xLoc, int yLoc);

	friend Spawner;

	/*
	friend Spawner;
	friend tower;
	friend Standard_Tower;
	*/
};

#endif