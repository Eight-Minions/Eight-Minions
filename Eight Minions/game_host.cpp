#include "game_host.h"

int game_host::init()
{

	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (SDLNet_ResolveHost(&ip, NULL, this->port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	socketset = SDLNet_AllocSocketSet(2);

	cout << "Init completed\n";

	return 0; // temporary
}

int game_host::waitForClients()
{
	cout << "waiting for first player to connect...\n";
	while(!(player1sd = SDLNet_TCP_Accept(sd)));
	cout << this->recieveMessagep1() << "\n";
	SDLNet_TCP_AddSocket(socketset, player1sd); //could error check here
	cout << "waiting for second player to connect...\n";
	while(!(player2sd = SDLNet_TCP_Accept(sd)));
	cout << this->recieveMessagep2() << "\n";
	SDLNet_TCP_AddSocket(socketset, player2sd); //could error check here as well
	cout << "both clients connected, continuing...\n";
	return 1;
}

int game_host::run()
{
	this->init();
	this->waitForClients();
	this->sendToClients("testing!!!");

	int r = 1;
	int x = 10;
	int change = 1;
	string n;
	char q[16];
	while(r)
	{
		if(SDLNet_CheckSockets(socketset,1) > 0 )
		{
			if(SDLNet_SocketReady(player1sd))
			{
				cout << this->recieveMessagep1() << "\n";
			}
			if(SDLNet_SocketReady(player2sd))
			{
				cout << this->recieveMessagep2() << "\n";
			}
		}
		x += change;
		if(x > 400)
			change = -1;
		if(x < 1)
			change = 1;
		itoa(x,q,10);
		n = q;
		cout << n << "\n";
		this->sendToClients(n);
		SDL_Delay(30);
	}


	//runs the game itself
	return 0;
}
void game_host::setPort(unsigned int setPort)
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


int game_host::sendUpdate()
{
	//send updates about the game to each player
	//each update will be a 16 (maybe more) character text string
	//the first character will represent the base type of update
	//1 = message, 2 = tower update, 3 = creep update, 4 = player update
	//the contents of the update will change depending on their base type
	//for messages, the rest of the string will be the message
	//for creep and tower updates, the next four characters will be the creep/tower number
	//the character after that will represent the attribute to be updated
	//then the remaining characters will be the new value for said attribute


	return 0;
}

int game_host::sendUpdate(char mess[15])
{
	string m = "1";
	m.append(mess);
	this->sendToClients(m);
	return 0;
}

int game_host::sendUpdate(int ToC, int id, int attr, int newVal)
{
	string m;
	m += (char) '0' + ToC;
	m += (char) '0' + id / 1000;
	m += (char) '0' + ((id % 1000) / 100);
	m += (char) '0' + ((id % 100) / 10);
	m += (char) '0' + id % 10;
	m += (char) '0' + attr;
	m += (char) '0' + newVal / 1000;
	m += (char) '0' + ((newVal % 1000) / 100);
	m += (char) '0' + ((newVal % 100) / 10);
	m += (char) '0' + newVal % 10;
	cout << m;
	return 0;
}

int game_host::sendToClients(string buff)
{
	if(!this->player1sd || !this->player2sd)
	{
		cout << "No Connection!\n";
		return -1;
	}
	else
	{
		if(SDLNet_TCP_Send(player1sd, (void *)buff.c_str(), buff.length()+1) < buff.length() + 1)
		{
			cout << "Message to client 1 failed to send...\n";
			return -1;
		}
		if(SDLNet_TCP_Send(player2sd, (void *)buff.c_str(), buff.length()+1) < buff.length() + 1)
		{
			cout << "Message to client 2 failed to send...\n";
			return -1;
		}
	}
	return 1;
}

string game_host::recieveMessagep1()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->player1sd, buff, 512));
	//cout << buff << "\n";
	string ret = buff;
	return ret;
}

string game_host::recieveMessagep2()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->player2sd, buff, 512));
	//cout << buff << "\n";
	string ret = buff;
	return ret;
}

void game_host::recieveMessageToQueue()
{
	//pseudocode:
	//recieve string from p1
	//push to queue
	//recieve string from p2
	//push to queue
	//return
}