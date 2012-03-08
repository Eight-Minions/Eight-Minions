#ifndef CLIENT_H
#define CLIENT_H

#include "resources.h"
#include "creep.h"

#define CONNECTION_SUCCESSFUL 1
#define CONNECTION_FAILURE 0 //generic error
#define SERVER_NOT_FOUND -1

class client
{
private:
	string server_addr;
	unsigned int port;
	IPaddress ip;
	TCPsocket sd;
	//MessageQueue mess; -typename not set in stone, its really whatever we want to make it, just for reference

	SDL_Surface* screen;
	SDL_Surface* background;

	queue<string> updateQueue;

	creep testc;

public:
	int init();
	void cleanup();
	void display();
	void processInput();
	int run();
	void setServerAddress(string);
	void setPort(unsigned int);
	int connectToServer();
	int sendToServer(string);
	string recieveMessage();
	void recieveMessageToQueue();
	void parseQueue();

	void savePlayerProfile();
	//this function will take any of the players individual stats, experience, purchased upgrades, and any other
	//relevant data, save it to a file, lock it with the players password, and encrypt it so they cant cheat and modify it.
};

#endif