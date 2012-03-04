#include "client.h"


int client::init()
{



 return 0;
}
void client::display()
{

}
void client::processInput()
{
	
}
int client::run()
{
	this->init();
	//main run loop
	return 0;
}
void client::setServerAddress(string address)
{
	//Last Changed: 3-2-12 @ 5:15
	//changelog:
	//made function set address
	//todo:
	//error checking, ensure input is valid

	this->server_addr = address;
}
void client::setPort(unsigned int setPort)
{
	//Last Changed: 3-2-12 @ 5:16
	//changelog:
	//made function set port
	//todo:
	//error checking, ensure input is valid
	this->port = setPort;
}
int client::connectToServer()
{
	//should create connection to given address on given port
	//class needs to keep track of the socket and have dedicated function to read from it
	if(WSAStartup(0x202, &wsaData) != 0)
	{
		//fail
		WSACleanup();
		return -1;
	}
	addr = inet_addr(server_addr.c_str());
	hp = gethostbyaddr((char *)&addr, 4, AF_INET);

	memset(&server, 0, sizeof(server));
	memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(port);
	
	sock = socket(AF_INET, socketType, 0);

	connect(sock, (struct sockaddr*)&server, sizeof(server));
	return 1;
}