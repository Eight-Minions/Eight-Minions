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
		if(creeps.checkForObjectWithID(update.getId1()))
		{
			if(update.getVal(2) <= 0) //delete dead creeps
			{
				creeps.deleteNode(update.getId1());
			}
			else
			{
				creep *temp = creeps.getObjectWithID(update.getId1());
				temp->setPlayer(update.getPlayer());
				int xdif = update.getVal(0) - temp->getX();

				if( xdif < 0)
					temp->setDir(0);
				else if(xdif > 0)
					temp->setDir(2);
				else
				{
					int ydif = update.getVal(1) - temp->getY();
					if(ydif < 0)
						temp->setDir(3);
					else if(ydif > 0)
						temp->setDir(1);
				}

				temp->setX(update.getVal(0));
				temp->setY(update.getVal(1));
				temp->setHealth(update.getVal(2));
				temp->setUpdateTime(SDL_GetTicks());
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
				towers.deleteNode(update.getId1());
			}
			towers.insertWithID(update.getId1(), new structure(1 ,update.getPlayer(), update.getVal(3),update.getVal(1),update.getVal(2)));
		}
		else if(update.getVal(0) == TOWERATTACK)
		{
			attacks.push_back(new attackAnim(update.getVal(1) * GRID_SIZE + BOARD_X_OFFSET,update.getVal(2) * GRID_SIZE + BOARD_Y_OFFSET,0,towerDelays[update.getVal(3)],update.getId1()));
		}
		else if(update.getVal(0) == TOWERDELETE)
		{
			this->removeTowerRecieve(update.getId1());
		}
		else if(update.getVal(0) == TOWERUPGRADE)
		{
			this->upgradeTowerRecieve(update.getId1());
		}
		else if(update.getVal(0) == TOWERCHANGE)
		{
			if(update.getVal(1) >= FASTCREEPTOWER && update.getVal(1) <= FATTYCREEPTOWER)
				this->changeSpawnerTypeRecieve(update.getId1(), update.getVal(1));
			else
				this->changeTowerRecieve(update.getId1(), update.getVal(1));
		}
		else if(update.getVal(0) == TOWERTOGGLE)
		{
			this->toggleTowerRecieve(update.getId1(), update.getVal(1));
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
	else if(updateType == GAMEOVER)
	{
		gameOverRecieve(update.getVal(0));
	}
	else if(updateType == BASE)
	{
		if(update.getVal(0) == UPGRADE)
			this->upgradeBaseRecieve();
		else if(update.getVal(0) == ADDTYPE)
			this->addTypeToBaseRecieve(update.getVal(1));
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
		//cout << packData << endl;
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

bool client::removeTowerSend(int x, int y) // Accepts Grid X and Grid Y
{
	cListNode<structure*> *curTower = towers.getStart();
	while (curTower != NULL)
	{
		if(curTower->getData()->getX() == x && curTower->getData()->getY() == y)
		{
			sendToServerUDP(UpdMess(this->self->getPnum(), TOWER, TOWERDELETE, curTower->getIndex()).getMT());
			return true;  // Sent message
		}
		curTower = curTower->getNext();
	}	
	return false; // not found
}
bool client::removeTowerRecieve(int towerID)
{
	if(towers.checkForObjectWithID(towerID))
	{	
		towers.deleteNode(towerID);
		return true;
	}
	return false;
}
bool client::upgradeTowerSend(int x, int y)
{
	cListNode<structure*> *curTower = towers.getStart();
	while (curTower != NULL)
	{
		if(curTower->getData()->getX() == x && curTower->getData()->getY() == y)
		{
			if(curTower->getData()->getLevel() < 5)
			{
				if(this->self->getMoney() >= curTower->getData()->getCost())
				{
					sendToServerUDP(UpdMess(this->self->getPnum(), TOWER, TOWERUPGRADE, curTower->getIndex()).getMT());
					return true;
				}
			}
			return false;
		}
		curTower = curTower->getNext();
	}	
	return false;
}
bool client::upgradeTowerRecieve(int towerID)
{
	if(towers.checkForObjectWithID(towerID))
	{
		//towers.getNodeWithID(towerID)->getData()->upgradeClient();
		if(towers.getNodeWithID(towerID)->getData()->getLevel() < 5)
			towers.getNodeWithID(towerID)->getData()->setLevel(towers.getNodeWithID(towerID)->getData()->getLevel() + 1);
		char buff[4];
		SDL_FreeSurface(text[19]);
		text[19] = TTF_RenderText_Solid(font10, itoa(towers.getNodeWithID(towerID)->getData()->getLevel(),buff,10), Cblack);
		return true;
	}
	return false;
}
bool client::changeTowerTypeSend( int Tid, int newType )
{
	sendToServerUDP(UpdMess(this->self->getPnum(), TOWER, TOWERCHANGE, Tid, newType).getMT());
	return true;
}
bool client::changeTowerRecieve(int towerID, int newType)
{
	if(towers.checkForObjectWithID(towerID))
	{
		towers.getNodeWithID(towerID)->getData()->changeTypeClient(newType);
		return true;
	}
	return false;
}
bool client::toggleTowerSend(int Tid)
{
	if(towers.getNodeWithID(Tid)->getData()->getType() >= NORMCREEPTOWER && towers.getNodeWithID(Tid)->getData()->getType() <= FATTYCREEPTOWER)
	{
		if(towers.getNodeWithID(Tid)->getData()->isPaused())
		{
			sendToServerUDP(UpdMess(this->self->getPnum(), TOWER, TOWERTOGGLE, Tid, false).getMT());
			towers.getNodeWithID(Tid)->getData()->unpause();
			return false;
		}
		else
		{
			sendToServerUDP(UpdMess(this->self->getPnum(), TOWER, TOWERTOGGLE, Tid, true).getMT());
			towers.getNodeWithID(Tid)->getData()->pause();
			return true;
		}
	}
}
bool client::toggleTowerRecieve(int towerID, int newState)
{
	if(towers.checkForObjectWithID(towerID))
	{
		if(newState == true)
			towers.getNodeWithID(towerID)->getData()->pause();
		else
			towers.getNodeWithID(towerID)->getData()->unpause();
		return true;
	}
	return false;
}

int client::gameOverRecieve(int winner)
{
	// Not sure what to do here. I think this is for you Jeromy
	//ten four

	//load game over image (happy image for win, sad image for lose)
	//create text saying which player won

	SDL_Surface *messageBox = LoadImageCK("images/messageBox.png");
	SDL_Surface *gameOverText;
	SDL_Rect* message_box = newRect(50,50,0,0);
	SDL_Rect* gotext = newRect(100,150,0,0);
	if(self->getPnum() == winner)
	{
		gameOverText = TTF_RenderText_Solid(font, "Congratulations! You Won!",Cblack);
	}
	else
	{
		gameOverText = TTF_RenderText_Solid(font, "You lost....",Cblack);
	}

	while(this->run_game == 1)
	{
		if( SDL_PollEvent( &event ) )
		{
			if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
			{
				run_game = 0;
			}
		}
		SDL_BlitSurface(messageBox,NULL,screen,message_box);
		SDL_BlitSurface(gameOverText,NULL,screen,gotext);
		SDL_Flip(screen);
		SDL_Delay(50);
	}
	//display it
	//wait for some keypress or mouse click to end the game

	return winner;
}

bool client::upgradeBaseSend()
{
	sendToServerUDP(UpdMess(this->self->getPnum(), BASE, UPGRADE).getMT());
	return true;
}
bool client::upgradeBaseRecieve()
{
	this->baseLevel += 1;
	string buff = "Level ";
	buff += (baseLevel + '0');
	SDL_FreeSurface(text[25]);
	text[25] = TTF_RenderText_Solid(font, buff.c_str(), Cblack);
	return true;
}
bool client::addTypeToBaseSend(int newType)
{
	sendToServerUDP(UpdMess(this->self->getPnum(), BASE, ADDTYPE, newType).getMT());
	return true;
}
bool client::addTypeToBaseRecieve(int newType)
{

	int buttonNum = 0;
	switch(newType)
	{
	case FAST:
		buttonNum = 21;
		break;
	case SWARM:
		buttonNum = 22;
		break;
	case FATTY:
		buttonNum = 23;
		break;
	case TANK:
		buttonNum = 24;
		break;
	case TITAN:
		buttonNum = 25;
		break;
	}

	buttons[buttonNum]->setClick(true);
	buttons[buttonNum]->Lock();
	return true;
}
bool client::changeSpawnerTypeSend(int x, int y, int newType)
{
	cListNode<structure*> *curTower = towers.getStart();
	while (curTower != NULL)
	{
		if(curTower->getData()->getX() == x && curTower->getData()->getY() == y)
		{
			if(curTower->getData()->getType() == NORMCREEPTOWER && (newType >= FASTCREEPTOWER && newType <= FATTYCREEPTOWER))
			{
				sendToServerUDP(UpdMess(this->self->getPnum(), TOWER, TOWERCHANGE, curTower->getIndex(), newType).getMT());
			}
		}
		curTower = curTower->getNext();
	}	
	return false;
}
bool client::changeSpawnerTypeRecieve(int towerID, int newType)
{
	if(towers.checkForObjectWithID(towerID))
	{
		towers.getNodeWithID(towerID)->getData()->changeTypeClient(newType);
		return true;
	}
	return false;
}