#include "client.h"

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
	//Last Changed: 3-5-12 @ 12:13
	//changelog:
	//made function set port
	//validated the input
	//added confirmation
	//todo:
	//
	if(setPort > 65535)
	{
		cout << "INVALID PORT!\n";
		system("pause");
		exit(1);
	}else
	{
		this->port = setPort;
		cout << "Port Set!\n";
	}
}

int client::connectToServer()
{
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (SDLNet_ResolveHost(ip, this->server_addr.c_str(), this->port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(sd = SDLNet_TCP_Open(ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if(!(this->UDPsock = SDLNet_UDP_Open(port)))
	{
		fprintf(stderr, "ERROR OPENING UDP SOCKET: %s\n", SDLNet_GetError());
		system("pause");
		exit(EXIT_FAILURE);
	}
	this->UDPpack = SDLNet_AllocPacket(512);


	/* test sending something to the server */
	string buff = "Client Connected!";

	SDLNet_ResolveHost(ip, this->server_addr.c_str(),port);
	UDPpack->address = *ip;
	strcpy((char*)UDPpack->data, "test");
	UDPpack->len = 5;
	SDLNet_UDP_Send(UDPsock,-1,UDPpack);

	SDLNet_TCP_Send(sd, (void *)buff.c_str(), buff.length()+1);
	char temp[32];
	SDLNet_TCP_Recv(sd, temp, 32);
	if(strcmp(temp,"SIG:START"))
	{
		cout << "unsuccessful connection!\n" << buff << "\nAborting...\n";
		return -1;
	}
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

int client::performUpdate(string upd)
{
	int updateType = 0;
	UpdMess update(upd);
	updateType = update.getType();
	if(updateType == CREEP)
	{
		if(creeps.checkForObjectWithID(update.getId1())){
			creeps.getObjectWithID(update.getId1())->setPlayer(update.getPlayer());
			creeps.getObjectWithID(update.getId1())->setX(update.getVal(0));
			creeps.getObjectWithID(update.getId1())->setY(update.getVal(1));
			creeps.getObjectWithID(update.getId1())->setHealth(update.getVal(2));
		}
		else
		{
			creeps.insertInOrder(new creep(update.getVal(3), update.getPlayer(), update.getVal(4), update.getVal(0), update.getVal(1)));
			creeps.getObjectWithID(update.getId1())->setHealth(update.getVal(2));
		}
	}
	else if(updateType == TOWER)
	{
		if(towers.checkForObjectWithID(update.getId1()))
		{
			towers.getObjectWithID(update.getId1())->setX(update.getVal(0));
			towers.getObjectWithID(update.getId1())->setY(update.getVal(1));
			towers.getObjectWithID(update.getId1())->setType(update.getVal(2));
		}
		else
		{
			towers.insertInOrder(new tower(1,update.getVal(2),update.getVal(0),update.getVal(1)));
		}

	}
	else if(updateType == TOWERATTACK){


	}
	else{
		return 0;
	}
	return 1;
}

string client::recieveMessage()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->sd, buff, 16 /*512*/));
	//cout << buff << "\n";
	string ret = buff;
	return buff;
}

int client::recieveMessageToQueue()
{
	//receives messages and processes them while there are messages to be received
	string packData = recieveMessageUDP();
	int i = 0;
	int len = 0;
	string temp;
	while (packData != "NO MESSAGE")
	{
		len = packData.length();
		for(i = 0;i < len + 1; i++)
		{
			if(packData[i] != '\n' && packData[i] != '\0')
			{
				temp += packData[i];
			}
			else
			{
				performUpdate(temp);
				temp = "";
			}
		}
		packData = recieveMessageUDP();
	}
	return 0;
}

string client::recieveMessageUDP()
{
	if(!UDPsock)
	{
		return "UDP Socket Not Set";
	}
	if (SDLNet_UDP_Recv(this->UDPsock,UDPpack))
	{
		string retStr = (char *)UDPpack->data;
		return retStr;
	}
	return "NO MESSAGE";
}
