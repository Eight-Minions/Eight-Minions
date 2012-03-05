#ifndef CLIENT_H
#define CLIENT_H

#include "resources.h"

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
};

#endif