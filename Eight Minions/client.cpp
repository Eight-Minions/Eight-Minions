#include "client.h"


int client::init()
{
	//i kinda want something to happen here, i feel all naked having empty functions	


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
	this->recieveMessage();
	system("pause");
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
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (SDLNet_ResolveHost(&ip, this->server_addr.c_str(), this->port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	

	/* test sending something to the server */
	string buff = "Client Connected!";
	SDLNet_TCP_Send(sd, (void *)buff.c_str(), buff.length()+1);

	//should create connection to given address on given port
	//class needs to keep track of the socket and have dedicated function to read from it

	return 1;
}

int client::sendToServer(string buff)
{
	if(!this->sd)
	{
		cout << "No Connection!\n";
		return -1;
	}
	else
	{
		if(SDLNet_TCP_Send(sd, (void *)buff.c_str(), buff.length()+1) < buff.length() + 1)
		{
			cout << "Message to server failed to send...\n";
			return -1;
		}
	}
	return 1;
}

int client::recieveMessage()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->sd, buff, 512));
	cout << buff << "\n";
	return 0;
}