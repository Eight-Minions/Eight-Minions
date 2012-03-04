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

	return 1;
}