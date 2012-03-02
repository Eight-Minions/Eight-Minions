#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "networking.h"

class client
{
private:
	string server_addr;
	unsigned int port;

public:
	void display();
	void processInput();
	int run();
	void setServerAddress(string);
	void setPort(unsigned int);

};
