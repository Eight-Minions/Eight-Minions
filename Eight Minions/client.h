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
	SOCKET sock;
	WSADATA wsaData;
	struct sockaddr_in server;
	struct hostent *hp;
	int socketType;
	unsigned int addr;

public:
	int init();
	void display();
	void processInput();
	int run();
	void setServerAddress(string);
	void setPort(unsigned int);
	int connect();
	int sendToServer(string);

};

#endif