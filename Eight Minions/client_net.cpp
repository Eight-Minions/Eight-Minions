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

	this->self = new player;
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
	this->self->setPnum(temp[0] - '0');
	if(strcmp(&temp[1],"SIG:START"))
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
			if(update.getVal(2) <= 0) //delete dead creeps
			{
				creeps.deleteNode(update.getId1());
			}
			else
			{
				creeps.getObjectWithID(update.getId1())->setPlayer(update.getPlayer());
				creeps.getObjectWithID(update.getId1())->setX(update.getVal(0));
				creeps.getObjectWithID(update.getId1())->setY(update.getVal(1));
				creeps.getObjectWithID(update.getId1())->setHealth(update.getVal(2));
			}
		}
		else
		{
			// ERROR creep does not exist on this end
		}
	}
	else if(updateType == NEWCREEP)
	{
		creeps.insertWithID(update.getId1(), new creep(update.getVal(3), update.getPlayer(), update.getVal(4), update.getVal(0), update.getVal(1)));
		creeps.getObjectWithID(update.getId1())->setHealth(update.getVal(2));
	}
	else if(updateType == TOWER)
	{
		if(update.getVal(0) == TOWERCREATION)
		{
			if(towers.checkForObjectWithID(update.getId1()))
			{
				towers.getObjectWithID(update.getId1())->setX(update.getVal(1));
				towers.getObjectWithID(update.getId1())->setY(update.getVal(2));
				towers.getObjectWithID(update.getId1())->setType(update.getVal(3));
			}
			else
			{
				towers.insertInOrder(new structure(1,update.getPlayer(), update.getVal(3),update.getVal(1),update.getVal(2)));
			}
		}
		else if(update.getVal(0) == TOWERATTACK)
		{
			attacks.push_back(new attackAnim(update.getVal(1) * GRID_SIZE + BOARD_X_OFFSET,update.getVal(2) * GRID_SIZE + BOARD_Y_OFFSET,0,towerDelays[update.getVal(3)],update.getId1()));
		}
	}
	else if(updateType == PLAYERUPDATE)
	{
		if(update.getPlayer() == self->getPnum())
		{
			self->setHealth(update.getVal(0));
			self->setMoney(update.getVal(1));
			char buff[8];
			text[1] = TTF_RenderText_Solid( font, _itoa(self->getHealth(),buff,10), Cwhite);
			text[3] = TTF_RenderText_Solid(font, _itoa(self->getMoney(),buff,10), Cblack);
		}
	}
	else
	{
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
		//dump << packData << endl;
		cout << packData << endl;
		for(i = 0;i < len + 1; i++)
		{
			if(packData[i] != '\n' && packData[i] != '\0')
			{
				temp += packData[i];
			}
			else
			{
				//cout << temp << "\n";
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
		if(retStr != "")
		{
			return retStr;
		}
	}
	return "NO MESSAGE";
}

int client::sendToServerUDP( string mess )
{
	char *temp = (char *)malloc(mess.length() + 1);
	strcpy(temp,mess.c_str());
	strcpy((char *)UDPpack->data,(char *) temp);
	UDPpack->len = mess.length() + 1;
	SDLNet_UDP_Send(UDPsock,-1,UDPpack);

	return 1;
}