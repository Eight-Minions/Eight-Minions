#include "client.h"


int client::init()
{
	//Start SDL
	if(SDL_Init( SDL_INIT_EVERYTHING ) == -1)
	{
		cout << "SDL Failed to initialize...\n";
		return -1;
	}

	//Sets window caption
	SDL_WM_SetCaption( "Eight Minions", NULL );
	//create screen, params are width in pixels, height in pixels, bpp, and flags
	screen = SDL_SetVideoMode(840,550,32,SDL_SWSURFACE);
	this->background = IMG_Load("background.png");

	socketset = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketset, this->sd);

	//<test code>
	/* Creating creeps for testing here */
	creep n(1,1,20,20);
	this->testc = n;
	creep q(2,1,200,200);
	this->testca = q;
	//</test code>

	return 1;
}

void client::cleanup()
{
	//do all freeing of memory and cleanup type stuff here
	SDL_free(background);
	SDL_Quit();
}
void client::display()
{
	SDL_BlitSurface(background, NULL, screen, NULL);

	//<test code>
	this->testc.displayCreep(screen);
	//</test code>

	this->displayTowers();
	this->displayCreeps();
	this->displayMisc();
	this->displayUI();
	SDL_Flip(screen);
}

int client::run()
{
	if(this->init() == -1)
	{
		cout << "Function Init failed to complete.\n";
		return -1;
	}
	//main run loop. does not work at this time, but will eventually look like this.
	int run = 1;
	while(run)
	{
		if(SDL_PollEvent( &event ))
			if(event.type == SDL_QUIT)
				run = 0;


		this->recieveMessageToQueue();
		this->parseQueue();
		this->display();

		SDL_Delay(20);
	}

	this->cleanup();
	return 0;
}

int client::testrun()
{
	if(this->init() == -1)
	{
		cout << "Function Init failed to complete.\n";
		return -1;
	}
	//main run loop
	int run = 1;
	UpdMess testMess;
	string temp;
	int now = 0;
	int n_rec = 0;
	while(run)
	{
		//gather input - the follow series of if-statements will handle all user input
		if( SDL_PollEvent( &event ) )
		{
			if(event.type == SDL_QUIT)
			{
				run = 0;
			}
			if(event.type == SDL_MOUSEBUTTONUP)
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					event.button.x; //x coordinate of click on the window
					event.button.y; //y coordinate of click on the window

					//////////////////////////////////////////////////////////////
					//Your goal, using this information, make the game do things
					//when you click, i.e. clicking a tower displays info about it
					//clicking the 'buy' menu (or whatever we decide to have) opens 
					//a menu of things to buy. clicking a tower to buy and clicking a 
					//spot on the map checks if the tower can go there and then puts it 
					//there, subtracts money, and any other tasks that need to be done
					//some of this will require server message which i will explain/help
					//with, but i dont want to do everything. so this is not my task
					///////////////////////////////////////////////////////////////
				}

			}
		}

		//<test code>
		while(testMess.setMess(this->recieveMessageUDP()))
		{
			testc.setX((double)testMess.getVal(0));
			testc.setY((double)testMess.getVal(1));
			cout << testc.getX() << " " << testc.getY() << "\n";
		}

		//</test code>
		this->display();


		SDL_Delay(20); //change this to be scaled by a timer
	}

	this->cleanup();
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

	if(!(this->UDPsock = SDLNet_UDP_Open(port)))
	{
		fprintf(stderr, "ERROR OPENING UDP SOCKET: %s\n", SDLNet_GetError());
		system("pause");
		exit(EXIT_FAILURE);
	}
	this->UDPpack = SDLNet_AllocPacket(512);


	/* test sending something to the server */
	string buff = "Client Connected!";
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
	if(updateType == CREEP){
		if(creeps.checkForObjectWithID(update.getId1())){
			creeps.getObjectWithID(update.getId1()).setX(update.getVal(0));
			creeps.getObjectWithID(update.getId1()).setY(update.getVal(1));
			creeps.getObjectWithID(update.getId1()).setHealth(update.getVal(2));
		}
		else{
			creeps.insertInOrder(creep(update.getVal(3),update.getVal(4), update.getVal(0), update.getVal(1)));
			creeps.getObjectWithID(update.getId1()).setHealth(update.getVal(2));
		}
	}
	else if(updateType == TOWER){

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
	do 
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
	} while (packData != "NO MESSAGE");
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

void client::parseQueue()
{

}

void client::displayCreeps()
{
	cListNode<creep> *cur = creeps.getStart();
	while(cur != NULL)
	{
		cur->getData().displayCreep(screen);
	}
}

void client::displayTowers()
{
	
}

void client::displayMisc()
{

}

void client::displayUI()
{

}
