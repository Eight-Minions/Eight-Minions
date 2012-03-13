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

	/* Creating creeps for testing here */
	creep n(1,1,20,20);
	this->testc = n;
	creep q(2,1,200,200);
	this->testca = q;

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
	//put down background image
	SDL_BlitSurface(background, NULL, screen, NULL);
	//loop through each tower and display it
	//loop through each creep and display it
	//display any special effects, bullets, explosions, etc
	//display interface objects, health, money stats, etc <-maybe only update this when it changes? just an idea
	
	//testing creeps
	this->testc.displayCreep(screen);
	this->testca.displayCreep(screen);
	//end testing

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
	while(run)
	{
		//gather input
		if( SDL_PollEvent( &event ) )
		{
			

			if(event.type == SDL_QUIT)
			{
				run = 0;
			}
		}
		/*
		while(SDLNet_CheckSockets(socketset, 1) > 0)
		{
			cout << "socket has data, attempting to read\n";
			if(SDLNet_SocketReady(sd))
			{
				this->performUpdate(this->recieveMessage());
			}
		}*/

		cout << this->recieveMessageUDP() << "\n";
		this->display();

		/*
		if(this->testca.getX() > 400)
			cx = -1;
		if(this->testca.getX() < 120)
			cx = 1;
		if(this->testca.getY() > 450)
			cy = -1;
		if(this->testca.getY() < 80)
			cy = 1;
		this->testca.setX(testca.getX() + cx);
		this->testca.setY(testca.getY() + cy);
		*/
		SDL_Delay(20);
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
	this->UDPpack = SDLNet_AllocPacket(256);


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

	//temporary testing code starts here;
	if(upd[5] == '1')
	{
		int x = (1000 * (upd[6] - '0')) + (100 * (upd[7] - '0')) + (10 * (upd[8] - '0')) + (upd[9] - '0');
		this->testc.setX(x);
		cout << "X value changed to: " << x << "\n";
	}
	if(upd[5] == '2')
	{
		int y = (1000 * (upd[6] - '0')) + (100 * (upd[7] - '0')) + (10 * (upd[8] - '0')) + (upd[9] - '0');
		this->testc.setY(y);
		cout << "Y value changed to: " << y << "\n";
	}

	return 0;
}

string client::recieveMessage()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->sd, buff, 16 /*512*/));
	//cout << buff << "\n";
	string ret = buff;
	return buff;
}

void client::recieveMessageToQueue()
{

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